/***************************************************************************
                          testfixedsizebufferdatabufferif.cpp  -  description
                            -------------------
    begin                : Mon Mai 3 2004
    copyright            : (C) 2004 by Friedrich W. H. Kossebau
    email                : Friedrich.W.H@Kossebau.de
***************************************************************************/

/***************************************************************************
*                                                                         *
*   This library is free software; you can redistribute it and/or         *
*   modify it under the terms of the GNU Library General Public           *
*   License version 2 as published by the Free Software Foundation.       *
*                                                                         *
***************************************************************************/


// lib specific
#include <kfixedsizebuffer.h>
// app specific
#include "testfixedsizebufferdatabufferif.h"


using namespace KHE;

static const int FixedSizeBufferSize = 60;

// all test imply that the buffer ca
// readonly 
KFixedSizeBufferDataBufferIfTest::KFixedSizeBufferDataBufferIfTest()
 : KDataBufferIfTest( "KFixedSizeBufferDataBufferIfTest" )
{
  TestSection.set( 10,40 );

  KFixedSizeBuffer *Buffer = new KFixedSizeBuffer( FixedSizeBufferSize );
  char *Data = Buffer->rawData();
  for( char i=0; i<FixedSizeBufferSize; ++i )
    Data[i] = i+1;

  DataBuffer = Buffer;
}


KFixedSizeBufferDataBufferIfTest::~KFixedSizeBufferDataBufferIfTest()
{
  delete DataBuffer;
}


void KFixedSizeBufferDataBufferIfTest::setup()
{
}

void KFixedSizeBufferDataBufferIfTest::tearDown()
{
}

#include "testfixedsizebufferdatabufferif.moc"
