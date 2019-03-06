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

#include <testlib/qtest_zanshin.h>

#include <KConfig>
#include <KConfigGroup>
#include <KSharedConfig>

#include "akonadi/akonadistoragesettings.h"

using namespace Akonadi;

Q_DECLARE_METATYPE(QSet<Akonadi::Collection::Id>)

class AkonadiStorageSettingsTest : public QObject
{
    Q_OBJECT
public:
    explicit AkonadiStorageSettingsTest(QObject *parent = nullptr)
        : QObject(parent)
    {
        qRegisterMetaType<Akonadi::Collection>();
        qRegisterMetaType<Akonadi::Collection::List>();
        qRegisterMetaType<QSet<Akonadi::Collection::Id>>();
    }

private:
    KConfigGroup configGroup()
    {
        return KConfigGroup(KSharedConfig::openConfig(), "General");
    }

    QList<Akonadi::Collection::Id> idList(int max)
    {
        QList<Akonadi::Collection::Id> list;
        list.reserve(max);
        for (int i = 1; i < max; i++) {
            list << i;
        }
        return list;
    }

    Akonadi::Collection::List colList(int max)
    {
        Akonadi::Collection::List list;
        list.reserve(max);
        foreach (auto id, idList(max)) {
            list << Collection(id);
        }
        return list;
    }

private slots:
    void shouldReadFromConfigurationFile()
    {
        // GIVEN

        KConfigGroup g = configGroup();

        for (int i = 1; i <= 18; i += 3) {
            // WHEN
            g.writeEntry("defaultCollection", i);

            // THEN
            QCOMPARE(StorageSettings::instance().defaultCollection(), Collection(i));
        }
    }

    void shouldWriteToConfigurationFile()
    {
        // GIVEN

        KConfigGroup g = configGroup();

        for (int i = 1; i <= 18; i += 3) {
            // WHEN
            StorageSettings::instance().setDefaultCollection(Collection(i));

            // THEN
            QCOMPARE(g.readEntry("defaultCollection", -1), i);
        }
    }

    void shouldNotifyTaskCollectionChanges()
    {
        StorageSettings &settings = StorageSettings::instance();
        QSignalSpy spy(&settings, &Akonadi::StorageSettings::defaultCollectionChanged);
        settings.setDefaultCollection(Collection(2));
        QCOMPARE(spy.count(), 1);
        QCOMPARE(spy.first().first().value<Collection>(), Collection(2));
    }

    void shouldNotNotifyIdenticalTaskCollectionChanges()
    {
        StorageSettings &settings = StorageSettings::instance();
        settings.setDefaultCollection(Collection(4));
        QSignalSpy spy(&settings, &Akonadi::StorageSettings::defaultCollectionChanged);
        settings.setDefaultCollection(Collection(4));
        QCOMPARE(spy.count(), 0);
    }
};

ZANSHIN_TEST_MAIN(AkonadiStorageSettingsTest)

#include "akonadistoragesettingstest.moc"
