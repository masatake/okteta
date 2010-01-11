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

#include "structviewitemdelegate.h"
#include "datatypes/datainformation.h"
#include <QLineEdit>
#include <KDebug>

StructViewItemDelegate::StructViewItemDelegate(QObject * parent) :
    QStyledItemDelegate(parent)
{
}

StructViewItemDelegate::~StructViewItemDelegate()
{
}

QWidget * StructViewItemDelegate::createEditor(QWidget * parent,
        const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    Q_UNUSED(option)
    if (!index.isValid())
        return new QWidget();
    DataInformation* data = static_cast<DataInformation*> (index.internalPointer());
    if (!data)
        return NULL;
    QWidget* ret = data->createEditWidget(parent);
    ret->setFocusPolicy(Qt::WheelFocus);
    return ret;
}

void StructViewItemDelegate::setModelData(QWidget * editor,
        QAbstractItemModel * model, const QModelIndex & index) const
{
    if (!index.isValid())
        return;
    DataInformation* data = static_cast<DataInformation*> (index.internalPointer());
    QVariant value = data->dataFromWidget(editor);
    model->setData(index, value, Qt::EditRole);
}

void StructViewItemDelegate::setEditorData(QWidget * editor,
        const QModelIndex & index) const
{

    if (!index.isValid())
        return;
    DataInformation* data = static_cast<DataInformation*> (index.internalPointer());
    data->setWidgetData(editor);
}

QSize StructViewItemDelegate::sizeHint(const QStyleOptionViewItem & option,
        const QModelIndex & index) const
{
    Q_UNUSED(option)
    if (!index.isValid()) {
        kDebug() << "invalid index";
        return QSize();
    }
    DataInformation* data = static_cast<DataInformation*> (index.internalPointer());
    if (!data) {
        kDebug() << "data == NULL";
        return QSize();
    }
    QWidget* ret = data->createEditWidget(NULL);
    return ret->sizeHint();
}