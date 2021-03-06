/*
    This file is part of the Okteta Core library, made within the KDE community.

    Copyright 2004 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#ifndef OKTETA_CHARCODEC_H
#define OKTETA_CHARCODEC_H


// lib
#include <okteta/oktetacore.h>
#include <okteta/oktetacore_export.h>
#include <okteta/byte.h>

class QStringList;
class QChar;


namespace Okteta
{

class Character;


class OKTETACORE_EXPORT CharCodec
{
  public:
    virtual ~CharCodec() {}

  public:
    /** */
    static CharCodec* createCodec( CharCoding charCoding );
    /** */
    static CharCodec* createCodec( const QString& name );

    static const QStringList& codecNames();

  public: // API to be implemented
    virtual Character decode( Byte byte ) const = 0;
    virtual bool encode( Byte* byte, const QChar& _char ) const = 0;
    virtual bool canEncode( const QChar& _char ) const = 0;
    virtual const QString& name() const = 0;
};

}

#endif

