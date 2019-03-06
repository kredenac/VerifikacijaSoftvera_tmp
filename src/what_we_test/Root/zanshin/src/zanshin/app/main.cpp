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

#include <QApplication>
#include <QBoxLayout>
#include <QDockWidget>
#include <QProcess>
#include <QAction>

#include <KActionCollection>


#include <KXmlGuiWindow>

#include <KConfigGroup>
#include <KSharedConfig>

#include "widgets/applicationcomponents.h"
#include "widgets/availablepagesview.h"
#include "widgets/availablesourcesview.h"
#include "widgets/editorview.h"
#include "widgets/pageview.h"

#include "presentation/applicationmodel.h"

#include "utils/dependencymanager.h"

#include "aboutdata.h"
#include "dependencies.h"

#include <iostream>
#include <KAboutData>
#include <KLocalizedString>
#include <QCommandLineParser>

int main(int argc, char **argv)
{
    KLocalizedString::setApplicationDomain("zanshin");
    QApplication app(argc, argv);
    App::initializeDependencies();

    auto aboutData = App::getAboutData();
    QCommandLineParser parser;
    KAboutData::setApplicationData(aboutData);
    parser.addVersionOption();
    parser.addHelpOption();
    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);

    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("zanshin-migratorrc"));
    KConfigGroup group = config->group("Migrations");
    if (!group.readEntry("MigratedTags", false)) {
        std::cerr << "Migrating tags, please wait..." << std::endl;
        QProcess proc;
        proc.start(QStringLiteral("zanshin-migrator"));
        proc.waitForFinished(-1);
        if (proc.exitStatus() == QProcess::CrashExit) {
            std::cerr << "Migrator crashed!" << std::endl;
        } else if (proc.exitCode() == 0) {
            std::cerr << "Migration done" << std::endl;
        } else {
            std::cerr << "Migration error, code" << proc.exitCode() << std::endl;
        }
    }

    auto widget = new QWidget;
    auto components = new Widgets::ApplicationComponents(widget);
    components->setModel(Presentation::ApplicationModel::Ptr::create());

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(components->pageView());
    widget->setLayout(layout);

    auto sourcesDock = new QDockWidget(i18n("Sources"));
    sourcesDock->setObjectName(QStringLiteral("sourcesDock"));
    sourcesDock->setWidget(components->availableSourcesView());

    auto pagesDock = new QDockWidget(i18n("Pages"));
    pagesDock->setObjectName(QStringLiteral("pagesDock"));
    pagesDock->setWidget(components->availablePagesView());

    auto editorDock = new QDockWidget(i18n("Editor"));
    editorDock->setObjectName(QStringLiteral("editorDock"));
    editorDock->setWidget(components->editorView());

    auto window = new KXmlGuiWindow;
    window->setCentralWidget(widget);

    window->addDockWidget(Qt::RightDockWidgetArea, editorDock);
    window->addDockWidget(Qt::LeftDockWidgetArea, pagesDock);
    window->addDockWidget(Qt::LeftDockWidgetArea, sourcesDock);

    auto actions = components->globalActions();
    actions.insert(QStringLiteral("dock_sources"), sourcesDock->toggleViewAction());
    actions.insert(QStringLiteral("dock_pages"), pagesDock->toggleViewAction());
    actions.insert(QStringLiteral("dock_editor"), editorDock->toggleViewAction());

    auto ac = window->actionCollection();
    ac->addAction(KStandardAction::Quit, window, SLOT(close()));
    for (auto it = actions.constBegin(); it != actions.constEnd(); ++it) {
        auto shortcut = it.value()->shortcut();
        if (!shortcut.isEmpty()) {
            ac->setDefaultShortcut(it.value(), shortcut);
        }
        ac->addAction(it.key(), it.value());
    }

    window->setupGUI(QSize(1024, 600),
                     KXmlGuiWindow::ToolBar
                   | KXmlGuiWindow::Keys
                   | KXmlGuiWindow::Save
                   | KXmlGuiWindow::Create);

    delete window->findChild<QAction*>("help_contents");
    delete window->findChild<QAction*>("help_whats_this");

    window->show();

    {
        auto &deps = Utils::DependencyManager::globalInstance();
        auto repo = deps.create<Domain::DataSourceRepository>();
        repo->windowNeedsDataBackend(window);
    }

    return app.exec();
}
