/*
    This file is part of the Kasten Framework, made within the KDE community.

    Copyright 2008 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#ifndef BYTEARRAYSOURCECODESTREAMENCODERCONFIGEDITOR_H
#define BYTEARRAYSOURCECODESTREAMENCODERCONFIGEDITOR_H

// lib
#include "bytearraysourcecodestreamencoder.h"
// Kasten gui
#include <kasten/abstractmodelstreamencoderconfigeditor.h>

class KLineEdit;
class KComboBox;
class QSpinBox;
class QCheckBox;


namespace Kasten
{

class ByteArraySourceCodeStreamEncoderConfigEditor : public AbstractModelStreamEncoderConfigEditor
{
  Q_OBJECT

  public:
    explicit ByteArraySourceCodeStreamEncoderConfigEditor( ByteArraySourceCodeStreamEncoder* encoder, QWidget* parent = 0 );
    virtual ~ByteArraySourceCodeStreamEncoderConfigEditor();

  public: // AbstractModelStreamEncoderConfigEditor API
    virtual bool isValid() const;
    virtual AbstractSelectionView* createPreviewView() const;

  protected Q_SLOTS:
    void onSettingsChanged();

  protected:
    ByteArraySourceCodeStreamEncoder* mEncoder;
    SourceCodeStreamEncoderSettings mSettings;

    KLineEdit* mVariableNameEdit;
    QSpinBox* mItemsPerLineEdit;
    KComboBox* mDataTypeSelect;
    QCheckBox* mUnsignedAsHexadecimalCheck;
};

}

#endif
