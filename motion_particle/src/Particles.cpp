//
//  Particles.cpp
//  motion_particle
//
//  Created by //wat on 2017/07/30.
//
//

#include "Particles.h"


// setup
//----------------------------------------
void Particles::setup( int _num )
{
  time          = shared_ptr< float >( new float );
  mode          = shared_ptr< Particle::Mode >( new Particle::Mode );
  attractPoints = shared_ptr< vector< AttractPoint > >( new vector< AttractPoint >() );
  
  Particle::setTime( time );
  Particle::setCollisionFrame( 0, 0, ofGetWidth(), ofGetHeight() );
  Particle::setMode( mode );
  Particle::setAttractPoints( attractPoints );
  
  particles.resize( _num );
  
  // pointSprite
  pointSprites.loadShader( "shaders/PointSprite" );
  pointSprites.loadTexture( "images/texture.png" );
  pointSprites.setup( _num );
}


// reset
//----------------------------------------
void Particles::reset()
{
  for( auto& p : particles ) p.reset();
}


// update
//----------------------------------------
void Particles::update()
{
  ( *time ) = ofGetElapsedTimef();
  
  // update particles & update vboMesh
  pointSprites.update( &particles );
}


// draw
//----------------------------------------
void Particles::draw()
{
  // draw particles
  pointSprites.draw();
  
  // draw attract points
  for( auto& a : ( *attractPoints ) ) a.draw();
}


// windowResized
//----------------------------------------
void Particles::windowResized( int _w, int _h )
{
  Particle::setCollisionFrame( 0, 0, _w, _h );
  reset();
}


// nextMode
//----------------------------------------
void Particles::nextMode()
{
  ( *mode ) = static_cast< Particle::Mode >( ( static_cast< int >( *mode ) + 1 ) % static_cast< int >( Particle::Mode::size ) );
}


// prevMode
//----------------------------------------
void Particles::prevMode()
{
  int size = static_cast< int >( Particle::Mode::size );
  ( *mode ) = static_cast< Particle::Mode >( ( static_cast< int >( *mode ) - 1 + size ) % size );
}


// clearAttractPoints
//----------------------------------------
void Particles::clearAttractPoints()
{
  attractPoints->clear();
  attractPoints->shrink_to_fit();
}


// addAttractPoint
//----------------------------------------
void Particles::addAttractPoint( int _x, int _y, float _range )
{
  attractPoints->push_back( { ofPoint( _x, _y ), _range } );
}


// getMode
//----------------------------------------
Particle::Mode Particles::getMode()
{
  return ( *mode );
}
