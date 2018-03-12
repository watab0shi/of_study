//
//  Particles.h
//  motion_particle
//
//  Created by //wat on 2017/07/30.
//
//

#ifndef Particles_h
#define Particles_h

#include "ofMain.h"
#include "Particle.h"
#include "PointSprites.h"


// Particles
//--------------------------------------------------------------------------------
class Particles
{
public:
  void setup( int _num );
  void reset();
  void update();
  void draw();
  void windowResized( int _w, int _h );
  
  void nextMode();
  void prevMode();
  
  void clearAttractPoints();
  void addAttractPoint( int _x, int _y, float _range );
  
  Particle::Mode getMode();
  
private:
  vector< Particle >                   particles;
  
  shared_ptr< float >                  time;
  shared_ptr< Particle::Mode >         mode;
  shared_ptr< vector< AttractPoint > > attractPoints;
  
  PointSprites                         pointSprites;
};

#endif /* Particles_h */
