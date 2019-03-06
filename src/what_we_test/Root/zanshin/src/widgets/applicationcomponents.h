/* This file is part of Zanshin

   Copyright 2014 Kevin Ottens <ervin@kde.org>

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


#ifndef WIDGETS_APPLICATIONCOMPONENTS_H
#define WIDGETS_APPLICATIONCOMPONENTS_H

#include <QHash>
#include <QModelIndexList>
#include <QObject>
#include <QPointer>

#include <functional>

#include "domain/task.h"

#include "presentation/metatypes.h"

class QAction;
class QWidget;

namespace Presentation {
class ErrorHandler;
}

namespace Widgets {

class AvailablePagesView;
class AvailableSourcesView;
class EditorView;
class PageView;
class PageViewErrorHandler;
class RunningTaskWidget;

class QuickSelectDialogInterface;

class ApplicationComponents : public QObject
{
    Q_OBJECT
public:
    typedef QSharedPointer<QuickSelectDialogInterface> QuickSelectDialogPtr;
    typedef std::function<QuickSelectDialogPtr(QWidget*)> QuickSelectDialogFactory;

    explicit ApplicationComponents(QWidget *parent = nullptr);
    ~ApplicationComponents();

    QHash<QString, QAction*> globalActions() const;

    QObjectPtr model() const;

    AvailableSourcesView *availableSourcesView() const;
    AvailablePagesView *availablePagesView() const;
    virtual PageView *pageView() const;
    EditorView *editorView() const;
    RunningTaskWidget *runningTaskView() const;

    QuickSelectDialogFactory quickSelectDialogFactory() const;

public slots:
    virtual void setModel(const QObjectPtr &model);
    void setQuickSelectDialogFactory(const QuickSelectDialogFactory &factory);

private slots:
    void onCurrentPageChanged(QObject *page);
    void onCurrentTaskChanged(const Domain::Task::Ptr &task);
    void onMoveItemsRequested();

private:
    Presentation::ErrorHandler *errorHandler() const;
    void moveItems(const QModelIndex &destination, const QModelIndexList &droppedItems);

    QHash<QString, QAction*> m_actions;
    QObjectPtr m_model;

    QWidget *m_parent;
    QPointer<AvailableSourcesView> m_availableSourcesView;
    QPointer<AvailablePagesView> m_availablePagesView;
    QPointer<PageView> m_pageView;
    QPointer<EditorView> m_editorView;
    QPointer<RunningTaskWidget> m_runningTaskView;

    QScopedPointer<PageViewErrorHandler> m_errorHandler;
    QuickSelectDialogFactory m_quickSelectDialogFactory;
};

}

#endif // WIDGETS_APPLICATIONCOMPONENTS_H
