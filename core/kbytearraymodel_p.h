/***************************************************************************
                          kbytearraymodel_p.h  -  description
                             -------------------
    copyright            : (C) 2003,2007 by Friedrich W. H. Kossebau
    email                : kossebau@kde.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License version 2 as published by the Free Software Foundation.       *
 *                                                                         *
 ***************************************************************************/


#ifndef KHE_CORE_KBYTEARRAYMODEL_P_H
#define KHE_CORE_KBYTEARRAYMODEL_P_H


// lib
#include "kbytearraymodel.h"


namespace KHECore
{

class KByteArrayModelPrivate
{
  public:
    KByteArrayModelPrivate( KByteArrayModel *parent, char *D, unsigned int S, int RS, bool KM );
    KByteArrayModelPrivate( KByteArrayModel *parent, const char *D, unsigned int S );
    KByteArrayModelPrivate( KByteArrayModel *parent, int S, int MS );
    ~KByteArrayModelPrivate();

  public:
    char datum( unsigned int offset ) const;
    int size() const;
    bool isReadOnly() const;
    bool isModified() const;

    int insert( int at, const char *data, int length );
    int remove( const KSection &section );
    unsigned int replace( const KSection &before, const char *after, unsigned int afterLength );
    int move( int to, const KSection &fromSection );
    int fill( const char fillChar, unsigned int from = 0, int length = -1 );
    void setDatum( unsigned int offset, const char datum );

    void setModified( bool modified = true );

    int indexOf( const char *searchString, int length, int from = 0 ) const;
//     virtual int find( const char*KeyData, int length, const KSection &Section ) const;
    int lastIndexOf( const char *searchString, int length, int from = -1 ) const;

  public:
    void setReadOnly( bool readOnly = true );
    void setMaxSize( int maxSize );
    /** sets whether the memory given by setData or in the constructor should be kept on resize
      */
    void setKeepsMemory( bool keepsMemory = true );
    void setAutoDelete( bool autoDelete = true );
    void setData( char *data, unsigned int size, int rawSize = -1, bool keepMemory = true );

  public:
    char *data() const;
    int maxSize() const;
    /** returns whether the memory of the byte array is kept on resize */
    bool keepsMemory() const;
    bool autoDelete() const;

  protected:
    /** resizes the buffer, if possible, saving the data and splitting the data, if demanded
     * @param AddSize additional size the buffer should grow
     * @param SplitPos if -1 does not split
     * @param SaveUpperPart true if upper part should be copied into new buffer
     * @return additional size the buffer has grown
     */
    int addSize( int AddSize, int SplitPos = -1, bool SaveUpperPart = true );

  protected:
    KByteArrayModel *p;
    /** */
    char *m_data;
    /** size of the data */
    unsigned int m_size;
    /** m_size of data array */
    unsigned int m_rawSize;
    /** maximal size of array, unlimited if -1 */
    int m_maxSize;
    /** flag whether the initially given memory should be kept */
    bool m_keepsMemory:1;
    /** flag whether the  */
    bool m_autoDelete:1;
    /**  */
    bool m_readOnly:1;
    /** */
    bool m_modified:1;
};


inline KByteArrayModelPrivate::~KByteArrayModelPrivate() { if( m_autoDelete ) delete m_data; }

inline char KByteArrayModelPrivate::datum( unsigned int Offset ) const { return m_data[Offset]; }
inline int KByteArrayModelPrivate::size()                        const { return m_size; }

inline bool KByteArrayModelPrivate::isReadOnly()   const { return m_readOnly; }
inline bool KByteArrayModelPrivate::isModified()   const { return m_modified; }

inline void KByteArrayModelPrivate::setReadOnly( bool RO )    { m_readOnly = RO; }
inline void KByteArrayModelPrivate::setMaxSize( int MS )      { m_maxSize = MS; }
inline void KByteArrayModelPrivate::setKeepsMemory( bool KM ) { m_keepsMemory = KM; }
inline void KByteArrayModelPrivate::setAutoDelete( bool AD )  { m_autoDelete = AD; }
inline void KByteArrayModelPrivate::setDatum( unsigned int offset, const char datum )
{
    m_data[offset] = datum;
    m_modified = true;
    emit p->contentsReplaced( offset, 1, 1 );
    emit p->contentsChanged( offset, offset );
    emit p->modificationChanged( true );
}
inline void KByteArrayModelPrivate::setModified( bool modified )
{
    m_modified = modified;
    emit p->modificationChanged( m_modified );
}
inline void KByteArrayModelPrivate::setData( char *data, unsigned int size, int rawSize, bool keepMemory )
{
    if( m_autoDelete )
        delete m_data;
    const int oldSize = m_size;

    m_data = data;
    m_size = size;
    m_rawSize = (rawSize<(int)size) ? size : rawSize;
    if( m_maxSize != -1 && m_maxSize < (int)size )
        m_maxSize = size;
    m_keepsMemory = keepMemory;

    m_modified = false;
    emit p->contentsReplaced( 0, oldSize, size );
    emit p->contentsChanged( 0, oldSize-1 );
    emit p->modificationChanged( false );
}



inline char *KByteArrayModelPrivate::data()       const { return m_data; }
inline int KByteArrayModelPrivate::maxSize()      const { return m_maxSize; }
inline bool KByteArrayModelPrivate::keepsMemory() const { return m_keepsMemory; }
inline bool KByteArrayModelPrivate::autoDelete()  const { return m_autoDelete; }

}

#endif
