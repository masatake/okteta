/*
    This file is part of the Kasten Framework, made within the KDE community.

    Copyright 2007-2009,2012 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#ifndef ABSTRACTMODELSYNCHRONIZER_H
#define ABSTRACTMODELSYNCHRONIZER_H

// lib
#include <kasten/kastencore_export.h>
#include <kasten/kastencore.h>
// Qt
#include <QObject>

class QUrl;


namespace Kasten
{

class AbstractLoadJob;
class AbstractConnectJob;
class AbstractSyncToRemoteJob;
class AbstractSyncFromRemoteJob;
class AbstractSyncWithRemoteJob;
class AbstractDocument;

class AbstractModelSynchronizerPrivate;

// TODO: better names? Active Translator? 
// synchronizers are created by factory functions (like plugins)

// TODO: should synchronizers set the document to readonly if remote is readonly? or who?
// TODO: should synchronizers offer to change writeflag at remote?
// TODO: allow synchronizers which can read-only, perhaps also write-only (usecase?)

/**
possible actions:
1. synchronizer loads document and synchronizes until closing
   -> done by factory functions
2. synchronizer gets attached to a document new created or with other synchronizer
3. synchronizer used to export a model
*/
class KASTENCORE_EXPORT AbstractModelSynchronizer : public QObject
{
  Q_OBJECT

  public:
    enum ConnectOption // TODO: better names
    {
      SyncLocalAndRemote = 0,
      ReplaceRemote = 1,
      ReplaceLocal = 2
    };
  protected:
    explicit AbstractModelSynchronizer( AbstractModelSynchronizerPrivate* d );

  public:
    AbstractModelSynchronizer();

    virtual ~AbstractModelSynchronizer();

  public:
    QUrl url() const;

  public: // API to be implemented
    // TODO: makes this a job, too
    // TODO: filesystem synchronizer (or: to-passive-storage) does not need this: subclass or interface?
//     virtual void startOffering( AbstractDocument* document ) = 0;
    // TODO: once the synchronizer is attached to a document, this function should not be called
    // is there a way to ensure this?
    virtual AbstractLoadJob* startLoad( const QUrl& url ) = 0;
    /** */
    // TODO: not in constructor? cannot be called twice, each synchronizer is attached to its document
//     virtual AbstractDocument* createWorkingCopy( const QUrl& originUrl, int* success ) const = 0;

    /** */
    // TODO: static? or by function? or another class? but 
//     virtual void copyTo( const QUrl& url, AbstractDocument* document, int* success ) const = 0;

    /** overwrite remote with local (save) */
    virtual AbstractSyncToRemoteJob* startSyncToRemote() = 0;
    /** overwrite local with remote (reload) */
    virtual AbstractSyncFromRemoteJob* startSyncFromRemote() = 0;

    /** changes the  */ // TODO: better name for replace: overwrite?
    virtual AbstractSyncWithRemoteJob* startSyncWithRemote( const QUrl& url, AbstractModelSynchronizer::ConnectOption option ) = 0;

    virtual AbstractConnectJob* startConnect( AbstractDocument* document,
                                              const QUrl& url, AbstractModelSynchronizer::ConnectOption option ) = 0;
//     virtual bool syncBiDirectly() = 0;
//     virtual bool canSyncBiDirectly() const = 0;
//     virtual bool deleteDocument();

    virtual AbstractDocument* document() const = 0;
    virtual LocalSyncState localSyncState() const = 0;
    virtual RemoteSyncState remoteSyncState() const = 0;


  Q_SIGNALS:
    void urlChanged( const QUrl& url );
    // TODO: next two could be part of an interface? parameter quite specific
    void dataPulled( int ) const;
    void dataPushed( int ) const;

    // TODO: should be signal the diff? how to say then remote is in synch again?
    // could be done by pairs of flags instead of notset = isnot
    // TODO: this signal should be part of AbstractModel?
    void localSyncStateChanged( Kasten::LocalSyncState newState );
    void remoteSyncStateChanged( Kasten::RemoteSyncState newState );

  protected: // get
    void setUrl( const QUrl& url );

  protected:
    Q_DECLARE_PRIVATE( AbstractModelSynchronizer )
  protected:
    AbstractModelSynchronizerPrivate* const d_ptr;
};

}

#endif
