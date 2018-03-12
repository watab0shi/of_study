#include "ofApp.h"


// setup
//------------------------------------------------------------
void ofApp::setup()
{
  ofSetFrameRate( 60 );
  ofBackground( 0 );
}


// update
//------------------------------------------------------------
void ofApp::update()
{
  if( ofGetMousePressed() )
  {
    for( int i = 0; i < 10; ++i ) particles.add( ofPoint( mouseX, mouseY ) );
  }
  
  particles.update();
  
  pointSprite.update( particles );
}


// draw
//------------------------------------------------------------
void ofApp::draw()
{
  ofEnableBlendMode( OF_BLENDMODE_ADD );
  pointSprite.draw();
  ofEnableBlendMode( OF_BLENDMODE_ALPHA );
  
  ofDrawBitmapStringHighlight( ofToString( particles.size() ), 20, 40 );
}