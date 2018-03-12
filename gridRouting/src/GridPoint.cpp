
#include "GridPoint.h"


int GridPoint::pointSize = 4;
void GridPoint::setPointSize( int _size )
{
  GridPoint::pointSize = _size;
}

int GridPoint::getPointSize()
{
  return GridPoint::pointSize;
}


// GridPoint
//------------------------------------------------------------
GridPoint::GridPoint() : ofPoint( 0, 0 ), neighbors{ nullptr, nullptr, nullptr, nullptr }
{
}

GridPoint::GridPoint( float _x, float _y ) : ofPoint( _x, _y ), neighbors{ nullptr, nullptr, nullptr, nullptr }
{
}

GridPoint::GridPoint( ofPoint _pos ) : ofPoint( _pos ), neighbors{ nullptr, nullptr, nullptr, nullptr }
{
}


// draw
//------------------------------------------------------------
void GridPoint::draw()
{
  ofFill();
  ofSetColor( 255 );
  
  ofDrawRectangle( x - GridPoint::pointSize * .5, y - GridPoint::pointSize * .5, GridPoint::pointSize, GridPoint::pointSize );
}


// drawNeighbors
//------------------------------------------------------------
void GridPoint::drawNeighbors()
{
  ofNoFill();
  ofSetColor( 255 );
  
  for( auto& n : neighbors )
  {
    if( !n ) continue;
    ofDrawCircle( static_cast< ofPoint >( *n ), 10 );
  }
}


// setNeighbors
//------------------------------------------------------------
void GridPoint::setNeighbors( shared_ptr< GridPoint > _top, shared_ptr< GridPoint > _right, shared_ptr< GridPoint > _bottom, shared_ptr< GridPoint > _left )
{
  neighbors[ 0 ] = _top;
  neighbors[ 1 ] = _right;
  neighbors[ 2 ] = _bottom;
  neighbors[ 3 ] = _left;
}
