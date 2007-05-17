/***************************************************************************
                          knavigator.h  -  description
                             -------------------
    begin                : Sa Dez 4 2004
    copyright            : (C) 2004 by Friedrich W. H. Kossebau
    email                : kossebau@kde.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License version 2 as published by the Free Software Foundation.       *
 *                                                                         *
 ***************************************************************************/


#ifndef KHE_UI_KNAVIGATOR_H
#define KHE_UI_KNAVIGATOR_H


// lib
#include "kcontroller.h"


namespace KHEUI
{

class KNavigator : public KController
{
  protected:
    enum KMoveAction { MoveBackward, MoveWordBackward, MoveForward, MoveWordForward,
                       MoveUp, MovePgUp, MoveDown, MovePgDown,
                       MoveLineStart, MoveHome, MoveLineEnd, MoveEnd };
  public:
    KNavigator( KByteArrayView *HE, KController *P );

  public: // KEditor API
    virtual bool handleKeyPress( QKeyEvent *KeyEvent );

  protected:
    /** moves the cursor according to the action, handles all drawing */
    void moveCursor( KMoveAction Action, bool Select );
};

}

#endif
