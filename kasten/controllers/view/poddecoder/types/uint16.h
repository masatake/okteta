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

#ifndef UINT16_H
#define UINT16_H

// Qt
#include <QtCore/QMetaType>
#include <QtCore/QString>


struct UInt16
{
  public:
    UInt16( quint16 v );
    UInt16();

  public:
    QString toString( bool asHex ) const;

  public:
    quint16 value;
};


inline UInt16::UInt16() : value( 0 ) {}
inline UInt16::UInt16( quint16 v ) : value( v ) {}

inline QString UInt16::toString( bool asHex ) const
{
    return asHex ? QString::fromLatin1( "0x%1" ).arg( value, 4, 16, QChar::fromLatin1('0') ) :
                   QString::number( value );
}

Q_DECLARE_METATYPE( UInt16 )

#endif
