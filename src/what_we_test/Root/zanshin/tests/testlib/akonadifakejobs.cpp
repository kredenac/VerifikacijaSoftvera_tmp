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

#include "akonadifakejobs.h"

#include <KCalCore/Todo>

#include <QTimer>

using namespace Testlib;

void AkonadiFakeCollectionFetchJob::setCollections(const Akonadi::Collection::List &collections)
{
    m_collections = collections;
}

Akonadi::Collection::List AkonadiFakeCollectionFetchJob::collections() const
{
    auto result = isDone() ? m_collections : Akonadi::Collection::List();

    if (m_resource.isEmpty()) {
        auto it = std::remove_if(result.begin(), result.end(),
                                 [] (const Akonadi::Collection &col) {
                                     const auto mime = col.contentMimeTypes();
                                     return !mime.contains(KCalCore::Todo::todoMimeType());
                                 });
        result.erase(it, std::end(result));
    }

    return result;
}

QString AkonadiFakeCollectionFetchJob::resource() const
{
    return m_resource;
}

void AkonadiFakeCollectionFetchJob::setResource(const QString &resource)
{
    m_resource = resource;
}

void AkonadiFakeItemFetchJob::setItems(const Akonadi::Item::List &items)
{
    m_items = items;
}

Akonadi::Item::List AkonadiFakeItemFetchJob::items() const
{
    if (expectedError() != KJob::NoError)
        return m_items;

    return isDone() ? m_items : Akonadi::Item::List();
}

Akonadi::Collection AkonadiFakeItemFetchJob::collection() const
{
    return m_collection;
}

void AkonadiFakeItemFetchJob::setCollection(const Akonadi::Collection &collection)
{
    m_collection = collection;
}

