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

#include "sint32editor.h"

// C++
#include <limits>


SInt32Editor::SInt32Editor( QWidget* parent )
  : QSpinBox( parent )
{
    const qint32 int32Max = std::numeric_limits<qint32>::max();
    const qint32 int32Min = std::numeric_limits<qint32>::min();

    setRange( int32Min, int32Max );
}

void SInt32Editor::setData( SInt32 data )
{
    setValue( data.value );
}

SInt32 SInt32Editor::data() const
{
//     interpretText();
    return value();
}

SInt32Editor::~SInt32Editor() {}
