#pragma once

#include "ofMain.h"
#include "GridPoint.h"


// Route
//--------------------------------------------------------------------------------
class Route
{
public:
  Route();
  Route( int _id, shared_ptr< GridPoint > _point, ofFloatColor _color, int _maxNumLines, int _speed, vector< Route >* _otherRoutes );
  Route( int _id, shared_ptr< GridPoint > _point, ofFloatColor _color, int _maxNumLines, int _speed, ofPolyline _lastLine, vector< Route >* _otherRoutes );
  
  enum ClosingMode {
    CLOSING_ALPHA,
    CLOSING_TRACE
  };
  
  void update();
  void draw();
  
  void close()
  {
    bClosing = true;
    
    // reset draingIndex
    drawingIndex = routePoints.size() - 1;
  }
  
  // setter
  void setDrawingSpeed( int _speed ){ drawingSpeed = _speed; }
  
  // getter
  int                     getId(){          return routeId;}
  shared_ptr< GridPoint > getEndPoint(){    return endPoint; }
  int                     getMaxNumLines(){ return maxNumLines; };
  ofFloatColor            getColor(){       return color; }
  ofPolyline              getLine(){        return line; }
  bool                    isOpened(){       return bOpened; }
  bool                    isClosed(){       return bClosed; }
  bool                    isClosing(){      return bClosing; }
  
  // static
  static void setLineWidth( int _width );
  static void setNumExcludePointsOfLastLine( int _num );
  static void setClosingMode( ClosingMode _mode );
  static void setStoppingDuration( float _duration );
  
private:
  void routing( ofPolyline* _lastLine = nullptr, vector< Route >* _otherRoutes = nullptr );
  
  int                     routeId;
  shared_ptr< GridPoint > endPoint;
  int                     maxNumLines;
  ofFloatColor            color;
  float                   alpha;
  ofPolyline              line;
  
  vector< ofPoint >       routePoints;
  
  int                     drawingIndex;
  int                     drawingSpeed;
  
  bool                    bOpened;
  float                   openedTime;
  
  bool                    bClosing;
  bool                    bClosed;
  
  // static
  static int              lineWidth;
  static int              numExcludePointsOfLastLine;
  static ClosingMode      closingMode;
  static float            stoppingDuration;
};