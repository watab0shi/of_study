#pragma once

#include "ofMain.h"
#include "EventQueue.h"


// ofApp
//--------------------------------------------------------------------------------
class ofApp : public ofBaseApp
{
public:
  void setup();
  void update();
  void draw();
  
  EventQueue             Q;
  void                   addQueues();
  
  const int              SIZE = 50;
  ofPoint                pos;
  ofFloatColor           color;
  vector< ofPoint >      points;
  vector< ofFloatColor > colors;
};
