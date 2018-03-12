#include "ofApp.h"


const int fadeAmounts[] = {
  80,//  PARTICLE_MODE_ATTRACT
  128,// PARTICLE_MODE_REPEL
  255,// PARTICLE_MODE_SNOW
  64,//  PARTICLE_MODE_NEAREST
  26//   PARTICLE_MODE_FLOW
};


// setup
//----------------------------------------
void ofApp::setup()
{
  // basic variables
  w          = ofGetWidth();
  h          = ofGetHeight();
  frameRate  = 30;
  
  
  // gui
  setupGui();
  
  // particles
  particles.setup( 15000 );
  
  // fbo
  fbo.allocate( w, h, GL_RGB32F_ARB );
  
  fbo.begin();
  {
    ofClear( 0, 255 );
  }
  fbo.end();
  
  
  // application settings
  ofSetVerticalSync( true );
  ofEnableAntiAliasing();
  ofShowCursor();
  ofSetCircleResolution( 48 );
  
  ofSetFrameRate( frameRate );
  ofBackground( 0 );
}


// update
//----------------------------------------
void ofApp::update()
{
  fps = floor( ofGetFrameRate() * 10 ) / 10;
  
  // update particles
  particles.update();
  
  // draw in fbo
  fbo.begin();
  {
    // fading
    ofFill();
    ofSetColor( 0, fadeAmounts[ mode ] );
    ofDrawRectangle( 0, 0, w, h );
    
    // draw particles
    particles.draw();
  }
  fbo.end();
}


// draw
//----------------------------------------
void ofApp::draw()
{
  // draw fbo
  ofSetColor( 255 );
  fbo.draw( 0, 0, w, h );
  
  // draw gui
  if( visibleGui ) gui.draw();
}


// keyPressed
//----------------------------------------
void ofApp::keyPressed( int _key )
{
  switch( _key )
  {
    // toggle gui
    case ' ':
      visibleGui = !visibleGui;
      ( visibleGui ) ? ofShowCursor(): ofHideCursor();
      break;
    
    // next mode
    case OF_KEY_LEFT:
      particles.prevMode();
      mode = static_cast< int >( particles.getMode() );
      break;
    
    // previous mode
    case OF_KEY_RIGHT:
      particles.nextMode();
      mode = static_cast< int >( particles.getMode() );
      break;
    
    // reset
    case 'r':
      particles.reset();
      break;
      
    // fullscreen
    case 'f':
      ofToggleFullscreen();
      break;
      
    default:
      break;
  }
}


// keyReleased
//----------------------------------------
void ofApp::keyReleased( int _key )
{
  
}


// mouseMoved
//----------------------------------------
void ofApp::mouseMoved( int _x, int _y )
{
  particles.clearAttractPoints();
  
  // out of window
  if( !ofRectangle( 0, 0, w, h ).inside( _x, _y ) ) return;
  
  particles.addAttractPoint( _x, _y, 100 );
  
//  particles.addAttractPoint( w / 2, h / 2, 150 );
}


// mouseDragged
//----------------------------------------
void ofApp::mouseDragged( int _x, int _y, int _button )
{
  
}


// mousePressed
//----------------------------------------
void ofApp::mousePressed( int _x, int _y, int _button )
{
  
}


// mouseReleased
//----------------------------------------
void ofApp::mouseReleased( int _x, int _y, int _button )
{
  
}


// mouseEntered
//----------------------------------------
void ofApp::mouseEntered( int _x, int _y )
{
  
}


// mouseExited
//----------------------------------------
void ofApp::mouseExited( int _x, int _y )
{
  
}


// windowResized
//----------------------------------------
void ofApp::windowResized( int _w, int _h )
{
  w = _w;
  h = _h;
  
  // reset collision frame & reset particles
  particles.windowResized( w, h );
  
  // resize fbo
  fbo.allocate( w, h, GL_RGB32F_ARB );
  
  fbo.begin();
  {
    ofClear( 0, 255 );
  }
  fbo.end();
}


// dragEvent
//----------------------------------------
void ofApp::dragEvent( ofDragInfo _dragInfo )
{
  
}


// gotMessage
//----------------------------------------
void ofApp::gotMessage( ofMessage _msg )
{
  
}


// exit
//----------------------------------------
void ofApp::exit()
{
  // save gui settings
//  gui.saveToFile( settingFile.getAbsolutePath() );
}


// setupGui
//----------------------------------------
void ofApp::setupGui()
{
  int hue = 0;// gui color
  
  ofxGuiSetFont( "gui/Menlo-Italic.ttf", 10 );
  ofxGuiSetDefaultWidth( 255 );
  ofxGuiSetHeaderColor( ofColor::fromHsb( hue, 255, 180 ) );
  ofxGuiSetFillColor( ofColor::fromHsb( hue, 255, 180 ) );
  ofxGuiSetBackgroundColor( ofColor( 36 ) );
  
  params.setName( "Motion_Particle" );
  params.add( fps.set( "FPS", 0, 0, 60 ) );
  params.add( mode.set( "Mode", 0, 0, static_cast< int >( Particle::Mode::size ) - 1 ) );
  
  gui.setup( params );
  gui.setUseTTF( true );
  gui.setSize( 255, gui.getShape().height + 10 );
  gui.setHeaderBackgroundColor( ofColor::fromHsb( hue, 255, 180 ) );
  
  // load gui settings
  settingFile = ofFile( ofToDataPath( "gui/settings.xml" ) );
//  if( settingFile.exists() ) gui.loadFromFile( settingFile.getAbsolutePath() );
  
  visibleGui = true;
}
