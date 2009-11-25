/*
 *   This file is part of the Okteta Kasten module, part of the KDE project.
 *
 *   Copyright 2009 Alex Richardson <alex.richardson@gmx.de>
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) version 3, or any
 *   later version accepted by the membership of KDE e.V. (or its
 *   successor approved by the membership of KDE e.V.), which shall
 *   act as a proxy defined in Section 6 of version 3 of the license.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef UINT16DATAINFORMATION_H_
#define UINT16DATAINFORMATION_H_

#include "unsignedprimitivedatainformation.h"

class UInt16DataInformation: public UnsignedPrimitiveDataInformation
{
PRIMITIVEDATAINFORMATION_SUBCLASS_CONSTURUCTORS(UInt16,UnsignedPrimitive)
public:
    inline int getSize() const
    {
        return 16;
    }
    inline QString getTypeName() const
    {
        return i18nc("Data type", "unsigned short");
    }
    DATAINFORMATION_CLONE(UInt16)
    virtual QString getValueString() const;
};

#endif /* UINT16DATAINFORMATION_H_ */