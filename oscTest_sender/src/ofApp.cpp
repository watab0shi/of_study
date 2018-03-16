#include "ofApp.h"


// setup
//------------------------------------------------------------
void ofApp::setup()
{
  oscPort = 11111;
  oscSender.setup( "localhost", oscPort );
  
  for( int i = 0; i < 5; ++i ) addRandomPoint();
  
  ofBackground( 0 );
  ofSetVerticalSync( true );
  ofSetFrameRate( 30 );// <---------- 30fps!!!
}

void ofApp::addRandomPoint()
{
  attractPoints.push_back( { ofPoint( ofRandomWidth(), ofRandomHeight() ), ofRandom( 40, 80 ) } );
}


// update
//------------------------------------------------------------
void ofApp::update()
{
  sendMessages( attractPoints );
}

void ofApp::sendMessages( const vector< AttractPoint >& _points )
{
  ofxOscMessage msg;
  msg.setAddress( "/test/attractpoint/size" );
  msg.addIntArg( _points.size() );// total number of vector
  oscSender.sendMessage( msg );
  
  int i = 0;
  for( auto& p : _points )
  {
    ofxOscMessage msg_;
    msg_.setAddress( "/test/attractpoint/point" );
    msg_.addIntArg( i );//         index
    msg_.addFloatArg( p.pos.x );// position X
    msg_.addFloatArg( p.pos.y );// position Y
    msg_.addFloatArg( p.range );// range
    oscSender.sendMessage( msg_ );
    
    ++i;
  }
}


// draw
//------------------------------------------------------------
void ofApp::draw()
{
  ofNoFill();
  
  int i = 0;
  for( auto& ap : attractPoints )
  {
    ofSetColor( ofColor::fromHsb( i * ( 255 / attractPoints.size() ), 200, 255 ) );
    ofDrawCircle( ap.pos, ap.range );
    ofDrawBitmapStringHighlight( ofToString( i ), ap.pos );
    ++i;
  }
  
  ofDrawBitmapStringHighlight( ofToString( ofGetFrameRate(), 2 ), 20, 20 );
  ofDrawBitmapStringHighlight( "Sender\n\nDrag -> move\n'-'  -> pop_back\n'='  -> push_back", 20, 40 );
}


// keyPressed
//------------------------------------------------------------
void ofApp::keyPressed( int _key )
{
  if( _key == '-' )
  {
    if( attractPoints.size() > 0 ) attractPoints.pop_back();
  }
  if( _key == '=' )
  {
    addRandomPoint();
  }
}

// mouseDragged
//------------------------------------------------------------
void ofApp::mouseDragged( int _x, int _y , int _button )
{
  if( bSelect && ( pointItr != attractPoints.end() ) ) ( *pointItr ).pos.set( _x, _y );
}


// mousePressed
//------------------------------------------------------------
void ofApp::mousePressed( int _x, int _y , int _button )
{
  pointItr = std::find_if( attractPoints.begin(), attractPoints.end(), [ _x, _y ]( AttractPoint& _p ){ return ( ofDist( _x, _y, _p.pos.x, _p.pos.y ) < _p.range ); } );
  
  if( pointItr != attractPoints.end() )
  {
    ( *pointItr ).pos.set( _x, _y );
    bSelect = true;
  }
}


// mouseReleased
//------------------------------------------------------------
void ofApp::mouseReleased( int _x, int _y , int _button )
{
  if( bSelect && ( pointItr != attractPoints.end() ) ) ( *pointItr ).pos.set( _x, _y );
  
  bSelect = false;
}
