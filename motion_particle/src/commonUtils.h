//
//  commonUtils.h
//  motion_particle
//
//  Created by //wat on 2017/07/30.
//
//

#ifndef commonUtils_h
#define commonUtils_h

#include "ofMain.h"


// getRandom
//----------------------------------------
static float getRandom( float _min, float _max, float _padding )
{
  return ofRandom( _min + _padding, _max - _padding );
}


// getRandomPos
//----------------------------------------
static ofPoint getRandomPos( ofRectangle _rect, float _xPadding = 0, float _yPadding = 0 )
{
  return ofPoint( getRandom( _rect.getLeft(), _rect.getRight(), _xPadding ), getRandom( _rect.getTop(), _rect.getBottom(), _yPadding ) );
}


#endif /* commonUtils_h */
