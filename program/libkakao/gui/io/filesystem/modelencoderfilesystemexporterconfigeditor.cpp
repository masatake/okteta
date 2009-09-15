/*
    This file is part of the Kakao Framework, part of the KDE project.

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

#include "modelencoderfilesystemexporterconfigeditor.h"

// lib
#include <abstractmodelstreamencoderconfigeditor.h>
// Qt
#include <QtGui/QLayout>


ModelEncoderFileSystemExporterConfigEditor::ModelEncoderFileSystemExporterConfigEditor( AbstractModelStreamEncoderConfigEditor* encoderConfigEditor )
 : mEncoderConfigEditor( encoderConfigEditor )
{
    QHBoxLayout* layout = new QHBoxLayout( this );
    layout->setSpacing( 0 );
    layout->addWidget( mEncoderConfigEditor );
}

bool ModelEncoderFileSystemExporterConfigEditor::isValid() const
{
    return mEncoderConfigEditor->isValid();
}

QString ModelEncoderFileSystemExporterConfigEditor::name() const
{
    return mEncoderConfigEditor->name();
}

AbstractSelectionView* ModelEncoderFileSystemExporterConfigEditor::createPreviewView() const
{
    return mEncoderConfigEditor->createPreviewView();
}

ModelEncoderFileSystemExporterConfigEditor::~ModelEncoderFileSystemExporterConfigEditor()
{
    delete mEncoderConfigEditor;
}