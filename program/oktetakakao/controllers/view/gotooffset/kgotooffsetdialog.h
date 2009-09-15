/*
    This file is part of the Okteta Kakao module, part of the KDE project.

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

#ifndef KGOTOOFFSETDIALOG_H
#define KGOTOOFFSETDIALOG_H

// KDE
#include <KDialog>
// Qt
#include <QtCore/QByteArray>
#include <QtCore/QString>

class GotoOffsetTool;
class QCheckBox;
class KComboBox;
class KByteArrayValidator;


class KGotoOffsetDialog : public KDialog
{
  Q_OBJECT

  public:
    explicit KGotoOffsetDialog( GotoOffsetTool* tool, QWidget* parent = 0 );
    ~KGotoOffsetDialog();

  public: // set
    void setOffset( int offset );
    void setRange( int firstOffset, int lastOffset );

  public: // get
    int offset() const;

  protected: // QWidget API
    virtual void showEvent( QShowEvent* showEvent );

  protected: // KDialog API
    virtual void slotButtonClicked( int button );

  private Q_SLOTS:
    void onSelectorChanged( int index );
    void onOffsetChanged( const QString& text );
    void onToolIsApplyableChanged( bool isApplyable );

  private:
    KComboBox* mSelector;
    KComboBox* mOffsetEdit;
    QCheckBox* mAtCursorCheckBox;
    QCheckBox* mExtendSelectionCheckBox;
    QCheckBox* mBackwardsCheckBox;

    QString mOffsetString[2];
    KByteArrayValidator* mOffsetValidator;

    GotoOffsetTool* mTool;
};

#endif