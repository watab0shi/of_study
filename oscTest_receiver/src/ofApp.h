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
  
  vector< AttractPoint > attractPoints;
  
  ofxOscReceiver         oscReceiver;
  int                    oscPort;
};
