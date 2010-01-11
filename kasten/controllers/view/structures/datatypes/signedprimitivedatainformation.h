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
#ifndef SIGNEDPRIMITIVEDATAINFORMATION_H_
#define SIGNEDPRIMITIVEDATAINFORMATION_H_

#include "primitivedatainformation.h"

class SignedPrimitiveDataInformation: public PrimitiveDataInformation
{
PRIMITIVEDATAINFORMATION_SUBCLASS_CONSTRUCTORS(SignedPrimitive,Primitive)
protected:
    QString correctSignedValue(QString& num, int base) const;
public:
    virtual inline int displayBase() const
    {
        int base = Kasten::StructViewPreferences::signedDisplayBase();
        if (base == Kasten::StructViewPreferences::EnumSignedDisplayBase::Binary)
        {
            return 2;
        }
        if (base == Kasten::StructViewPreferences::EnumSignedDisplayBase::Decimal)
        {
            return 10;
        }
        if (base
                == Kasten::StructViewPreferences::EnumSignedDisplayBase::Hexadecimal)
        {
            return 16;
        }
        return 10; //safe default value
    }
    virtual QVariant dataFromWidget(const QWidget* w) const;
};

#endif /* SIGNEDPRIMITIVEDATAINFORMATION_H_ */