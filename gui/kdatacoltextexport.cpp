/***************************************************************************
                          kdatacoltextexport.cpp  -  description
                             -------------------
    begin                : Sam Aug 30 2003
    copyright            : (C) 2003 by Friedrich W. H. Kossebau
    email                : kossebau@kde.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License version 2 as published by the Free Software Foundation.       *
 *                                                                         *
 ***************************************************************************/


#include "kdatacoltextexport.h"

// lib
#include "kdatacolumn.h"
#include "kdatalayout.h"
// C
#include <string.h>


namespace KHEUI {

static const int DefaultTEByteSpacingWidth = 1;
static const int TEGroupSpacingWidth = 3;

QString KDataColTextExport::whiteSpace( uint s )
{
  return QString().fill( ' ', s );
}

KDataColTextExport::KDataColTextExport( const KDataColumn* BufferColumn, const char *D,
                                            KCoordRange CR, int ByteWidth )
 : Data( D ),
   CoordRange( CR )
{
  NoOfBytesPerLine = BufferColumn->layout()->noOfBytesPerLine();
  Pos = new int[NoOfBytesPerLine];

  // TODO: remove this hack and make it more general
  int ByteSpacingWidth = BufferColumn->byteSpacingWidth();
  if( ByteSpacingWidth > 0 )
    ByteSpacingWidth = DefaultTEByteSpacingWidth;

  int SpacingTrigger = BufferColumn->noOfGroupedBytes()-1;
  if( SpacingTrigger < 0 )
    SpacingTrigger = NoOfBytesPerLine; // ensures to never trigger the group spacing

  int N = 0;
  int p = 0;
  int gs = 0;
  int *P = Pos;
  for( ; P<&Pos[NoOfBytesPerLine]; ++P, ++p, ++gs )
  {
    *P = N;
    N += ByteWidth;

    // is there a space behind the actual byte (if it is not the last)?
    if( gs == SpacingTrigger )
    {
      N += TEGroupSpacingWidth;
      gs = -1;
    }
    else
      N += ByteSpacingWidth;
  }
  N -= (gs==0)?TEGroupSpacingWidth:ByteSpacingWidth;

  NoOfCharsPerLine = N;
}


KDataColTextExport::~KDataColTextExport()
{
  delete [] Pos;
}


int KDataColTextExport::charsPerLine() const
{
  return NoOfCharsPerLine;
}


void KDataColTextExport::printFirstLine( QString *T, int Line ) const
{
  PrintLine = Line;
  PrintData = Data;
  print( T );
}


void KDataColTextExport::printNextLine( QString *T ) const
{
  print( T );
}


void KDataColTextExport::print( QString *T ) const
{
  T->append( whiteSpace(NoOfCharsPerLine) );
  ++PrintLine;
}

}
