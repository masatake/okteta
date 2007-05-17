/***************************************************************************
                          kfilebytearraymodel_p.cpp  -  description
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


#include "kfilebytearraymodel_p.h"

// C
#include <stdlib.h>


namespace KHECore {

KFileByteArrayModelPrivate::KFileByteArrayModelPrivate( int pageNumber, int pageSize )
 : m_noOfUsedPages( pageNumber ),
   m_noOfFreePages( pageNumber ),
   m_pageSize( pageSize ),
   m_firstPage( -1 ),
   m_lastPage( -1 ),
   m_size( 0 )
{
    m_isOpen = false;

//   if( !filename.empty() )
//     open(filename);
}


char KFileByteArrayModelPrivate::datum( unsigned int datumOffset ) const
{
//   std::cout << "reading datum " << datumOffset << std::endl;
    int offsetInPage = datumOffset - m_offsetOfActualPage;
    // there shouldn't be any need to check l
    if( offsetInPage >= 0 && offsetInPage < (int)m_pageSize )
        return m_actualPage[offsetInPage];

    // load the page
    unsigned int pageIndex = datumOffset / m_pageSize;
    ensurePageLoaded( pageIndex );
    return m_actualPage[datumOffset-m_offsetOfActualPage];
}


bool KFileByteArrayModelPrivate::open( const QString &fileName )
{
    // clear old data
    if( isOpen() && !close() ) // only occurs if close somehow fails.
        return false;

    m_file.setFileName( fileName );
    if( !m_file.open(QIODevice::ReadOnly) )
        return false;

    int fileSize = m_file.size();
    m_size = fileSize;

    // calculate necessary number of pages
    int noOfPages = fileSize/m_pageSize + 1;

    // initialize Page pointers
    m_data.resize( noOfPages );
    for( KPageOfChar::iterator D=m_data.begin(); D!=m_data.end(); ++D )
        *D = 0;

    m_firstPage = m_lastPage = 0;

    return ensurePageLoaded( 0 );
}


bool KFileByteArrayModelPrivate::close()
{
    if( !isOpen() )
        return false;

    m_file.close();

    if( m_file.error() != QFile::NoError )
        return false;

    // free pages
    for( KPageOfChar::iterator D=m_data.begin(); D!=m_data.end(); ++D )
        delete [] *D;

    m_firstPage = m_lastPage = -1;
    m_noOfFreePages = m_noOfUsedPages;

    return true;
}


bool KFileByteArrayModelPrivate::ensurePageLoaded( unsigned int pageIndex ) const
{
    if( !isOpen() )
        return false;
    // page loaded?
    if( m_data[pageIndex] != 0 )
    {
        m_actualPage = m_data[pageIndex];
        m_offsetOfActualPage = pageIndex * m_pageSize;
        return true;
    }

    // no page available?
    if( m_noOfFreePages < 1 )
    {
        // free the page which is the furthest away from the page we are loading
        if( abs(m_firstPage-pageIndex) > abs(m_lastPage-pageIndex) )
            while( !freePage(m_firstPage++) );
        else
            while( !freePage(m_lastPage--) );
    }

    // create Page
    m_data[pageIndex] = new char[m_pageSize];
    --m_noOfFreePages;

    // jump to position and read the page's data in
    bool success = m_file.seek( (unsigned long)(pageIndex*m_pageSize) );
    if( success )
        success = m_file.read( m_data[pageIndex], m_pageSize ) > 0;

    if( success )
    {
        // correct bounds
        if( (int)pageIndex < m_firstPage )
            m_firstPage = pageIndex;

        if( (int)pageIndex > m_lastPage )
            m_lastPage = pageIndex;

        m_actualPage = m_data[pageIndex];
        m_offsetOfActualPage = pageIndex * m_pageSize;
    }

    return success;
}


bool KFileByteArrayModelPrivate::freePage( unsigned int pageIndex ) const
{
    // check range and if is loaded at all
    if( (int)pageIndex >= m_data.size() || !m_data[pageIndex] )
        return false;

    delete [] m_data[pageIndex];
    m_data[pageIndex] = 0;
    ++m_noOfFreePages;
    return true;
}


KFileByteArrayModelPrivate::~KFileByteArrayModelPrivate()
{
    if( m_file.isOpen() )
        close();
}

}
