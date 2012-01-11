/*
 *   This file is part of the Okteta Kasten Framework, made within the KDE community.
 *
 *   Copyright 2010, 2011 Alex Richardson <alex.richardson@gmx.de>
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

#ifndef ABSTRACTSTRUCTUREPARSER_H_
#define ABSTRACTSTRUCTUREPARSER_H_

#include <QtCore/QList>
#include <QtCore/QStringList>

#include "../datatypes/primitive/enumdefinition.h"
#include "../datatypes/datainformation.h"

class TopLevelDataInformation;
namespace Kasten2
{
class StructureDefinitionFile;
}

class AbstractStructureParser
{
public:
    AbstractStructureParser(const Kasten2::StructureDefinitionFile* const def);
    virtual ~AbstractStructureParser();

    virtual QStringList parseStructureNames() = 0;
    virtual QList<const TopLevelDataInformation*> parseStructures() = 0;
    virtual bool isFullyParsed() const = 0;
    static DataInformation::DataInformationEndianess byteOrderFromString(const QString& string);

protected:
    const Kasten2::StructureDefinitionFile* const mDef;
private:
    Q_DISABLE_COPY(AbstractStructureParser)
};

#endif /* ABSTRACTSTRUCTUREPARSER_H_ */
