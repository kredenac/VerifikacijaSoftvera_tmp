/* This file is part of Zanshin

   Copyright 2015 Theo Vaucher <theo.vaucher@gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License or (at your option) version 3 or any later version
   accepted by the membership of KDE e.V. (or its successor approved
   by the membership of KDE e.V.), which shall act as a proxy
   defined in Section 14 of version 3 of the license.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
   USA.
*/


#include "workdaypagemodel.h"

#include <QMimeData>

#include <KLocalizedString>

#include "domain/taskqueries.h"
#include "domain/taskrepository.h"

#include "presentation/querytreemodel.h"

#include "utils/datetime.h"

using namespace Presentation;

WorkdayPageModel::WorkdayPageModel(const Domain::TaskQueries::Ptr &taskQueries,
                                   const Domain::TaskRepository::Ptr &taskRepository,
                                   QObject *parent)
    : PageModel(parent),
      m_taskQueries(taskQueries),
      m_taskRepository(taskRepository)
{
}

Domain::Task::Ptr WorkdayPageModel::addItem(const QString &title, const QModelIndex &parentIndex)
{
    const auto parentData = parentIndex.data(QueryTreeModelBase::ObjectRole);
    const auto parentTask = parentData.value<Domain::Task::Ptr>();

    auto task = Domain::Task::Ptr::create();
    task->setTitle(title);
    if (!parentTask)
        task->setStartDate(Utils::DateTime::currentDate());
    const auto job = parentTask ? m_taskRepository->createChild(task, parentTask)
                   : m_taskRepository->create(task);
    installHandler(job, i18n("Cannot add task %1 in Workday", title));

    return task;
}

void WorkdayPageModel::removeItem(const QModelIndex &index)
{
    QVariant data = index.data(QueryTreeModelBase::ObjectRole);
    auto task = data.value<Domain::Task::Ptr>();
    if (task) {
        const auto job = m_taskRepository->remove(task);
        installHandler(job, i18n("Cannot remove task %1 from Workday", task->title()));
    }
}

void WorkdayPageModel::promoteItem(const QModelIndex &index)
{
    QVariant data = index.data(QueryTreeModelBase::ObjectRole);
    auto task = data.value<Domain::Task::Ptr>();
    Q_ASSERT(task);
    const auto job = m_taskRepository->promoteToProject(task);
    installHandler(job, i18n("Cannot promote task %1 to be a project", task->title()));
}

QAbstractItemModel *WorkdayPageModel::createCentralListModel()
{
    auto query = [this](const Domain::Task::Ptr &task) -> Domain::QueryResultInterface<Domain::Task::Ptr>::Ptr {
        if (!task)
            return m_taskQueries->findWorkdayTopLevel();
        else
            return m_taskQueries->findChildren(task);
    };

    auto flags = [](const Domain::Task::Ptr &task) {
        const Qt::ItemFlags defaultFlags = Qt::ItemIsSelectable
                                         | Qt::ItemIsEnabled
                                         | Qt::ItemIsEditable
                                         | Qt::ItemIsDragEnabled;

        return task ? (defaultFlags | Qt::ItemIsUserCheckable | Qt::ItemIsDropEnabled) : defaultFlags;
    };

    using AdditionalInfo = Domain::QueryResult<Domain::Project::Ptr>::Ptr; // later on we'll want a struct with the context query as well

    auto data = [](const Domain::Task::Ptr &task, int role, const AdditionalInfo &projectQueryResult) -> QVariant {
        switch (role) {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return task->title();
        case Qt::CheckStateRole:
            return task->isDone() ? Qt::Checked : Qt::Unchecked;
        case Presentation::QueryTreeModelBase::AdditionalInfoRole:
            if (projectQueryResult && !projectQueryResult->data().isEmpty()) {
                Domain::Project::Ptr project = projectQueryResult->data().at(0);
                return i18n("Project: %1", project->name());
            }
            return i18n("Inbox"); // TODO add source name
        default:
            break;
        }
        return QVariant();
    };

    auto fetchAdditionalInfo = [this](const QModelIndex &index, const Domain::Task::Ptr &task) -> AdditionalInfo {
        if (index.parent().isValid()) // children are in the same collection as their parent, so the same project
            return nullptr;

        AdditionalInfo projectQueryResult = m_taskQueries->findProject(task);
        if (projectQueryResult) {
            QPersistentModelIndex persistentIndex(index);
            projectQueryResult->addPostInsertHandler([persistentIndex](const Domain::Project::Ptr &, int) {
                // When a project was found (inserted into the result), update the rendering of the item
                auto model = const_cast<QAbstractItemModel *>(persistentIndex.model());
                model->dataChanged(persistentIndex, persistentIndex);
            });
        }
        return projectQueryResult;
    };

    auto setData = [this](const Domain::Task::Ptr &task, const QVariant &value, int role) {
        if (role != Qt::EditRole && role != Qt::CheckStateRole) {
            return false;
        }

        const auto currentTitle = task->title();
        if (role == Qt::EditRole)
            task->setTitle(value.toString());
        else
            task->setDone(value.toInt() == Qt::Checked);

        const auto job = m_taskRepository->update(task);
        installHandler(job, i18n("Cannot modify task %1 in Workday", currentTitle));
        return true;
    };

    auto drop = [this](const QMimeData *mimeData, Qt::DropAction, const Domain::Task::Ptr &parentTask) {
        if (!mimeData->hasFormat(QStringLiteral("application/x-zanshin-object")))
            return false;

        auto droppedTasks = mimeData->property("objects").value<Domain::Task::List>();
        if (droppedTasks.isEmpty())
            return false;

        foreach(const auto &childTask, droppedTasks) {
            if (parentTask) {
                const auto job = m_taskRepository->associate(parentTask, childTask);
                installHandler(job, i18n("Cannot move task %1 as sub-task of %2", childTask->title(), parentTask->title()));
            } else {
                childTask->setStartDate(Utils::DateTime::currentDate());
                // TODO something like m_taskRepository->update(childTask) is missing here
                // It was removed in commit c97a99bf because it led to a LLCONFLICT in akonadi (due to dissociate below).
                // The removal broke tests-features-workday-workdaydraganddropfeature (date not changed).

                auto job = m_taskRepository->dissociate(childTask);
                installHandler(job, i18n("Cannot deparent task %1 from its parent", childTask->title()));
            }
        }

        return true;
    };

    auto drag = [](const Domain::Task::List &tasks) -> QMimeData* {
        if (tasks.isEmpty())
            return nullptr;

        auto data = new QMimeData;
        data->setData(QStringLiteral("application/x-zanshin-object"), "object");
        data->setProperty("objects", QVariant::fromValue(tasks));
        return data;
    };

    return new QueryTreeModel<Domain::Task::Ptr, AdditionalInfo>(query, flags, data, setData, drop, drag, fetchAdditionalInfo, this);
}
