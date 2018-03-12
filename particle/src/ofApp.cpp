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
}


// draw
//------------------------------------------------------------
void ofApp::draw()
{
  particles.draw();
  
  ofDrawBitmapStringHighlight( ofToString( particles.size() ), 20, 40 );
}