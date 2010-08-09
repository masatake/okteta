/*
 *   This file is part of the Okteta Kasten Framework, part of the KDE project.
 *
 *   Copyright 2009, 2010 Alex Richardson <alex.richardson@gmx.de>
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
#include "abstractarraydatainformation.h"
#include "primitivedatainformation.h"
#include "primitivefactory.h"
#include "../script/scriptvalueconverter.h"

#include <QtScript/QScriptContext>

QString AbstractArrayDataInformation::typeName() const
{
    if (!hasChildren())
        return i18n("Empty array");

    DataInformation* data = childAt(0);
    if (dynamic_cast<PrimitiveDataInformation*> (data))
    {
        //don't show name of child
        return i18nc("array type then length", "%1[%2]", data->typeName(),
                childCount());
    }
    return i18nc("subelem type then array name and length", "%1[%2] (%3)",
            data->name(), childCount(), data->typeName());
}

AbstractArrayDataInformation::AbstractArrayDataInformation(QString name,
        const DataInformation& childType, uint length, int index,
        DataInformation* parent) :
    DataInformationWithChildren(name, index, parent), mChildType(0)
{
    mChildType = childType.clone();
    mChildType->setParent(this);
    for (unsigned int i = 0; i < length; i++)
    {
        DataInformation* arrayElem = childType.clone();
        QObject::connect(arrayElem, SIGNAL(dataChanged()), this,
                SIGNAL(dataChanged()));
        appendChild(arrayElem);
    }
}

AbstractArrayDataInformation::AbstractArrayDataInformation(
        const AbstractArrayDataInformation& d) :
    DataInformationWithChildren(d), mChildType(0)
{
    if (d.mChildType)
        mChildType = d.mChildType->clone();
    mChildType->setParent(this);
}

bool AbstractArrayDataInformation::isDynamicArray() const
{
    //if this array has an update function it must be dynamic
    return mAdditionalData->updateFunction() != NULL;
}

QScriptValue AbstractArrayDataInformation::setArrayLength(int newLength)
{
    //kDebug() << "old child count: " << childCount();

    //arrays with length zero are useless -> minimum is 1 (prevents integer underflow later
    if (newLength < 0)
        return context() ? context()->throwError(
                "new Array length is less than zero: " + QString::number(newLength))
                : QScriptValue();
    if (newLength > 100000)
    {
        kWarning() << "attempting to set the length of the array" << name() << "to "
                << newLength << " which would use too much memory";

        return context() ? context()->throwError("new Array length is to large: "
                + QString::number(newLength)) : QScriptValue();
    }
    int oldLength = childCount();
    if (newLength > oldLength)
    {
        emit childrenAboutToBeInserted(this, oldLength, newLength - 1);
        for (int i = oldLength; i < newLength; ++i)
        {
            DataInformation* arrayElem = mChildType->clone();
            QObject::connect(arrayElem, SIGNAL(dataChanged()), this,
                    SIGNAL(dataChanged()));
            appendChild(arrayElem);
        }
        emit childrenInserted(this, oldLength, newLength - 1);
    }
    else if (newLength < oldLength) //XXX maybe keep some cached
    {
        emit childrenAboutToBeRemoved(this, newLength, oldLength - 1);
        for (int i = newLength; i != mChildren.length();)
        {
            delete mChildren.takeAt(i);
        }
        emit childrenRemoved(this, newLength, oldLength - 1);
    }
    return true; //success
}

QScriptValue AbstractArrayDataInformation::setArrayType(QScriptValue type)
{
    DataInformation* newChildType = NULL;

    //allow type just being a string (it must be a primitive type string)
    if (type.isString())
    {
        newChildType = PrimitiveFactory::newInstance("dummy", type.toString());
    }

    //now just use ScriptValueConverter to see if type is a valid object
    else
    {
        ScriptValueConverter conv(type, "dummy");
        newChildType = conv.convert();
    }
    //return if conversion failed
    if (!newChildType)
    {
        if (context())
            return context()->throwError("String '" + type.toString()
                    + "' is not a valid identifier for a primitive data type");
        else
            return QScriptValue();
    }
    //TODO optimise by checking if newChildType is the same as old child type (only for primitives)
    //childType is valid -> begin changing the children to the new type
    uint len = childCount();
    if (len == 0)
        return true; //do nothing, prevent integer underflow
    emit
    childrenAboutToBeRemoved(this, 0, len - 1);
    qDeleteAll(mChildren);
    mChildren.clear(); //qDeleteAll only uses delete operator, we have to remove from list manually
    childrenRemoved(this, 0, len - 1);

    mChildType = newChildType;
    mChildType->setParent(this);

    emit
    childrenAboutToBeInserted(this, 0, len - 1);
    for (uint i = 0; i < len; i++)
    {
        DataInformation* arrayElem = newChildType->clone();
        QObject::connect(arrayElem, SIGNAL(dataChanged()), this,
                SIGNAL(dataChanged()));
        appendChild(arrayElem);
    }emit
    childrenInserted(this, 0, len - 1);
    return true; //success
}

QScriptValue AbstractArrayDataInformation::childType() const
{
    if (mChildType)
        return mChildType->typeName().toLower();
    return QString();
}

AbstractArrayDataInformation::~AbstractArrayDataInformation()
{
}
