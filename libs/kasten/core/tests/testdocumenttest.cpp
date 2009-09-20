/*
    This file is part of the Kasten Framework, part of the KDE project.

    Copyright 2007 Friedrich W. H. Kossebau <kossebau@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library. If not, see <http://www.gnu.org/licenses/>.
*/

#include "testdocumenttest.h"

// test object
#include <testdocument.h>
// Qt
#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>

static const char TestData[] = "TestData";


void TestDocumentTest::checkTitleChanged( QSignalSpy* titleChangedSpy, const QString &title )
{
   QVERIFY( titleChangedSpy->isValid() );
   QCOMPARE( titleChangedSpy->count(), 1 );
   QList<QVariant> arguments = titleChangedSpy->takeFirst();
   QCOMPARE( arguments.at(0).toString(), title );
}

Q_DECLARE_METATYPE ( Kasten::AbstractDocument::SyncStates )

void TestDocumentTest::checkSyncStatesChanged( QSignalSpy* changedSpy, Kasten::AbstractDocument::SyncStates states )
{
   QVERIFY( changedSpy->isValid() );
   QCOMPARE( changedSpy->count(), 1 );
   QList<QVariant> arguments = changedSpy->takeFirst();
   QCOMPARE( arguments.at(0).value<Kasten::AbstractDocument::SyncStates>(), states );
}


// ------------------------------------------------------------------ tests ----

void TestDocumentTest::testPlainConstructor()
{
    Kasten::TestDocument* document = new Kasten::TestDocument();

    QVERIFY( document != 0 );
    QCOMPARE( *document->data(), QByteArray() );
    QCOMPARE( document->title(), QString() );
    QCOMPARE( document->syncStates(), Kasten::TestDocument::InSync );

    delete document;
}

void TestDocumentTest::testDataConstructor()
{
    const QByteArray testData( TestData );
    Kasten::TestDocument* document = new Kasten::TestDocument( testData );

    QVERIFY( document != 0 );
    QCOMPARE( *document->data(), testData );
    QCOMPARE( document->title(), QString() );
    QCOMPARE( document->syncStates(), Kasten::TestDocument::InSync );

    delete document;
}

void TestDocumentTest::testChangeData()
{
    qRegisterMetaType<Kasten::AbstractDocument::SyncStates>("Kasten::AbstractDocument::SyncStates");
    const QByteArray testData( TestData );

    Kasten::TestDocument* document = new Kasten::TestDocument();

    QSignalSpy* changedSpy = new QSignalSpy( document, SIGNAL(syncStatesChanged( Kasten::AbstractDocument::SyncStates )) );

    QCOMPARE( *document->data(), QByteArray() );
    QCOMPARE( document->syncStates(), Kasten::TestDocument::InSync );

    document->setData( testData );

    const Kasten::AbstractDocument::SyncStates states( Kasten::AbstractDocument::LocalHasChanges );
    QCOMPARE( *document->data(), testData );
    QCOMPARE( document->syncStates(), states );
    checkSyncStatesChanged( changedSpy, states );

    delete document;
    delete changedSpy;
}

void TestDocumentTest::testSetTitle()
{
    Kasten::TestDocument* document = new Kasten::TestDocument();

    QSignalSpy* titleChangedSpy = new QSignalSpy( document, SIGNAL(titleChanged(QString)) );

    const QLatin1String title( "title" );
    document->setTitle( title );

    QCOMPARE( document->title(), title );
    QCOMPARE( document->syncStates(), Kasten::TestDocument::InSync );
    checkTitleChanged( titleChangedSpy, title );

    delete document;
    delete titleChangedSpy;
}

void TestDocumentTest::testSetSyncStates()
{
    qRegisterMetaType<Kasten::AbstractDocument::SyncStates>("Kasten::AbstractDocument::SyncStates");

    Kasten::TestDocument* document = new Kasten::TestDocument();

    QSignalSpy* changedSpy = new QSignalSpy( document, SIGNAL(syncStatesChanged( Kasten::AbstractDocument::SyncStates )) );

    const Kasten::AbstractDocument::SyncStates
        states( Kasten::AbstractDocument::LocalHasChanges | Kasten::AbstractDocument::RemoteUnknown );
    document->setSyncStates( states );

    QCOMPARE( document->title(), QString() );
    QCOMPARE( document->syncStates(), states );
    checkSyncStatesChanged( changedSpy, states );

    delete document;
    delete changedSpy;
}

QTEST_MAIN( TestDocumentTest )