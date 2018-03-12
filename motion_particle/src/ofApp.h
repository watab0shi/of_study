#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Particles.h"


// ofApp
//--------------------------------------------------------------------------------
class ofApp : public ofBaseApp
{
public:
  void setup();
  void update();
  void draw();
  
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
  void exit();
  
  
  // basic variables
  float                w, h;
  int                  frameRate;
  
  // particles
  Particles            particles;
  
  // fbo
  ofFbo                fbo;
  
  // gui
  ofxPanel             gui;
  ofParameterGroup     params;
  ofParameter< float > fps;
  ofParameter< int >   mode;
  
  bool                 visibleGui;
  ofFile               settingFile;
  void                 setupGui();
};
