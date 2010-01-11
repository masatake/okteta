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

#include "structtreemodel.h"
#include "structtool.h"
#include "datatypes/dynamiclengtharraydatainformation.h"

namespace Kasten
{
StructTreeModel::StructTreeModel(StructTool* tool, QObject *parent) :
    QAbstractItemModel(parent), mTool(tool)
{
    connect(mTool, SIGNAL(dataChanged()), this, SLOT(onToolDataChange()));
    connect(mTool, SIGNAL(dataCleared()), this, SLOT(onToolDataClear()));
}

StructTreeModel::~StructTreeModel()
{
}
void StructTreeModel::onDataInformationChildCountChange(int oldCount, int newCount)
{
    Q_UNUSED(oldCount)
    Q_UNUSED(newCount)
    reset(); // TODO terribly inefficient, but i can't think of a better solution to prevent
    //crash on child count change
}

int StructTreeModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return mTool->columnCount();
}

QVariant StructTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    DataInformation *item = static_cast<DataInformation*> (index.internalPointer());
    if (!item)
    {
        kDebug() << "item is NULL";
        return QVariant();
    }
    const int column = index.column();
    if (role == Qt::FontRole)
    {
        if (column == 0 && item->parent() == 0)
        {
            // TODO: ideally here we would not take the default application font
            // (as given by QFont()) but the default of the view
            QFont font;
            font.setBold(true);
            return font;
        }
        else
            return QVariant();
    }
    else
        return item->data(column, role);
}
bool StructTreeModel::setData(const QModelIndex& index, const QVariant& value,
        int role)
{
    if (!index.isValid())
        return false;

    DataInformation *item = static_cast<DataInformation*> (index.internalPointer());
    if (!item)
        return false;
    bool change = mTool->setData(value, role, item);
    return change;
}

Qt::ItemFlags StructTreeModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return 0;
    DataInformation *item = static_cast<DataInformation*> (index.internalPointer());
    return mTool->flags(index.column(), item);
}

QVariant StructTreeModel::headerData(int section, Qt::Orientation orientation,
        int role) const
{
    if (orientation == Qt::Horizontal)
    {
        return mTool->headerData(section, role);
    }
    return QVariant();
}

QModelIndex StructTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    DataInformation *childItem;

    if (!parent.isValid())
        childItem = mTool->childAt(row);
    else
    {
        DataInformation* parentItem =
                static_cast<DataInformation*> (parent.internalPointer());
        if (!parentItem)
        {
            kDebug() << "parent item is NULL";
            return QModelIndex();
        }
        childItem = parentItem->childAt(row);
    }
    if (childItem)
    {
        if (dynamic_cast<DynamicLengthArrayDataInformation*> (childItem))
        {
            connect(childItem, SIGNAL(childCountChange(int,int)), this,
                    SLOT(onDataInformationChildCountChange(int,int)));
        }
        return createIndex(row, column, childItem);
    }
    else
        return QModelIndex();
}

QModelIndex StructTreeModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    DataInformation *childItem =
            static_cast<DataInformation*> (index.internalPointer());
    if (!childItem)
    {
        kDebug() << "childitem == NULL";
        return QModelIndex();
    }
    DataInformation *parentItem =
            static_cast<DataInformation*> (childItem->parent());
    if (!parentItem)
        return QModelIndex();

    if (dynamic_cast<DynamicLengthArrayDataInformation*> (parentItem))
    {
        connect(parentItem, SIGNAL(childCountChange(int,int)), this,
                SLOT(onDataInformationChildCountChange(int,int)));
    }
    return createIndex(parentItem->row(), 0, parentItem);
}

int StructTreeModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid())
        return mTool->childCount();
    DataInformation* parentItem =
            static_cast<DataInformation*> (parent.internalPointer());
    if (!parentItem)
    {
        kDebug() << "parentItem is NULL";
        return mTool->childCount();
    }
    return parentItem->childCount();
}

}