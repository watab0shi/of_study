#include "ofApp.h"


// setup
//------------------------------------------------------------
void ofApp::setup()
{
  points.emplace_back(  SIZE, -SIZE );// 右上の座標
  points.emplace_back(  SIZE,  SIZE );// 右下の座標
  points.emplace_back( -SIZE,  SIZE );// 左下の座標
  points.emplace_back( -SIZE, -SIZE );// 左上の座標
  
  colors.emplace_back( ofFloatColor::fromHsb( 0.25, 0.7, 0.9 ) );// 右上の色
  colors.emplace_back( ofFloatColor::fromHsb( 0.50, 0.7, 0.9 ) );// 右下の色
  colors.emplace_back( ofFloatColor::fromHsb( 0.75, 0.7, 0.9 ) );// 左下の色
  colors.emplace_back( ofFloatColor::fromHsb( 0.00, 0.7, 0.9 ) );// 左上の色
  
  // 初期値は左上
  pos   = points.back();
  color = colors.back();
  
  ofBackground( color );
}


// update
//------------------------------------------------------------
void ofApp::update()
{
  // 一周分のキューが終わったら再び追加してループさせる
  if( Q.size() == 0 ) addQueues();
  
  // キューを更新
  Q.update();
}


// draw
//------------------------------------------------------------
void ofApp::draw()
{
  ofBackground( color );
  
  ofPushMatrix();
  {
    ofTranslate( ofGetWidth()*.5, ofGetHeight()*.5 );
    
    ofFill();
    ofSetColor( 255 );
    ofDrawRectangle( pos - ofPoint( SIZE / 2 ), SIZE, SIZE );
  }
  ofPopMatrix();
}


// addQueues
//------------------------------------------------------------
void ofApp::addQueues()
{
  for( int i = 0; i < points.size(); ++i )
  {
    // 0.7秒間それぞれの position, color に対して値を近づける
    Q.repeat( 0.7, [ this, i ](){
      pos += ( points.at( i ) - pos ) / 8;
      
      // color += ( colors.at( i ) - color ) / 8; だと値がクランプされるため r,g,b,a の float をいじる
      for( int j = 0; j < 4; ++j ) color[ j ] += ( colors.at( i )[ j ] - color[ j ] ) / 8;
    } );
  }
}
