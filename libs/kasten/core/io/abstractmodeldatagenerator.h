/*
    This file is part of the Kasten Framework, made within the KDE community.

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

#ifndef ABSTRACTMODELDATAGENERATOR_H
#define ABSTRACTMODELDATAGENERATOR_H

// lib
#include <kasten/kastencore_export.h>
// Qt
#include <QObject>
#include <QString>

class QMimeData;


namespace Kasten
{

class AbstractModelDataGeneratorPrivate;


class KASTENCORE_EXPORT AbstractModelDataGenerator : public QObject
{
  Q_OBJECT

  public:
    enum Flags { StaticGeneration, DynamicGeneration };

  protected:
    AbstractModelDataGenerator( AbstractModelDataGeneratorPrivate* d );

  public:
    AbstractModelDataGenerator( const QString& typeName, const QString& mimeType, Flags flags );

    virtual ~AbstractModelDataGenerator();

  public: // API to be implemented
    virtual QMimeData* generateData() = 0;

  public:
    QString typeName() const;
    QString mimeType() const;
    Flags flags() const;

  protected:
    Q_DECLARE_PRIVATE( AbstractModelDataGenerator )
  protected:
    AbstractModelDataGeneratorPrivate* const d_ptr;
};

}

#endif
