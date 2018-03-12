#pragma once

#include "ofMain.h"



static void vertex2f( ofVec2f _v )
{
  glVertex2f( _v.x, _v.y );
}

static void vertex3f( ofVec3f _v )
{
  glVertex3f( _v.x, _v.y, _v.z );
}