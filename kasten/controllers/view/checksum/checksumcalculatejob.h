/*
    This file is part of the Okteta Kasten module, part of the KDE project.

    Copyright 2009 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#ifndef CHECKSUMCALCULATEJOB_H
#define CHECKSUMCALCULATEJOB_H

// Okteta core
#include <addressrange.h>
// Qt
#include <QtCore/QObject>

class AbstractByteArrayChecksumAlgorithm;

namespace Okteta {
class AbstractByteArrayModel;
}


namespace Kasten
{

class ChecksumCalculateJob : public QObject // not yet: KJob
{
  Q_OBJECT

  public:
    ChecksumCalculateJob( QString* checksum,
                          const AbstractByteArrayChecksumAlgorithm* algorithm,
                          const Okteta::AbstractByteArrayModel* model,
                          const Okteta::AddressRange& selection );

  public:
    void exec();

  protected Q_SLOTS:
    void onCalculatedBytes();

  protected:
    QString* mChecksum;

    const AbstractByteArrayChecksumAlgorithm* mAlgorithm;

    const Okteta::AbstractByteArrayModel* mByteArrayModel;
    const Okteta::AddressRange mSelection;
};


inline ChecksumCalculateJob::ChecksumCalculateJob( QString* checksum,
                                                   const AbstractByteArrayChecksumAlgorithm* algorithm,
                                                   const Okteta::AbstractByteArrayModel* model,
                                                   const Okteta::AddressRange& selection )
 : mChecksum( checksum ), mAlgorithm( algorithm ), mByteArrayModel( model ), mSelection( selection )
{}

}

#endif