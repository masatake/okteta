/*
    This file is part of the Kasten Framework, made within the KDE community.

    Copyright 2008-2009,2011 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#include "abstractfilesystemsyncwithremotejob.h"
#include "abstractfilesystemsyncwithremotejob_p.h"


namespace Kasten
{

AbstractFileSystemSyncWithRemoteJob::AbstractFileSystemSyncWithRemoteJob( AbstractModelFileSystemSynchronizer* synchronizer,
                                         const QUrl& url, AbstractModelSynchronizer::ConnectOption option )
  : AbstractSyncWithRemoteJob( new AbstractFileSystemSyncWithRemoteJobPrivate(this,synchronizer,url,option) )
{}

AbstractModelFileSystemSynchronizer* AbstractFileSystemSyncWithRemoteJob::synchronizer() const
{
    Q_D( const AbstractFileSystemSyncWithRemoteJob );

    return d->synchronizer();
}
QFile* AbstractFileSystemSyncWithRemoteJob::file() const
{
    Q_D( const AbstractFileSystemSyncWithRemoteJob );

    return d->file();
}

void AbstractFileSystemSyncWithRemoteJob::start()
{
    Q_D( AbstractFileSystemSyncWithRemoteJob );

    d->start();
}

void AbstractFileSystemSyncWithRemoteJob::completeSync( bool success )
{
    Q_D( AbstractFileSystemSyncWithRemoteJob );

    d->completeSync( success );
}

AbstractFileSystemSyncWithRemoteJob::~AbstractFileSystemSyncWithRemoteJob()
{
}

}

//have to include this because of Q_PRIVATE_SLOT
#include "moc_abstractfilesystemsyncwithremotejob.cpp"
