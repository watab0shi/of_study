#include "ofApp.h"


// setup
//------------------------------------------------------------
void ofApp::setup()
{
  oscPort = 11111;
  oscReceiver.setup( oscPort );
  
  ofBackground( 90 );
  ofSetVerticalSync( true );
  ofSetFrameRate( 60 );// <---------- 60fps!!!
}


// update
//------------------------------------------------------------
void ofApp::update()
{
//  attractPoints.clear();// <----------- don't do this!!!
  
  while( oscReceiver.hasWaitingMessages() )
  {
    ofxOscMessage msg;
    oscReceiver.getNextMessage( msg );
    string address = msg.getAddress();
    
    if( address == "/test/attractpoint/size" )
    {
      int size = msg.getArgAsInt( 0 );
      ofLog() << "[osc] size  : " << size;
      
      // 受信したサイズが現在のサイズより小さかったら、同じになるまで pop_back()
      if( size < attractPoints.size() )
      {
        while( attractPoints.size() != size ) attractPoints.pop_back();
      }
    }
    
    if( address == "/test/attractpoint/point" )
    {
      int     idx   = msg.getArgAsInt( 0 );
      ofPoint pos( msg.getArgAsFloat( 1 ), msg.getArgAsFloat( 2 ) );
      float   range = msg.getArgAsFloat( 3 );
      
      ofLog() << "[osc] --------------------";
      ofLog() << "[osc] idx   : " << idx;
      ofLog() << "[osc] pos   : " << pos;
      ofLog() << "[osc] range : " << range;
      
      // 現在のサイズ以上の index がきたら、新規追加
      if( idx >= attractPoints.size() )
      {
        attractPoints.push_back( { pos, range } );
      }
      // 現在のサイズ未満の index がきたら、いまの要素に代入
      else
      {
        attractPoints.at( idx ).pos   = pos;
        attractPoints.at( idx ).range = range;
      }
    }
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
  ofDrawBitmapStringHighlight( "Receiver", 20, 40 );
}
