/*
    This file is part of the Kakao Framework, part of the KDE project.

    Copyright 2006-2007 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#ifndef CLIPBOARDCONTROLLER_H
#define CLIPBOARDCONTROLLER_H


// Kakao gui
#include <kviewcontroller.h>

class KXmlGuiWindow;
class KAction;
class KViewManager;
namespace KDE { namespace If {
class DataSelectable;
class SelectedDataWriteable;
} }


class ClipboardController : public KViewController
{
  Q_OBJECT

  public:
    explicit ClipboardController( KXmlGuiWindow *window );

  public: // KViewController API
    virtual void setView( KAbstractView *view );

  protected Q_SLOTS: // action slots
    void cut();
    void copy();
    void paste();

  private Q_SLOTS:
    void onHasSelectedDataChanged( bool hasSelectedData );
    void onReadOnlyChanged( bool isReadOnly );
    void onClipboardDataChanged();

  protected:
    KXmlGuiWindow *mMainWindow;
    KAbstractView *mView;
    KDE::If::DataSelectable *mSelectionControl;
    KDE::If::SelectedDataWriteable *mMimeDataControl;

    KAction *mCutAction;
    KAction *mCopyAction;
    KAction *mPasteAction;
};

#endif
