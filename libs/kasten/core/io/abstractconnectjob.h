/*
    This file is part of the Kasten Framework, made within the KDE community.

    Copyright 2008-2009 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#ifndef ABSTRACTCONNECTJOB_H
#define ABSTRACTCONNECTJOB_H

// lib
#include <kasten/kastencore_export.h>
// KF5
#include <KJob>


namespace Kasten
{

class AbstractConnectJobPrivate;


class KASTENCORE_EXPORT AbstractConnectJob : public KJob
{
  Q_OBJECT

  protected:
    explicit AbstractConnectJob( AbstractConnectJobPrivate* d );

  public:
    AbstractConnectJob();

    virtual ~AbstractConnectJob();

  protected:
    // emits documentLoaded()
    // TODO: or better name property LoadedDocument?

  protected:
    AbstractConnectJobPrivate* const d_ptr;
};

}

#endif
