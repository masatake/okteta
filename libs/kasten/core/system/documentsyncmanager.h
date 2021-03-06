/*
    This file is part of the Kasten Framework, made within the KDE community.

    Copyright 2007,2009,2011 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#ifndef DOCUMENTSYNCMANAGER_H
#define DOCUMENTSYNCMANAGER_H

// lib
#include <kasten/kastencore_export.h>
// Qt
#include <QObject>

class QUrl;
class QString;


namespace Kasten
{

class AbstractDocument;
class AbstractModelSynchronizerFactory;
class DocumentManager;
class AbstractSaveDiscardDialog;
class AbstractOverwriteDialog;


class KASTENCORE_EXPORT DocumentSyncManager : public QObject
{
  Q_OBJECT

  public:
    explicit DocumentSyncManager( DocumentManager* manager );
    virtual ~DocumentSyncManager();

  public:
    void load( const QUrl& url );
// TODO: better name
    bool setSynchronizer( AbstractDocument* document );
    bool canClose( AbstractDocument* document );
    void reload( AbstractDocument* document );
    void save( AbstractDocument* document );

  public:
    QStringList supportedRemoteTypes() const;
    bool hasSynchronizerForLocal( const QString& mimeType ) const;
    QUrl urlOf( AbstractDocument* document ) const;

  public:
    void setDocumentSynchronizerFactory( AbstractModelSynchronizerFactory* synchronizerFactory );
    void setSaveDiscardDialog( AbstractSaveDiscardDialog* saveDiscardDialog );
    void setOverwriteDialog( AbstractOverwriteDialog* overwriteDialog );

  Q_SIGNALS:
    void urlUsed( const QUrl& url );

  private Q_SLOTS:
    void onDocumentLoaded( Kasten::AbstractDocument* document );

    void onDocumentsAdded( const QList<Kasten::AbstractDocument*>& documents );
    void onDocumentsClosing( const QList<Kasten::AbstractDocument*>& documents );

  private:
    // unless there is a singleton
    DocumentManager* mManager;

    // temporary hack: hard coded factories for byte arrays
    AbstractModelSynchronizerFactory* mSynchronizerFactory;

    AbstractSaveDiscardDialog* mSaveDiscardDialog;
    AbstractOverwriteDialog* mOverwriteDialog;
};

}

#endif
