/*
    This file is part of the Kasten Framework, made within the KDE community.

    Copyright 2007-2009 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#include "abstractmodelfilesystemsynchronizer_p.h"

// KF5
#include <KDirWatch>
// Qt
#include <QNetworkConfigurationManager>


namespace Kasten
{

void AbstractModelFileSystemSynchronizerPrivate::startFileWatching()
{
    Q_Q( AbstractModelFileSystemSynchronizer );

    if( ! mDirWatch )
    {
        mDirWatch = new KDirWatch( q );
        QObject::connect( mDirWatch, SIGNAL(dirty(QString)),
            q, SLOT(onFileDirty(QString)) );

        QObject::connect( mDirWatch, SIGNAL(created(QString)),
            q, SLOT(onFileCreated(QString)) );

        QObject::connect( mDirWatch, SIGNAL(deleted(QString)),
            q, SLOT(onFileDeleted(QString)) );
    }

    mDirWatch->addFile( mUrl.toLocalFile() );
}

void AbstractModelFileSystemSynchronizerPrivate::stopFileWatching()
{
    if( ! mDirWatch )
        return;

    mDirWatch->removeFile( mUrl.toLocalFile() );
}

void AbstractModelFileSystemSynchronizerPrivate::pauseFileWatching()
{
    if( ! mDirWatch )
        return;

    mDirWatch->stopScan();
}

void AbstractModelFileSystemSynchronizerPrivate::unpauseFileWatching()
{
    if( ! mDirWatch )
        return;

    mDirWatch->startScan();
}

void AbstractModelFileSystemSynchronizerPrivate::startNetworkWatching()
{
    Q_Q( AbstractModelFileSystemSynchronizer );

    mNetworkConfigurationManager = new QNetworkConfigurationManager();
    q->connect( mNetworkConfigurationManager, SIGNAL(onlineStateChanged(bool)), SLOT(onOnlineStateChanged(bool)) );
}
void AbstractModelFileSystemSynchronizerPrivate::stopNetworkWatching()
{
    delete mNetworkConfigurationManager;
    mNetworkConfigurationManager = 0;
}

void AbstractModelFileSystemSynchronizerPrivate::onFileDirty( const QString& fileName )
{
    Q_UNUSED( fileName )
    qCDebug(LOG_KASTEN_CORE) << fileName;
    setRemoteState( RemoteHasChanges );
}

void AbstractModelFileSystemSynchronizerPrivate::onFileCreated( const QString& fileName )
{
    Q_UNUSED( fileName )
    qCDebug(LOG_KASTEN_CORE) << fileName;
    //TODO: could happen after a delete, what to do?
    setRemoteState( RemoteHasChanges );
}

void AbstractModelFileSystemSynchronizerPrivate::onFileDeleted( const QString& fileName )
{
    Q_UNUSED( fileName )
    qCDebug(LOG_KASTEN_CORE) << fileName;
    setRemoteState( RemoteDeleted );
}

void AbstractModelFileSystemSynchronizerPrivate::onOnlineStateChanged( bool isOnline )
{
    qCDebug(LOG_KASTEN_CORE);
    setRemoteState( isOnline ? RemoteUnknown : RemoteUnreachable );
}

AbstractModelFileSystemSynchronizerPrivate::~AbstractModelFileSystemSynchronizerPrivate()
{
    delete mNetworkConfigurationManager;
}

}
