
#include "Grid.h"


// setup
//------------------------------------------------------------
void Grid::setup( int _cols, int _rows, int _w, int _h )
{
  float w  = _w;
  float h  = _h;
  float hw = w / 2;
  float hh = h / 2;
  
  cols     = _cols;
  rows     = _rows;
  gridSize = h / ( rows - 1 );
  
  ofVec2f offset = ofVec2f( ( w - ( cols - 1 ) * gridSize ) / 2, 0 );
  
  // 先に点だけ配置しておく
  for( int y = 0; y < rows; ++y )
  {
    for( int x = 0; x < cols; ++x )
    {
      gridPoints.emplace_back( make_shared< GridPoint >( ofPoint( x, y ) * gridSize + offset ) );
    }
  }
  
  // ↑で配置された点から隣接点を登録する
  setNeighbors( static_cast< int >( rows / 2 ) + 1, 0, 0, 0 );
}


void Grid::setNeighbors( int _paddingTop, int _paddingRight, int _paddingBottom, int _paddingLeft )
{
  for( int y = 0; y < rows; ++y )
  {
    for( int x = 0; x < cols; ++x )
    {
      // index
      int i  = ( y * cols ) + x;
      int iT = ( ( y - 1 ) * cols ) + x;// top
      int iR = ( y * cols ) + ( x + 1 );// right
      int iB = ( ( y + 1 ) * cols ) + x;// bottom
      int iL = ( y * cols ) + ( x - 1 );// left
      
      // is edge ?
      bool bTop    = ( y <= 0        + _paddingTop );
      bool bRight  = ( x >= cols - 1 - _paddingRight );
      bool bBottom = ( y >= rows - 1 - _paddingBottom );
      bool bLeft   = ( x <= 0        + _paddingLeft );
      
      // 隣接点を登録 外周の場合は nullptr をいれる
      gridPoints.at( i )->setNeighbors( ( bTop )    ? nullptr : gridPoints.at( iT ),
                                        ( bRight )  ? nullptr : gridPoints.at( iR ),
                                        ( bBottom ) ? nullptr : gridPoints.at( iB ),
                                        ( bLeft )   ? nullptr : gridPoints.at( iL ) );
    }
  }
}

// draw
//------------------------------------------------------------
void Grid::draw()
{
  for( auto& p : gridPoints ) p->draw();
}