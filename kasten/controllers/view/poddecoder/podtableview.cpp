/*
    This file is part of the Okteta Kasten module, part of the KDE project.

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

#include "podtableview.h"

// controller
#include "podtablemodel.h"
#include "poddelegate.h"
#include "poddecodertool.h"
// KDE
#include <KComboBox>
#include <KLocale>
// Qt
#include <QtGui/QLabel>
#include <QtGui/QLayout>
#include <QtGui/QCheckBox>
#include <QtGui/QTreeView>
#include <QtGui/QHeaderView>
#include <QtGui/QFocusEvent>


namespace Kasten
{

PODTableView::PODTableView( PODDecoderTool* tool, QWidget* parent )
 : QWidget( parent ), mTool( tool )
{
    QBoxLayout* baseLayout = new QVBoxLayout( this );
    baseLayout->setMargin( 0 );

    // table
    mPODTableModel = new PODTableModel( mTool, this );
    mPODTableView = new QTreeView( this );
    mPODTableView->setObjectName( "PODTable" );
    mPODTableView->setRootIsDecorated( false );
    mPODTableView->setAlternatingRowColors( true );
    mPODTableView->setItemsExpandable( false );
    mPODTableView->setUniformRowHeights( true );
    mPODTableView->setAllColumnsShowFocus( true );
    mPODTableView->setItemDelegate( new PODDelegate(mTool) );
//     mPODTableView->setEditTriggers( QAbstractItemView::AllEditTriggers );
    mPODTableView->setDragEnabled( true );
    mPODTableView->setSortingEnabled( false );
    mPODTableView->setModel( mPODTableModel );
    mPODTableView->installEventFilter( this );
    QHeaderView* header = mPODTableView->header();
    header->setResizeMode( QHeaderView::ResizeToContents );
    header->setStretchLastSection( false );
//     connect( mPODTableView, SIGNAL(doubleClicked( const QModelIndex& )),
//              SLOT(onDoubleClicked( const QModelIndex& )) );
    connect( mPODTableView->selectionModel(),
             SIGNAL(currentRowChanged( const QModelIndex&, const QModelIndex& )),
             SLOT(onCurrentRowChanged( const QModelIndex&, const QModelIndex& )) );

    baseLayout->addWidget( mPODTableView, 10 );

    // settings
    QBoxLayout *settingsLayout = new QHBoxLayout();
    settingsLayout->setMargin( 0 );

    mByteOrderSelection = new KComboBox( this );
    mByteOrderSelection->addItem( i18nc("@item:inlistbox","Little-endian") ); // add first for index
    mByteOrderSelection->addItem( i18nc("@item:inlistbox","Big-endian") );    // add second for index
    mByteOrderSelection->setCurrentIndex( mTool->byteOrder() );
    connect( mByteOrderSelection, SIGNAL(activated( int )),
             mTool, SLOT(setByteOrder( int )));
    const QString byteOrderToolTip =
        i18nc( "@info:tooltip",
               "The byte order to use for decoding the bytes." );
    mByteOrderSelection->setToolTip( byteOrderToolTip );
    settingsLayout->addWidget( mByteOrderSelection );

    QLabel* unsignedAsHexLabel = new QLabel( i18nc("@option:check","Unsigned as hexadecimal:"), this );
    settingsLayout->addWidget( unsignedAsHexLabel );

    mUnsignedAsHexCheck = new QCheckBox( this );
    mUnsignedAsHexCheck->setChecked( mTool->isUnsignedAsHex() );
    connect( mUnsignedAsHexCheck, SIGNAL(toggled( bool )),
             mTool, SLOT(setUnsignedAsHex( bool )) );
    unsignedAsHexLabel->setBuddy( mUnsignedAsHexCheck );
    const QString unsignedAsHexToolTip =
        i18nc( "@info:tooltip",
               "Sets whether the values of the unsigned integer types are shown as hexadecimal instead of as decimal." );
    unsignedAsHexLabel->setToolTip( unsignedAsHexToolTip );
    mUnsignedAsHexCheck->setToolTip( unsignedAsHexToolTip );
    settingsLayout->addWidget( mUnsignedAsHexCheck );
    settingsLayout->addStretch();

    baseLayout->addLayout( settingsLayout );
}

bool PODTableView::eventFilter( QObject* object, QEvent* event )
{
    if( object == mPODTableView )
    {
        if( event->type() == QEvent::FocusIn )
        {
            QFocusEvent* focusEvent = static_cast<QFocusEvent*>( event );
            const Qt::FocusReason focusReason = focusEvent->reason();
            if( focusReason != Qt::ActiveWindowFocusReason
                && focusReason != Qt::PopupFocusReason )
            {
                const QModelIndex current = mPODTableView->selectionModel()->currentIndex();
                const int podId = current.row();
                if( current.isValid() && ! mTool->value(podId).isNull() )
                    mTool->markPOD( podId );
            }
        }
        else if( event->type() == QEvent::FocusOut )
        {
            QFocusEvent* focusEvent = static_cast<QFocusEvent*>( event );
            const Qt::FocusReason focusReason = focusEvent->reason();
            if( focusReason != Qt::ActiveWindowFocusReason
                && focusReason != Qt::PopupFocusReason )
                mTool->unmarkPOD();
        }
    }

    return QWidget::eventFilter( object, event );
}

void PODTableView::onCurrentRowChanged( const QModelIndex& current, const QModelIndex& previous )
{
    Q_UNUSED( previous )

    const int podId = current.row();
    if( current.isValid() && ! mTool->value(podId).isNull() )
        mTool->markPOD( podId );
    else
        mTool->unmarkPOD();
}

PODTableView::~PODTableView() {}

}
