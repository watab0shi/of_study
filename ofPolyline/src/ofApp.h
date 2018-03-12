#pragma once

#include "ofMain.h"


// ofApp
//--------------------------------------------------------------------------------
class ofApp : public ofBaseApp
{
public:
  void setup();
  void update();
  void draw();
  
  void keyPressed( int _key );
  void mouseMoved( int _x, int _y );
  void windowResized( int _w, int _h );
  
  float                w, h;
  float                hw;
  float                qh;
  
  ofTrueTypeFont       font;
  int                  fontSize;
  string               word;
  
  int                  smoothing;
  int                  resampleCount;
  int                  resampleSpacing;
  
  vector< ofPolyline > outlines;
  vector< ofPolyline > smoothedOutlines;
  vector< ofPolyline > reCountedOutlines;
  vector< ofPolyline > reSpacedOutlines;
  
  void clearOutlines();
  void setOutlines( string _word );
  void drawOutlines( vector< ofPolyline >& _outlines, float _x, float _y, bool _bDrawOriginal = true );
};
