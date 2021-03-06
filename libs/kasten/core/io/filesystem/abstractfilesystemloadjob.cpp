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

#include "abstractfilesystemloadjob.h"
#include "abstractfilesystemloadjob_p.h"


namespace Kasten
{

AbstractFileSystemLoadJob::AbstractFileSystemLoadJob( AbstractModelFileSystemSynchronizer* synchronizer,
                                                      const QUrl& url )
  : AbstractLoadJob( new AbstractFileSystemLoadJobPrivate(this,synchronizer,url) )
{
}

AbstractModelFileSystemSynchronizer* AbstractFileSystemLoadJob::synchronizer() const
{
    Q_D( const AbstractFileSystemLoadJob );

    return d->synchronizer();
}

QUrl AbstractFileSystemLoadJob::url() const
{
    Q_D( const AbstractFileSystemLoadJob );

    return d->url();
}

QFile* AbstractFileSystemLoadJob::file() const
{
    Q_D( const AbstractFileSystemLoadJob );

    return d->file();
}

void AbstractFileSystemLoadJob::start()
{
    Q_D( AbstractFileSystemLoadJob );

    d->start();
}

void AbstractFileSystemLoadJob::setDocument( AbstractDocument* document )
{
    Q_D( AbstractFileSystemLoadJob );

    d->setDocument( document );
}


AbstractFileSystemLoadJob::~AbstractFileSystemLoadJob()
{
}

}

//have to include this because of Q_PRIVATE_SLOT
#include "moc_abstractfilesystemloadjob.cpp"
