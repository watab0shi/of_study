#pragma once

#include "ofMain.h"
#include "Particles.h"


// Particles
//--------------------------------------------------------------------------------
class PointSprite
{
private:
  ofVboMesh vboMesh;
  ofImage   textures[ 3 ];
  ofShader  shader;
  
public:
  PointSprite()
  {
    loadTextures( "images" );
    loadShader( "shaders/Billboard" );
    
    vboMesh.clear();
    vboMesh.setUsage( GL_DYNAMIC_DRAW );
    vboMesh.setMode( OF_PRIMITIVE_POINTS );
  }
  
  void loadTextures( string _dirName )
  {
    ofDirectory dir( _dirName );
    dir.allowExt( "png" );
    dir.listDir();
    
    ofDisableArbTex();
    int i = 0;
    for( auto& f : dir.getFiles() )
    {
      textures[ i ].load( f.path() );
      ++i;
      if( i == 3 ) break;
    }
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
      vboMesh.addNormal( ofVec3f( p.getRadius() * 2, p.getTextureId(), 0 ) );
      vboMesh.addColor( ( ofFloatColor )p.getColor() );
    }
  }
  
  void draw()
  {
    shader.begin();
    {
      shader.setUniformTexture( "tex0", textures[ 0 ], 0 );
      shader.setUniformTexture( "tex1", textures[ 1 ], 1 );
      shader.setUniformTexture( "tex2", textures[ 2 ], 2 );
      
      ofEnablePointSprites();
      vboMesh.draw();
      ofDisablePointSprites();
    }
    shader.end();
  }
};