#include "ofApp.h"


// setup
//------------------------------------------------------------
void ofApp::setup()
{
  w  = ofGetWidth();
  h  = ofGetHeight();
  hw = w / 2;
  qh = h / 4;
  
  fontSize = 100;
  
  // font.getStringAsPoints()するには load( fileName, fontSize, true, true, true ) と書く
  // load( string filename, int fontsize, bool _bAntiAliased = true, bool _bFullCharacterSet = true, bool makeContours = false )
  font.load( "Menlo-Italic.ttf", fontSize, true, true, true );
  
  smoothing       = 1;
  resampleCount   = 50;
  resampleSpacing = 1;
  
  word = "openFrameworks";
  setOutlines( word );
  
  ofSetFrameRate( 60 );
  ofBackground( 80 );
}


// update
//------------------------------------------------------------
void ofApp::update()
{
  int i = 0;
  for( auto& line : outlines )
  {
    // resampling outlines
    smoothedOutlines.at( i )  = line.getSmoothed( smoothing );// 滑らかに
    reCountedOutlines.at( i ) = line.getResampledByCount( resampleCount );// 指定した頂点数で再サンプル（必ずしも指定数ぴったりになるとは限らない）
    reSpacedOutlines.at( i )  = line.getResampledBySpacing( resampleSpacing );// 指定した長さおきに再サンプル
    
    // connect the last point to the first point
    smoothedOutlines.at( i ).addVertex( smoothedOutlines.at( i ).getVertices().front() );
    reCountedOutlines.at( i ).addVertex( reCountedOutlines.at( i ).getVertices().front() );
    reSpacedOutlines.at( i ).addVertex( reSpacedOutlines.at( i ).getVertices().front() );
    
    ++i;
  }
}


// draw
//------------------------------------------------------------
void ofApp::draw()
{
  // draw outlines
  drawOutlines( smoothedOutlines, hw, qh );//      smoothed
  drawOutlines( reCountedOutlines, hw, qh * 2 );// resampled by count
  drawOutlines( reSpacedOutlines, hw, qh * 3 );//  resampled by spacing
  
  // draw labels
  ofPushMatrix();
  {
    ofTranslate( 10, -fontSize * .5 );
    ofDrawBitmapStringHighlight( "Smoothing       : " + ofToString( smoothing ),       0, qh );
    ofDrawBitmapStringHighlight( "ResampleCount   : " + ofToString( resampleCount ),   0, qh * 2 );
    ofDrawBitmapStringHighlight( "ResampleSpacing : " + ofToString( resampleSpacing ), 0, qh * 3 );
  }
  ofPopMatrix();
}


// keyPressed
//------------------------------------------------------------
void ofApp::keyPressed( int _key )
{
  // タイピングできるように ( スペース以外 )
  if( _key >= 32 && _key <= 126 && _key != 32 )
  {
    word.push_back( static_cast< char >( _key ) );// int から char にキャストして文字列に追加
    setOutlines( word );// アウトライン再設定
  }
  // バックスペースのときは最後の文字を消す
  else if( _key == OF_KEY_BACKSPACE )
  {
    if( word.size() > 0 ) word.pop_back();
    
    if( word.size() == 0 ) clearOutlines();// 文字がないときはクリアだけ
    else                   setOutlines( word );// アウトライン再設定
  }
}


// mouseMoved
//------------------------------------------------------------
void ofApp::mouseMoved( int _x, int _y )
{
  // mouseX をもとにパラメーター更新
  smoothing       = static_cast< int >( ofMap( _x, 0, w, 1, 20, true ) );
  resampleCount   = static_cast< int >( ofMap( _x, 0, w, 50, 5, true ) );
  resampleSpacing = static_cast< int >( ofMap( _x, 0, w, 1, 100, true ) );
}


// windowResized
//------------------------------------------------------------
void ofApp::windowResized( int _w, int _h )
{
  w  = _w;
  h  = _h;
  hw = w * .5;
  qh = h * .25;
}


// clearOutlines
//------------------------------------------------------------
void ofApp::clearOutlines()
{
  outlines.clear();
  smoothedOutlines.clear();
  reCountedOutlines.clear();
  reSpacedOutlines.clear();
}


// setOutlines
//------------------------------------------------------------
void ofApp::setOutlines( string _word )
{
  // アウトラインをクリアしてから再設定する
  clearOutlines();
  
  // 真ん中指定で表示させるためのオフセット座標 fontは左下原点なので ( -w / 2, h / 2 ) になる
  ofPoint offset( -font.stringWidth( _word ) / 2, font.stringHeight( _word ) / 2 );
  
  // font.getStringAsPoints() で取れるのは vector< ofTTFCharacter >
  // ofTTFCharacter は ofPath の名前違い
  for( auto& path : font.getStringAsPoints( _word ) )
  {
    // ofPath::getOutline() で取れるのは vector< ofPolyline >
    for( auto& line : path.getOutline() )
    {
      // offsetを加算するために頂点を一旦変数に格納する
      vector< ofPoint > points = line.getVertices();
      
      // transform を使うとfor文をまわさずにコンテナの要素を一括で操作できる
      // vector< T > src, dst; のとき transform( src.begin(), src.end(), dst.begin(), []( T _t ){ return dstに入れる値; } ); ラムダ関数の引数には src の要素が入ってくる
      // ↓ではラムダ関数の外にある offset を使うため キャプチャする
      transform( line.getVertices().begin(), line.getVertices().end(), points.begin(), [ offset ]( ofPoint _p ){ return _p + offset; } );
      
      // そのままだと最後の頂点と最初の頂点の間が途切れてしまうので、最初の頂点を足してつなげてやる
      points.emplace_back( points.front() );
      
      // 頂点からアウトライン作成
      outlines.emplace_back( points );
    }
  }
  
  // オリジナルを代入してアウトラインの数を合わせておく
  smoothedOutlines  = outlines;
  reCountedOutlines = outlines;
  reSpacedOutlines  = outlines;
}


// drawOutlines
//------------------------------------------------------------
void ofApp::drawOutlines( vector< ofPolyline >& _outlines, float _x, float _y, bool _bDrawOriginal )
{
  ofPushMatrix();
  {
    ofTranslate( _x, _y );
    
    if( _bDrawOriginal )
    {
      ofSetColor( 255, 30 );
      for( auto& line : outlines ) line.draw();
    }
    
    ofSetColor( 255 );
    for( auto& line : _outlines ) line.draw();
  }
  ofPopMatrix();
}
