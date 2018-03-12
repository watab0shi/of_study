#include "ofApp.h"


// setup
//------------------------------------------------------------
void ofApp::setup()
{
  // gui
  setupGui();
  
  GridPoint::setPointSize( 4 );
  Route::setLineWidth( 2 );
  Route::setNumExcludePointsOfLastLine( 2 );
  Route::setClosingMode( static_cast< Route::ClosingMode >( closingMode.get() ) );
  Route::setStoppingDuration( stoppingDuration );
  Route::setNumExcludePointsOfLastLine( numExcludePoints );
  
  w = GRID_WIDTH;
  h = GRID_HEIGHT + GridPoint::getPointSize();
  
  // allocate fbo
  fbo.allocate( w, h, GL_RGB, 1 );
  fbo.begin();
  {
    ofClear( 0 );
  }
  fbo.end();
  
  syphonServer.setName( "openFrameworks" );
  
  // resize window
  ofSetWindowShape( w / 2, h / 2 );
  
  // grid生成 ( 8 + 1 ) x ( ( 6 * 2 ) + 1 )
  grid.setup( 9, 13, GRID_WIDTH, GRID_HEIGHT );
  
  // ルート生成
  int x[] = {  0,  4, 8 };
  int y[] = { 12, 12, 12 };
  for( int i = 0; i < 3; ++i )
  {
    routes.emplace_back( i, grid.getPointAt( x[ i ], y[ i ] ), routeColors[ i ], maxNumLines, routeSpeed, &routes );
    routes.back().setDrawingSpeed( routeSpeed );
  }
  
  ofEnableAlphaBlending();
  ofDisableAntiAliasing();
  ofDisableSmoothing();
  ofSetVerticalSync( true );
  ofSetFrameRate( 30 );
  ofBackground( 0 );
}


// update
//------------------------------------------------------------
void ofApp::update()
{
  fps              = floor( ofGetFrameRate() * 10 ) / 10;
  stoppingDuration = floor( stoppingDuration * 10 ) / 10;
  
  
  // 追加分の Route を一時的にいれておく用
  vector< Route > newRoutes;
  
  // ルート 更新と削除
  auto f = [ this, &newRoutes ]( Route& _r ){
    _r.update();
    
    if( _r.isClosed() )
    {
      // 終点のかぶりがおきないように routes と newRoutes を合わせた vector をわたす
      vector< Route > otherRoutes = routes;
      otherRoutes.insert( otherRoutes.end(), newRoutes.begin(), newRoutes.end() );
      
      // 新しいルート生成
      newRoutes.emplace_back( _r.getId(), _r.getEndPoint(), _r.getColor(), maxNumLines, routeSpeed, _r.getLine(), &otherRoutes );
      newRoutes.back().setDrawingSpeed( routeSpeed );
    }
    
    return _r.isClosed();
  };
  
  ofRemove( routes, f );
  
  // 追加分があったら routes の最後尾に追加
  if( newRoutes.size() > 0 ) routes.insert( routes.end(), newRoutes.begin(), newRoutes.end() );
  
  ofEnableAlphaBlending();
  // draw in fbo
  fbo.begin();
  {
    ofClear( 0 );
    
    ofPushMatrix();
    {
      // pointSizeの半分下にさげる
      ofTranslate( 0, GridPoint::getPointSize() * .5 );
    
      // グリッド描画
      grid.draw();
      
      // ルート描画
      for( auto& r : routes ) r.draw();
    }
    ofPopMatrix();
  }
  fbo.end();
  
  syphonServer.publishTexture( &fbo.getTexture() );
}


// draw
//------------------------------------------------------------
void ofApp::draw()
{
  ofEnableAlphaBlending();
  ofSetColor( 255, 255 );
  fbo.draw( 0, 0, ofGetWidth(), ofGetHeight() );
  
  // gui
  if( visibleGui ) gui.draw();
}


// keyPressed
//------------------------------------------------------------
void ofApp::keyPressed( int _key )
{
  // gui
  if( _key == ' ' )
  {
    visibleGui = !visibleGui;
  }
  
  // maxNumLines
  if( _key == '1' )
  {
    maxNumLines = MAX( maxNumLines - 1, 1 );
  }
  if( _key == '2' )
  {
    maxNumLines = MIN( maxNumLines + 1, 50 );
  }
  
  // routeSpeed
  if( _key == 'q' )
  {
    routeSpeed = MAX( routeSpeed - 1, 1 );
    for( auto& r : routes ) r.setDrawingSpeed( routeSpeed );
  }
  if( _key == 'w' )
  {
    routeSpeed = MIN( routeSpeed + 1, 100 );
    for( auto& r : routes ) r.setDrawingSpeed( routeSpeed );
  }
  
  // stoppingDuration
  if( _key == 'a' )
  {
    stoppingDuration = MAX( stoppingDuration - 0.1, 0.0 );
    Route::setStoppingDuration( stoppingDuration );
  }
  if( _key == 's' )
  {
    stoppingDuration = MIN( stoppingDuration + 0.1, 5.0 );
    Route::setStoppingDuration( stoppingDuration );
  }
  
  // set neighbors
  if( _key == '-' )
  {
    // 下半分でとどまる
    // 上半分にいるときはそのうち下にもどってくる
    grid.setNeighbors( static_cast< int >( grid.getRows() / 2 ) + 1, 0, 0, 0 );
  }
  if( _key == '=' )
  {
    // 全面自由に動き回る
    grid.setNeighbors( 0, 0, 0, 0 );
  }
}


// keyReleased
//------------------------------------------------------------
void ofApp::keyReleased( int _key )
{
}


// mouseMoved
//------------------------------------------------------------
void ofApp::mouseMoved( int _x, int _y )
{
}


// mouseDragged
//------------------------------------------------------------
void ofApp::mouseDragged( int _x, int _y , int _button )
{
}


// mousePressed
//------------------------------------------------------------
void ofApp::mousePressed( int _x, int _y , int _button )
{
}


// mouseReleased
//------------------------------------------------------------
void ofApp::mouseReleased( int _x, int _y , int _button )
{
}


// mouseEntered
//------------------------------------------------------------
void ofApp::mouseEntered( int _x, int _y ){

}


// mouseExited
//------------------------------------------------------------
void ofApp::mouseExited( int _x, int _y )
{
}


// windowResized
//------------------------------------------------------------
void ofApp::windowResized( int _w, int _h )
{
}


// gotMessage
//------------------------------------------------------------
void ofApp::gotMessage( ofMessage _msg )
{
}


// dragEvent
//------------------------------------------------------------
void ofApp::dragEvent( ofDragInfo _dragInfo )
{
}


// exit
//------------------------------------------------------------
void ofApp::exit()
{
  // save gui settings
  gui.saveToFile( settingFile.getAbsolutePath() );
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
  
  routeParams.setName( "Route" );
  routeParams.add( closingMode.set( "ClosingMode", 1, 0, 1 ) );
  routeParams.add( maxNumLines.set( "MaxNumLines", 1, 1, 50 ) );
  routeParams.add( routeSpeed.set( "RouteSpeed", 10, 1, 100 ) );
  routeParams.add( stoppingDuration.set( "StoppingDuration", 2., 0., 10. ) );
  routeParams.add( numExcludePoints.set( "NumExcludePoints", 2, 0, 50 ) );
  
  // スライダー変更イベントを関数に紐付け
  closingMode.addListener( this, &ofApp::onClosingModeChanged );
  routeSpeed.addListener( this, &ofApp::onRouteSpeedChanged );
  stoppingDuration.addListener( this, &ofApp::onStoppingDurationChanged );
  numExcludePoints.addListener( this, &ofApp::onNumExcludePointsChanged );
  
  params.setName( "GridRouting" );
  params.add( fps.set( "FPS", 0, 0, 60 ) );
  params.add( routeParams );
  
  gui.setup( params );
  gui.setUseTTF( true );
  gui.setSize( 255, gui.getShape().height + 10 );
  gui.setHeaderBackgroundColor( ofColor::fromHsb( hue, 255, 180 ) );
  
  // load gui settings
  settingFile = ofFile( ofToDataPath( "gui/settings.xml" ) );
  if( settingFile.exists() ) gui.loadFromFile( settingFile.getAbsolutePath() );
  
  visibleGui = true;
}


// closingModeChanged
//----------------------------------------
void ofApp::onClosingModeChanged( int& _v )
{
  Route::setClosingMode( static_cast< Route::ClosingMode >( _v ) );
}


// onRouteSpeedChanged
//----------------------------------------
void ofApp::onRouteSpeedChanged( int& _v )
{
  for( auto& r : routes ) r.setDrawingSpeed( _v );
}


// onStoppingDurationChanged
//----------------------------------------
void ofApp::onStoppingDurationChanged( float& _v )
{
  Route::setStoppingDuration( _v );
}


// onNumExcludePointsChanged
//----------------------------------------
void ofApp::onNumExcludePointsChanged( int& _v )
{
  Route::setNumExcludePointsOfLastLine( _v );
}
