/*
    This file is part of the Okteta Core library, made within the KDE community.

    Copyright 2006,2011 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#ifndef CHARCODECIFTEST_H
#define CHARCODECIFTEST_H

// Qt
#include <QObject>


namespace Okteta
{
class CharCodec;


class CharCodecIfTest : public QObject
{
  Q_OBJECT

  protected:
    CharCodecIfTest();

  protected: // API to be implemented
    virtual CharCodec* createCodec() = 0;
    virtual void deleteCodec( CharCodec* codec ) = 0;

  private Q_SLOTS: // test functions
    void init();
    void cleanup();

    void testEncodeDecode_data();
    void testEncodeDecode();

  private:
    /** pointer to the buffer to test */
    CharCodec* mCharCodec;
};


inline CharCodecIfTest::CharCodecIfTest() : mCharCodec( 0 ) {}

}

#endif
