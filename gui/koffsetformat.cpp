/***************************************************************************
                          koffsetformat.cpp  -  description
                             -------------------
    begin                : Mit Mai 21 2003
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


#include "koffsetformat.h"

// C
#include <stdio.h>


namespace KHEUI {

const unsigned int KOffsetFormat::CodingWidth[2] = { 9, 10 };

const KOffsetFormat::print KOffsetFormat::PrintFunction[2] =
{ KOffsetFormat::printHexadecimalOffset, KOffsetFormat::printDecimalOffset };



void KOffsetFormat::printHexadecimalOffset( char *Buffer, unsigned int Offset )
{
  sprintf( Buffer, "%04X:%04X", Offset>>16, Offset&0x0000FFFF );
}


void KOffsetFormat::printHexadecimalSmallOffset( char *Buffer, unsigned int Offset )
{
  sprintf( Buffer, "%04x:%04x", Offset>>16, Offset&0x0000FFFF );
}


void KOffsetFormat::printDecimalOffset( char *Buffer, unsigned int Offset )
{
  sprintf( Buffer, "%010u", Offset );
}

}
