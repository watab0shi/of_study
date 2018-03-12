//
//  AttractPoint.h
//  motion_particle
//
//  Created by //wat on 2017/07/30.
//
//

#ifndef AttractPoint_h
#define AttractPoint_h

#include "ofMain.h"


// AttractPoint
//--------------------------------------------------------------------------------
struct AttractPoint
{
  ofPoint pos;
  float   range;
  
  void draw()
  {
    ofFill();
    ofSetColor( 0, 128 );
    ofDrawCircle( pos, range );
  }
  
  void debugDraw()
  {
    ofNoFill();
    ofSetColor( 255 );
    ofDrawCircle( pos, range );
    
    ofFill();
    ofSetColor( 0, 128 );
    ofDrawCircle( pos, range );
    
    ofSetColor( 192 );
    ofDrawCircle( pos, 4 );
  }
};


#endif /* AttractPoint_h */
