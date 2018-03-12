#pragma once

#include "ofMain.h"
#include "GridPoint.h"


// Grid
//--------------------------------------------------------------------------------
class Grid
{
public:
  void                    setup( int _cols, int _rows, int _w, int _h );
  void                    setNeighbors( int _paddingTop, int _paddingRight, int _paddingBottom, int _paddingLeft );
  void                    draw();
  
  shared_ptr< GridPoint > getRandomPoint()
  {
    return gridPoints.at( static_cast< int >( ofRandom( gridPoints.size() ) ) );
  }
  
  shared_ptr< GridPoint > getPointAt( int _index )
  {
    if( ( _index >= 0 ) && ( _index < gridPoints.size() ) )
    {
      return gridPoints.at( _index );
    }
    else
    {
      cout << "[ Grid ] _index needs to be 0 ~ gridPoints.size()-1" << endl;
      return nullptr;
    }
  }
  
  shared_ptr< GridPoint > getPointAt( int _x, int _y )
  {
    if( ( _x >= 0 && _x < cols ) && ( _y >= 0 && _y < rows ) )
    {
      return gridPoints.at( ( _y * cols ) + _x );
    }
    else
    {
      return nullptr;
    }
  }
  
  int getColumns(){ return cols; }
  int getRows(){    return rows; }
  int size(){       return gridPoints.size(); }
  
private:
  int                               cols, rows;
  float                             gridSize;
  vector< shared_ptr< GridPoint > > gridPoints;
};