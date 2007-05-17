/***************************************************************************
                          kdatalayout.h  -  description
                             -------------------
    begin                : Thu Jun 12 2003
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


#ifndef KHE_UI_KDATALAYOUT_H
#define KHE_UI_KDATALAYOUT_H

// lib
#include "kcoordrange.h"
// commonlib
#include <ksection.h>


namespace KHEUI {

/**@short the logical layout of a plain buffer view
  *
  * Given the values for
  * * length of the buffer,
  * * number of bytes per line,
  * * a possible (relative) offset in the display, and
  * * the number of lines per page jump
  * the following values are calculated:
  * * starting line of display,
  * * starting position in this line,
  * * final line of display,
  * * final position in this line, and
  * * the total number of lines (is final line +1 or 0)
  *
  * This layout sees the buffer as a continuous stream of byte,
  * thus uses each line after the start from the begin to the end.
  *
  * If the buffer is empty the end coord will be set one pos left to the start coord
  * to easen the cursor handling.
  *
  *@author Friedrich W. H.  Kossebau
  */
class KDataLayout
{
  public:
    KDataLayout( int NoBpL, int SO, int L );
    //KDataLayout();
    ~KDataLayout();


  public: // given values
    /** */
    int startOffset() const;
    /** returns number of bytes per line */
    int noOfBytesPerLine() const;
    /** returns the length of the displayed data (equals Buffer->size()) */
    int length() const;
    /** returns number of lines per visual page */
    int noOfLinesPerPage() const;

  public: // calculated values
    int startLine() const;
    int startPos() const;
    /** returns the coord of the start */
    KCoord start() const;

    int finalLine() const;
    int finalPos() const;
    /** returns the coord of the end */
    KCoord final() const;

    /** tells how much lines this layout needs (incl. blank leading lines due to StartOffset) */
    int noOfLines() const;


  public: // value calculation service
    /** calculates the index of the coord
      * If the coord is before the first coord the first index is returned,
      * if the coord is behind the last coord the last index is returned
      */
    int indexAtCCoord( const KCoord &C ) const;
    /** calculates the index of the first pos in line.
      * If the line is below the first line the first index is returned,
      * if the line is above the last line the last index is returned
      */
    int indexAtCLineStart( int L ) const;
    /** calculates the index of last pos in line
      * If the line is below the first line the first index is returned,
      * if the line is above the last line the last index is returned
      */
    int indexAtCLineEnd( int L ) const;
    /** calculates the line in which index is found
      * If the index is below the first index the first line is returned,
      * if the index is above the last index the last line is returned
      */
    int lineAtCIndex( int Index ) const;
    /** calculates the coord in which index is found
      * If the index is below the first index the first coord is returned,
      * if the index is above the last index the last coord is returned
      */
    KCoord coordOfCIndex( int Index ) const;

    /** calculates the index of coord. if coord is invalid the behaviour is undefinded */
    int indexAtCoord( const KCoord &C ) const;
    /** calculates the index of the first pos in line. if line is invalid the behaviour is undefinded */
    int indexAtLineStart( int L ) const;
    /** calculates the index of last pos in line. if line is invalid the behaviour is undefinded */
    int indexAtLineEnd( int L ) const;
    /** calculates the line in which index is found. if index is invalid the behaviour is undefinded */
    int lineAtIndex( int Index ) const;
    /** calculates the coord in which index is found. if index is invalid the behaviour is undefinded */
    KCoord coordOfIndex( int Index ) const;
    /** calculates the range of coords in which the indizes are found. if indizes are invalid the behaviour is undefinded */
    KCoordRange coordRangeOfIndizes( const KHE::KSection &Indizes ) const;

    /** returns the used positions in line */
    KHE::KSection positions( int Line ) const;
    /** returns the first Pos in line. if line is invalid the behaviour is undefinded */
    int firstPos( int Line ) const;
    /** returns the last Pos in line. if line is invalid the behaviour is undefinded */
    int lastPos( int Line ) const;
    /** returns the valid Pos or the first Pos in line. if coord is invalid the behaviour is undefinded */
    int firstPos( const KCoord &C ) const;
    /** returns the valid Pos or the last Pos in line. if coord is invalid the behaviour is undefinded */
    int lastPos( const KCoord &C ) const;
    /** returns true if the line has content */
    bool hasContent( int Line ) const;
    /** returns true if the coord is the first in it's line. if coord is invalid the behaviour is undefinded */
    bool atLineStart( const KCoord &C ) const;
    /** returns true if the coord is the last in it's line. if coord is invalid the behaviour is undefinded */
    bool atLineEnd( const KCoord &C ) const;

    /** returns the index if valid or the nearest valid index */
    int correctIndex( int I ) const;
    /** returns the coord if valid or the nearest valid coord */
    KCoord correctCoord( const KCoord &C ) const;


  public: // modification access; return true if changes
     /** sets StartOffset, returns true if changed */
    bool setStartOffset( int SO );
    /** sets number of bytes per line, returns true if changed */
    bool setNoOfBytesPerLine( int N );
    /** sets number of lines per page */
    void setNoOfLinesPerPage( int N );
    /** sets length of data to display, returns true if changed */
    bool setLength( int L );


  protected:
    /** calculates the start coord by startoffset and number of bytes per line */
    void calcStart();
    /** calculates the final coord by startoffset, length, and number of bytes per line */
    void calcEnd();


 protected:
    /** how many chars per line */
    int NoOfBytesPerLine;
    /** starting offset of the displayed data */
    int StartOffset;
    /** length of the displayed buffer */
    int Length;
    /** number of lines that are moved by page up/down */
    int NoOfLinesPerPage;

  protected: // calculated values, buffered
    /** coord in which the start offset is (starting with 0) */
//    KCoord Start;
    /** coord in which the last byte is (starting with 0) */
//    KCoord Final;
    /** */
    KCoordRange ContentCoords;
};


inline int KDataLayout::startOffset()       const { return StartOffset; }
inline int KDataLayout::noOfBytesPerLine()  const { return NoOfBytesPerLine; }
inline int KDataLayout::length()            const { return Length; }

inline KCoord KDataLayout::final()    const { return ContentCoords.end(); }
inline KCoord KDataLayout::start()    const { return ContentCoords.start(); }
inline int KDataLayout::startPos()          const { return start().pos(); }
inline int KDataLayout::finalPos()          const { return final().pos(); }
inline int KDataLayout::startLine()         const { return start().line(); }
inline int KDataLayout::finalLine()         const { return final().line(); }
inline int KDataLayout::noOfLinesPerPage()  const { return NoOfLinesPerPage; }
inline int KDataLayout::noOfLines()         const { return Length==0?0:final().line()+1; }

}

#endif
