/*
    This file is part of the Kasten Framework, made within the KDE community.

    Copyright 2009,2012 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#include "documentlistmodel.h"

// lib
#include "documentstool.h"
// Kasten core
#include <kasten/abstractmodelsynchronizer.h>
#include <kasten/abstractdocument.h>
// KF5
#include <KLocalizedString>

#include <QIcon>


namespace Kasten
{

DocumentListModel::DocumentListModel( DocumentsTool* documentsTool, QObject* parent )
 : QAbstractTableModel( parent ),
   mDocumentsTool( documentsTool )
{
    connect( mDocumentsTool, SIGNAL(documentsAdded(QList<Kasten::AbstractDocument*>)),
             SLOT(onDocumentsAdded(QList<Kasten::AbstractDocument*>)) );
    connect( mDocumentsTool, SIGNAL(documentsClosing(QList<Kasten::AbstractDocument*>)),
             SLOT(onDocumentsClosing(QList<Kasten::AbstractDocument*>)) );
    connect( mDocumentsTool, SIGNAL(focussedDocumentChanged(Kasten::AbstractDocument*)),
             SLOT(onFocussedDocumentChanged(Kasten::AbstractDocument*)) );
}

int DocumentListModel::rowCount( const QModelIndex& parent ) const
{
    return (! parent.isValid()) ? mDocumentsTool->documents().size() : 0;
}

int DocumentListModel::columnCount( const QModelIndex& parent ) const
{
    return (! parent.isValid()) ? NoOfColumnIds : 0;
}

QVariant DocumentListModel::data( const QModelIndex& index, int role ) const
{
    QVariant result;

    if( role == Qt::DisplayRole )
    {
        const int documentIndex = index.row();
        const AbstractDocument* document = mDocumentsTool->documents().at( documentIndex );

        const int tableColumn = index.column();
        switch( tableColumn )
        {
            case TitleColumnId:
                result = document->title();
                break;
            default:
                ;
        }
    }
    else if( role == Qt::DecorationRole )
    {
        const int documentIndex = index.row();
        const AbstractDocument* document = mDocumentsTool->documents().at( documentIndex );
        const AbstractModelSynchronizer* synchronizer = document ? document->synchronizer() : 0;

        const int tableColumn = index.column();
        switch( tableColumn )
        {
            case CurrentColumnId:
                if( document == mDocumentsTool->focussedDocument() )
                    result = QIcon::fromTheme( QStringLiteral("arrow-right") );
                break;
            case LocalStateColumnId:
                if( synchronizer && synchronizer->localSyncState() == LocalHasChanges )
                    result = QIcon::fromTheme( QStringLiteral("document-save") );
                break;
            case RemoteStateColumnId:
                // TODO: use static map, syncState int -> iconname
                if( ! synchronizer )
                    result = QIcon::fromTheme( QStringLiteral("document-new") );
                else
                {
                    const RemoteSyncState remoteSyncState = synchronizer->remoteSyncState();
                    if( remoteSyncState == RemoteHasChanges )
                        result = QIcon::fromTheme( QStringLiteral("document-save") );
                    else if( remoteSyncState == RemoteDeleted )
                        result = QIcon::fromTheme( QStringLiteral("edit-delete") );
                    else if( remoteSyncState == RemoteUnknown )
                        result = QIcon::fromTheme( QStringLiteral("flag-yellow") );
                    else if( remoteSyncState == RemoteUnreachable )
                        result = QIcon::fromTheme( QStringLiteral("network-disconnect") );
                }
                break;
            default:
                ;
        }
    }

    return result;
}

QVariant DocumentListModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    QVariant result;

    if( role == Qt::DisplayRole )
    {
        const QString titel =
//             section == LocalStateColumnId ?  i18nc("@title:column Id of the version",         "Id") :
            section == TitleColumnId ?     i18nc("@title:column description of the change", "Title") :
            QString();
        result = titel;
    }
    else if( role == Qt::ToolTipRole )
    {
        const QString titel =
//             section == LocalStateColumnId ?                i18nc("@info:tooltip","Id of the version") :
            section == TitleColumnId ? i18nc("@info:tooltip","Title of the document") :
            QString();
        result = titel;
    }
    else
        result = QAbstractTableModel::headerData( section, orientation, role );

    return result;
}

void DocumentListModel::onFocussedDocumentChanged( AbstractDocument* document )
{
Q_UNUSED( document )

    beginResetModel();
    endResetModel();
// TODO: store current focused document, then only emit for changed
#if 0
    const int oldVersionIndex = mVersionIndex;
    mVersionIndex = versionIndex;

    emit dataChanged( index(versionIndex,CurrentColumnId), index(versionIndex,CurrentColumnId) );
    emit dataChanged( index(oldVersionIndex,CurrentColumnId), index(oldVersionIndex,CurrentColumnId) );
#endif
}

void DocumentListModel::onDocumentsAdded( const QList<Kasten::AbstractDocument*>& documents )
{
    foreach( AbstractDocument* document, documents )
    {
        connect( document, SIGNAL(synchronizerChanged(Kasten::AbstractModelSynchronizer*)),
                 SLOT(onSynchronizerChanged(Kasten::AbstractModelSynchronizer*)) );
        AbstractModelSynchronizer* synchronizer = document->synchronizer();
        if( synchronizer )
        {
            connect( synchronizer, SIGNAL(localSyncStateChanged(Kasten::LocalSyncState)),
                    SLOT(onSyncStatesChanged()) );
            connect( synchronizer, SIGNAL(remoteSyncStateChanged(Kasten::RemoteSyncState)),
                    SLOT(onSyncStatesChanged()) );
        }
    }
    // TODO: try to understand how this whould be done with {begin,end}{Insert,Remove}Columns
    beginResetModel();
    endResetModel();
}

void DocumentListModel::onDocumentsClosing( const QList<Kasten::AbstractDocument*>& documents )
{
Q_UNUSED( documents )
    // TODO: try to understand how this whould be done with {begin,end}{Insert,Remove}Columns
    beginResetModel();
    endResetModel();
}


void DocumentListModel::onSynchronizerChanged( AbstractModelSynchronizer* synchronizer )
{
    // TODO: what about the old synchronizer? assume it is deleted and that way disconnects?
    if( synchronizer )
    {
        connect( synchronizer, SIGNAL(localSyncStateChanged(Kasten::LocalSyncState)),
                 SLOT(onSyncStatesChanged()) );
        connect( synchronizer, SIGNAL(remoteSyncStateChanged(Kasten::RemoteSyncState)),
                 SLOT(onSyncStatesChanged()) );
    }
    // TODO: try to understand how this whould be done with {begin,end}{Insert,Remove}Columns
    beginResetModel();
    endResetModel();
}

void DocumentListModel::onSyncStatesChanged()
{
    // TODO: try to understand how this whould be done with {begin,end}{Insert,Remove}Columns
    beginResetModel();
    endResetModel();
}


DocumentListModel::~DocumentListModel() {}

}
