#pragma once

#include "ofMain.h"
#include "Particles.h"


// Particles
//--------------------------------------------------------------------------------
class PointSprite
{
private:
  ofVboMesh vboMesh;
  ofImage   texture;
  ofShader  shader;
  
public:
  PointSprite()
  {
    loadTexture( "images/texture.png" );
    loadShader( "shaders/Billboard" );
    
    vboMesh.clear();
    vboMesh.setUsage( GL_DYNAMIC_DRAW );
    vboMesh.setMode( OF_PRIMITIVE_POINTS );
  }
  
  void loadTexture( string _fileName )
  {
    ofDisableArbTex();
    texture.load( _fileName );
    ofEnableArbTex();
  }
  
  void loadShader( string _shaderName )
  {
    shader.load( _shaderName );
  }
  
  void update( Particles& _ps )
  {
    vboMesh.clear();
    
    for( auto& p : _ps.get() )
    {
      vboMesh.addVertex( p.getPosition() );
      vboMesh.addNormal( ofVec3f( p.getRadius() * 2, 0, 0 ) );
      vboMesh.addColor( ( ofFloatColor )p.getColor() );
    }
  }
  
  void draw()
  {
    shader.begin();
    {
      ofEnablePointSprites();
      texture.getTexture().bind();
      vboMesh.draw();
      texture.getTexture().unbind();
      ofDisablePointSprites();
    }
    shader.end();
  }
};