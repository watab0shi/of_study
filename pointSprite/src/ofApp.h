#pragma once

#include "ofMain.h"
#include "Particles.h"
#include "PointSprite.h"


// ofApp
//--------------------------------------------------------------------------------
class ofApp : public ofBaseApp
{
public:
  void setup();
  void update();
  void draw();
  
  Particles   particles;
  PointSprite pointSprite;
};
