//
//  PointSprites.cpp
//  motion_particle
//
//  Created by //wat on 2017/07/30.
//
//

#include "PointSprites.h"


// setup
//----------------------------------------
void PointSprites::setup( int _num )
{
  vboMesh.setUsage( GL_DYNAMIC_DRAW );
  vboMesh.setMode( OF_PRIMITIVE_POINTS );
  
  vboMesh.getVertices().resize( _num );
  vboMesh.getNormals().resize( _num );
  vboMesh.getColors().resize( _num );
}


// update
//----------------------------------------
void PointSprites::update( vector< Particle >* _particles )
{
  int i = 0;
  for( auto& p : ( *_particles ) )
  {
    p.update();// call particle's update here
    
    vboMesh.setVertex( i, static_cast< ofVec3f >( p.getPosition() ) );
    vboMesh.setNormal( i, ofVec3f( p.getRadius(), 0, 0 ) );
    vboMesh.setColor( i, static_cast< ofFloatColor >( p.getColor() ) );
    ++i;
  }
}


// draw
//----------------------------------------
void PointSprites::draw()
{
  shader.begin();
  
  ofEnableBlendMode( OF_BLENDMODE_ADD );
  
  ofEnablePointSprites();
  
  texture.getTexture().bind();
  
  vboMesh.draw();
  
  texture.getTexture().unbind();
  
  ofDisablePointSprites();
  
  ofEnableBlendMode( OF_BLENDMODE_ALPHA );
  
  shader.end();
}


// loadTexture
//----------------------------------------
void PointSprites::loadTexture( string _fileName )
{
  ofDisableArbTex();
  texture.load( _fileName );
}


// loadShader
//----------------------------------------
void PointSprites::loadShader( string _shaderName )
{
  shader.load( _shaderName );
}
