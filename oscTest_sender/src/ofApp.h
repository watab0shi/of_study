#pragma once

#include "ofMain.h"
#include "ofxOsc.h"


struct AttractPoint
{
  ofPoint pos;
  float   range;
};

// ofApp
//--------------------------------------------------------------------------------
class ofApp : public ofBaseApp
{
public:
  void setup();
  void update();
  void draw();
  
  void keyPressed( int _key );
  void mouseDragged( int _x, int _y, int _button );
  void mousePressed( int _x, int _y, int _button );
  void mouseReleased( int _x, int _y, int _button );
  
  vector< AttractPoint > attractPoints;
  void addRandomPoint();
  
  ofxOscSender           oscSender;
  int                    oscPort;
  void                   sendMessages( const vector< AttractPoint >& _points );
  
  bool                             bSelect;
  vector< AttractPoint >::iterator pointItr;
};
