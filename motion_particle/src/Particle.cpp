//
//  Particle.cpp
//  motion_particle
//
//  Created by //wat on 2017/07/29.
//
//

#include "Particle.h"


// [ static ] time
//----------------------------------------
shared_ptr< float > Particle::time = nullptr;

void Particle::setTime( const shared_ptr< float >& _time )
{
  Particle::time = _time;
}


// [ static ] collisionFrame
//----------------------------------------
ofRectangle Particle::collisionFrame( 0, 0, 0, 0 );

void Particle::setCollisionFrame( int _x, int _y, int _w, int _h )
{
  Particle::collisionFrame.set( _x, _y, _w, _h );
}


// [ static ] mode
//----------------------------------------
shared_ptr< Particle::Mode > Particle::mode = nullptr;

void Particle::setMode( const shared_ptr< Particle::Mode >& _mode )
{
  Particle::mode = _mode;
}


// [ static ] attractPoints
//----------------------------------------
shared_ptr< vector< AttractPoint > > Particle::attractPoints = nullptr;

void Particle::setAttractPoints( const shared_ptr< vector< AttractPoint > >& _attractPoints )
{
  Particle::attractPoints = _attractPoints;
}


// Particle
//----------------------------------------
Particle::Particle()
{
  reset();
}


// reset
//----------------------------------------
void Particle::reset()
{
  baseRadius = 10 + ofRandom( 14 );
  radius     = baseRadius;
  
  pos        = getRandomPos( collisionFrame, radius, radius );
  vel.set( ofRandomf(), ofRandomf(), 0 );
  
  damping    = ofRandom( 0.985, 0.994 );
  
  force.set( 0, 0, 0 );
  
  nColorRange = ofRandom( 32 );
}


// update
//----------------------------------------
void Particle::update()
{
  AttractPoint target  = { ofPoint( 0, 0 ), 0 };
  float        closest = 99999;
  
  // find closest point
  for( auto& a : ( *attractPoints ) )
  {
    float length = ( a.pos - pos ).length();
    if( length < closest )
    {
      closest = length;
      target  = a;
    }
  }
  
  // for noise
  ofVec2f np( pos * 0.006 );
  float   nt     = ( *Particle::time ) * 0.2;
  float   cNoise = ofNoise( nt ) * 32;
  
  // calc direction to target
  force      = target.pos - pos;
  float dist = fabs( force.length() );
  force.normalize();
  
  // slow down velocity
  vel *= damping;
  
  // update color & velocity in current mode
  switch( ( *mode ) )
  {
    // PARTICLE_MODE_ATTRACT
    //----------------------------------------
    case PARTICLE_MODE_ATTRACT:
      color.set( 192 + cNoise, 92 - cNoise, 64 - cNoise );
      
      if( target.range != 0 )
      {
        vel += force * 0.5;
      }
      else
      {
        force.x = ofSignedNoise( np.x, np.y, nt );
        force.y = ofSignedNoise( np.x, np.y, nt + 1000 );

        vel    += force * 0.02;
      }
      break;
      
    // PARTICLE_MODE_REPEL
    //----------------------------------------
    case PARTICLE_MODE_REPEL:
      color.set( 222 + cNoise, 210 + cNoise, 64 - cNoise );
      
      if( ( target.range != 0 ) && ( dist < target.range ) )
      {
        vel -= force * 0.6;
      }
      else
      {
        force.x = ofSignedNoise( np.x, np.y, nt );
        force.y = ofSignedNoise( np.x, np.y, nt + 1000 );
        
        vel    += force * 0.02;
      }
      break;
      
    // PARTICLE_MODE_SNOW
    //----------------------------------------
    case PARTICLE_MODE_SNOW:
      color.set( 255 - cNoise, 255 - cNoise, 255 );
      
      if( ( target.range != 0 ) && ( dist < ( target.range * 1.5 ) ) )
      {
        vel *= 0.95;
      }
      else
      {
        float fakeWind = ofSignedNoise( np.x * 0.4, np.y * 0.4, nt ) * 0.015;
        
        force.x = fakeWind + ( ofSignedNoise( np.x * 0.6, np.y * 0.6, ( nt * 2.0 ) + 1000 ) * 0.03 );
        force.y = fabs( ofSignedNoise( np.x * 0.2, np.y * 0.2, ( nt * 2.0 ) + 2000 ) ) * 0.05 + 0.005;
        
        vel    += force * 1.2;
      }
      
      // back to top
      if( pos.y - ( radius / 3 ) > collisionFrame.getBottom() )
      {
        pos.x = getRandom( collisionFrame.getLeft(), collisionFrame.getRight(), radius );
        pos.y = collisionFrame.getTop() - ( radius / 3 );
      }
      break;
    
    // PARTICLE_MODE_NEAREST
    //----------------------------------------
    case PARTICLE_MODE_NEAREST:
      color.set( 64 - cNoise, 222 + cNoise, 222 + cNoise );
      
      if( target.range != 0 )
      {
        force = target.pos - pos;
        
        if( dist < target.range )
        {
          vel -= force * 0.003;
        }
        else if( ( dist >= target.range ) && ( dist < target.range * 2 ) )
        {
          vel += force * 0.006;
        }
      }
      else
      {
        force.x = ofSignedNoise( np.x, np.y, nt );
        force.x = ofSignedNoise( np.x, np.y, nt + 1000 );
        
        vel += force * 0.003;
      }
      break;
      
    // PARTICLE_MODE_FLOW
    //----------------------------------------
    case PARTICLE_MODE_FLOW:
      color.setHsb( 180 + cNoise, 255, 255 );
      
      if( ( target.range != 0 ) && ( dist < target.range * 1.5 ) )
      {
        vel.x -= force.x * 0.2;
        vel.y *= 1.02;
      }
      else
      {
        float fakeWind = ofSignedNoise( np.x * 0.05, np.y * 0.05, nt ) * 0.02;
        
        force.x = fakeWind + ofSignedNoise( np.x * 0.15, np.y * 0.15, nt * 2 ) * 0.04;
        force.y = fabs( ofSignedNoise( np.x * 0.015, np.y * 0.15, ( nt * 2 ) + 1000 ) * 0.05 ) + 0.005;
        
        vel += force * 1.5;
      }
      
      // back to top
      if( pos.y - ( radius / 3 ) > collisionFrame.getBottom() )
      {
        pos.x = getRandom( collisionFrame.getLeft(), collisionFrame.getRight(), radius );
        pos.y = collisionFrame.getTop() - ( radius / 3 );
      }
      break;
      
    default:
      break;
  }
  
  // update position & radius
  pos   += vel;
  radius = baseRadius + fabs( vel.length() ) * 1.2;
  
  // collision to frame : x
  float cr = radius / 3;
  if( ( pos.x - cr ) < collisionFrame.getLeft() )
  {
    pos.x  = collisionFrame.x + cr;
    vel.x *= -1.0;
  }
  else if( ( pos.x + cr ) > ( collisionFrame.getRight() ) )
  {
    pos.x  = ( collisionFrame.x + collisionFrame.width ) - cr;
    vel.x *= -1.0;
  }
  
  // skip y collision in SNOW & FLOW mode
  if( ( *mode ) == PARTICLE_MODE_SNOW || ( *mode ) == PARTICLE_MODE_FLOW ) return;
  
  // collision to frame : y
  if( ( pos.y - cr ) < collisionFrame.getTop() )
  {
    pos.y  = collisionFrame.x + cr;
    vel.y *= -1.0;
  }
  else if( ( pos.y + cr ) > ( collisionFrame.getBottom() ) )
  {
    pos.y  = ( collisionFrame.y + collisionFrame.height ) - cr;
    vel.y *= -1.0;
  }
}


// draw
//----------------------------------------
void Particle::draw()
{
  ofSetColor( color );
  ofDrawCircle( pos, radius );
}


// getPosition
//----------------------------------------
ofPoint Particle::getPosition()
{
  return pos;
}


// getRadius
//----------------------------------------
float Particle::getRadius()
{
  return radius;
}


// getColor
//----------------------------------------
ofColor Particle::getColor()
{
  return color;
}
