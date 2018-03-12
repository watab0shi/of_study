#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSyphon.h"
#include "Grid.h"
#include "Route.h"


// ofApp
//--------------------------------------------------------------------------------
class ofApp : public ofBaseApp
{
public:
  void setup();
  void update();
  void draw();
  void exit();
  
  void keyPressed( int _key );
  void keyReleased( int _key );
  void mouseMoved( int _x, int _y );
  void mouseDragged( int _x, int _y, int _button );
  void mousePressed( int _x, int _y, int _button );
  void mouseReleased( int _x, int _y, int _button );
  void mouseEntered( int _x, int _y );
  void mouseExited( int _x, int _y );
  void windowResized( int _w, int _h );
  void dragEvent( ofDragInfo _dragInfo );
  void gotMessage( ofMessage _msg );
  
  int                  w, h;
  
  ofFbo                fbo;
  ofxSyphonServer      syphonServer;
  
  // grid
  const int            GRID_WIDTH  = 1920;
  const int            GRID_HEIGHT = 2160;
  Grid                 grid;
  
  // route
  vector< Route >      routes;
  const ofFloatColor   routeColors[ 3 ] = { { 1., 0., 0. }, { 0., 1., 0. }, { 0., 0., 1. } };
  
  // gui
  ofxPanel             gui;
  ofParameterGroup     params;
  ofParameter< float > fps;
  
  ofParameterGroup     routeParams;
  ofParameter< int >   closingMode;
  ofParameter< int >   maxNumLines;
  ofParameter< int >   routeSpeed;
  ofParameter< float > stoppingDuration;
  ofParameter< int >   numExcludePoints;
  
  void                 onClosingModeChanged( int& _v );
  void                 onRouteSpeedChanged( int& _v );
  void                 onStoppingDurationChanged( float& _v );
  void                 onNumExcludePointsChanged( int& _v );
  
  bool                 visibleGui;
  ofFile               settingFile;
  void                 setupGui();
};
