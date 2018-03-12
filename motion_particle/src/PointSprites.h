//
//  PointSprites.h
//  motion_particle
//
//  Created by //wat on 2017/07/30.
//
//

#ifndef PointSprites_h
#define PointSprites_h

#include "ofMain.h"
#include "Particle.h"


// PointSprite
//--------------------------------------------------------------------------------
class PointSprites
{
public:
  void setup( int _num );
  void update( vector< Particle >* _particles );
  void draw();
  
  void loadTexture( string _fileName );
  void loadShader( string _shaderName );
  
private:
  ofVboMesh vboMesh;
  ofImage   texture;
  ofShader  shader;
};

#endif /* PointSprites_h */
