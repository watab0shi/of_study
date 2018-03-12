//
//  Particle.h
//  motion_particle
//
//  Created by //wat on 2017/07/29.
//
//

#ifndef Particle_h
#define Particle_h

#include "ofMain.h"
#include "commonUtils.h"
#include "AttractPoint.h"


// Particle
//--------------------------------------------------------------------------------
class Particle
{
public:
  Particle();
  
  void reset();
  void update();
  void draw();
  
  // particle mode
  enum Mode
  {
    PARTICLE_MODE_ATTRACT,
    PARTICLE_MODE_REPEL,
    PARTICLE_MODE_SNOW,
    PARTICLE_MODE_NEAREST,
    PARTICLE_MODE_FLOW,
    size// use for number of modes
  };
  
  // setter
  void    setTargetPosition( ofPoint _pos );
  
  // getter
  ofPoint getPosition();
  float   getRadius();
  ofColor getColor();
  
  // static setter
  static void setTime( const shared_ptr< float >& _time );
  static void setCollisionFrame( int _x, int _y, int _w, int _h );
  static void setMode( const shared_ptr< Mode >& _mode );
  static void setAttractPoints( const shared_ptr< vector< AttractPoint > >& _attractPoints );
  
private:
  ofPoint pos;
  ofPoint vel;
  ofPoint force;
  float   damping;
  float   baseRadius, radius;
  ofColor color;
  float   nColorRange;
  
  // static variables
  static shared_ptr< float >                  time;
  static ofRectangle                          collisionFrame;
  static shared_ptr< Mode >                   mode;
  static shared_ptr< vector< AttractPoint > > attractPoints;
};



#endif /* Particle_h */
