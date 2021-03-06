/*
    This file is part of the Kasten Framework, made within the KDE community.

    Copyright 2009,2011 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#ifndef DIALOGHANDLER_H
#define DIALOGHANDLER_H

// lib
#include <kasten/kastengui_export.h>
// Kasten core
#include <kasten/abstractoverwritedialog.h>
#include <kasten/abstractsavediscarddialog.h>

class QWidget;


namespace Kasten
{

class KASTENGUI_EXPORT DialogHandler : public AbstractOverwriteDialog,
                                       public AbstractSaveDiscardDialog
{
  public:
    explicit DialogHandler( QWidget* widget = 0 );

    virtual ~DialogHandler();

  public: // AbstractOverwriteDialog API
    virtual Answer queryOverwrite( const QUrl& url, const QString& title ) const;

  public: // AbstractSaveDiscardDialog API
    virtual Answer queryDiscardOnReload( const AbstractDocument* document, const QString& title ) const;
    virtual Answer querySaveDiscard( const AbstractDocument* document, const QString& title ) const;
    virtual Answer queryDiscard( const AbstractDocument* document, const QString& title ) const;

  public:
    void setWidget( QWidget* widget );

  private:
    QWidget* mWidget;
};

}

#endif
