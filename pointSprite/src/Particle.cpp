
#include "Particle.h"


// Particle
//------------------------------------------------------------
Particle::Particle()
: pos( 0 ), vel( 0 ), radius( 0 ), color( 0 ), life( 1 ), bDead( false )// メンバイニシャライザ 各メンバ変数のコンストラクタとして機能
{
}

Particle::Particle( ofPoint _pos, ofPoint _vel, float _radius, ofColor _color, float _life )
: pos( _pos ), vel( _vel ), radius( _radius ), color( _color ), life( _life ), bDead( false )
{
}


// update
//------------------------------------------------------------
void Particle::update()
{
  pos += vel;
  
  if( ofGetElapsedTimef() > life )
  {
    if( radius > 0.1 )
    {
      radius -= radius / 10;
    }
    else
    {
      radius = 0;
      bDead  = true;
    }
  }
}


// draw
//------------------------------------------------------------
void Particle::draw()
{
  ofFill();
  ofSetColor( color );
  
  ofPushMatrix();
  {
    ofTranslate( pos );
    ofDrawCircle( 0, 0, radius );
  }
  ofPopMatrix();
}