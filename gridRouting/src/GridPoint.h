#pragma once

#include "ofMain.h"


// GridPoint
//--------------------------------------------------------------------------------
class GridPoint : public ofPoint
{
public:
  GridPoint();
  GridPoint( float _x, float _y );
  GridPoint( ofPoint _pos );
  
  void draw();
  void drawNeighbors();
  
  static void setPointSize( int _size );
  static int  getPointSize();
  
  shared_ptr< GridPoint > neighbors[ 4 ];
  void setNeighbors( shared_ptr< GridPoint > _top, shared_ptr< GridPoint > _right, shared_ptr< GridPoint > _bottom, shared_ptr< GridPoint > _left );
  
private:
  static int  pointSize;
};