/* This file is part of Zanshin

   Copyright 2019 Kevin Ottens <ervin@kde.org>
   Copyright 2019 David Faure <faure@kde.org>

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
#include <featurelib/zanshincontext.h>

using namespace Testlib;

// Feature: Modifying a task's due date
// As someone adding a task
// I can set the due date by editing the field "due date"
// In order to have a task that ends at the entered date
class WorkdayDuedateEditFeature : public QObject
{
    Q_OBJECT
private slots:
    void Setting_a_date_s_due_date_to_today_makes_it_appear_in_the_Workday_page()
    {
        ZanshinContext c;
        Given(c.I_display_the_page("Inbox"));
        And(c.I_add_a_task("Make more test tasks"));
        And(c.there_is_an_item_in_the_central_list("Make more test tasks"));
        When(c.I_open_the_item_in_the_editor());
        And(c.I_change_the_editor_field("due date", "2015-03-10"));
        And(c.I_display_the_page("Workday"));
        And(c.I_look_at_the_central_list());
        And(c.I_list_the_items());
        Then(c.the_list_contains("Make more test tasks"));
    }

    void Setting_a_date_s_due_date_to_a_date_in_the_past_makes_it_appear_in_the_Workday_page()
    {
        ZanshinContext c;
        Given(c.I_display_the_page("Inbox"));
        And(c.I_add_a_task("Buy potatoes"));
        And(c.there_is_an_item_in_the_central_list("Buy potatoes"));
        When(c.I_open_the_item_in_the_editor());
        And(c.I_change_the_editor_field("due date", "2001-03-10"));
        And(c.I_display_the_page("Workday"));
        And(c.I_look_at_the_central_list());
        And(c.I_list_the_items());
        Then(c.the_list_contains("Buy potatoes"));
    }
};

ZANSHIN_TEST_MAIN(WorkdayDuedateEditFeature)

#include "workdayduedateeditfeature.moc"
