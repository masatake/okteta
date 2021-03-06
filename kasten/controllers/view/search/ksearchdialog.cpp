/*
    This file is part of the Okteta Kasten module, made within the KDE community.

    Copyright 2006-2009 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#include "ksearchdialog.h"

// controller
#include "searchtool.h"
// KF5
#include <KLocalizedString>


namespace Kasten
{

KSearchDialog::KSearchDialog( SearchTool* tool, QWidget* parent )
  : KAbstractFindDialog( parent ),
    mTool( tool )
{
    setWindowTitle( i18nc("@title:window","Find Bytes") );

    setFindButton( i18nc("@action:button","&Find"),
                   QStringLiteral("edit-find"),
                   i18nc("@info:tooltip","Start searching"),
                   xi18nc("@info:whatsthis",
                          "If you press the <interface>Find</interface> button, "
                          "the bytes you entered above are searched for within "
                          "the byte array.") );

    setupFindBox();
    setupOperationBox();
    setupCheckBoxes();

    setFindButtonEnabled( false );
    setModal( false );

    setCharCodec( mTool->charCodingName() );
    connect( mTool,  &SearchTool::charCodecChanged,
             this, &KSearchDialog::setCharCodec );
}


void KSearchDialog::onFindButtonClicked()
{
    hide();

    rememberCurrentSettings();

    mTool->setSearchData( data() );
    mTool->setCaseSensitivity( caseSensitivity() );

    mTool->search( direction(), fromCursor(), inSelection() );
}

void KSearchDialog::showEvent( QShowEvent* showEvent )
{
    KAbstractFindDialog::showEvent( showEvent );

    setInSelection( mTool->hasSelectedData() );
}

KSearchDialog::~KSearchDialog() {}

}
