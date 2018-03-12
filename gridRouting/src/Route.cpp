#include "Route.h"
#include "CommonUtils.h"


// static
//------------------------------------------------------------
int Route::lineWidth = 2;
void Route::setLineWidth( int _width )
{
  Route::lineWidth = _width;
}

int Route::numExcludePointsOfLastLine = 2;
void Route::setNumExcludePointsOfLastLine( int _num )
{
  Route::numExcludePointsOfLastLine = _num;
}

Route::ClosingMode Route::closingMode = Route::CLOSING_TRACE;
void Route::setClosingMode( Route::ClosingMode _mode )
{
  Route::closingMode = _mode;
}

float Route::stoppingDuration = 2.;
void Route::setStoppingDuration( float _duration )
{
  Route::stoppingDuration = _duration;
}


// Route
//------------------------------------------------------------
Route::Route()
: endPoint( nullptr ), maxNumLines( 1 ), color( 1., 1., 1. ), alpha( 255 ), drawingIndex( 0 ), drawingSpeed( 5 ), bOpened( false ), openedTime( 0. ), bClosing( false ), bClosed( false )
{
}

Route::Route( int _id, shared_ptr< GridPoint > _point, ofFloatColor _color, int _maxNumLines, int _speed, vector< Route >* _otherRoutes )
: routeId( _id ), endPoint( _point ), color( _color ), alpha( 255 ), maxNumLines( _maxNumLines ), drawingIndex( 0 ), drawingSpeed( _speed ), bOpened( false ), openedTime( 0. ), bClosing( false ), bClosed( false )
{
  // maxNumLines が 1 未満の場合は return
  if( maxNumLines < 1 )
  {
    cout << "[ Route ] maxNumVertices needs 2~ points!" << endl;
    return;
  }
  
  // line に始点を追加
  line.addVertex( static_cast< ofPoint >( *endPoint ) );
  
  // ルート作成
  routing( nullptr, _otherRoutes );
}

Route::Route( int _id, shared_ptr< GridPoint > _point, ofFloatColor _color, int _maxNumLines, int _speed, ofPolyline _lastLine, vector< Route >* _otherRoutes )
: routeId( _id ), endPoint( _point ), color( _color ), alpha( 255 ), maxNumLines( _maxNumLines ), line( _lastLine ), drawingIndex( 0 ), drawingSpeed( _speed ), bOpened( false ), openedTime( 0. ), bClosing( false ), bClosed( false )
{
  // maxNumLines が 1 未満の場合は return
  if( maxNumLines < 1 )
  {
    cout << "[ Route ] maxNumVertices needs 2~ points!" << endl;
    return;
  }
  
  // 一時的に params に入れておいた前回の線をコピー
  ofPolyline lastLine = _lastLine;
  
  // line をクリアして始点を追加
  line.clear();
  line.addVertex( static_cast< ofPoint >( *endPoint ) );
  
  // ルート作成
  routing( &lastLine, _otherRoutes );
}


// routing
//------------------------------------------------------------
void Route::routing( ofPolyline* _lastLine, vector< Route >* _otherRoutes )
{
  bool bEndRouting = false;
  
  // 1点分のルート生成を while でまわして、行き止まりになるか、shape の 点数が maxNumLines に達するまで続ける
  while( !bEndRouting )
  {
    // 進むことができる点の index を一時的に入れておくための配列
    vector< int > indices;
    
    // for( auto& p : endPoint->neighbors ) でもいいが、index を使いたいので普通のfor文
    for( int i = 0; i < 4; ++i )
    {
      // 隣接点が利用可能かどうか
      bool bAvailable = true;
      
      // 点に値が入っていなかったら
      if( !endPoint->neighbors[ i ] )
      {
        continue;// とばして次の点へ
      }
      // 値が入っていたら
      else
      {
        // _lastLine に値が入っているときだけ
        if( _lastLine )
        {
          // 前回の軌跡とかぶっているかチェック
          int nVerts = _lastLine->getVertices().size();
          for( int j =  0; j < nVerts; ++j )
          {
            // かぶってたら
            if( static_cast< ofPoint >( *endPoint->neighbors[ i ] ) == _lastLine->getVertices().at( ( nVerts - 1 ) - j ) )
            {
              bAvailable = false;// 利用不可に
              break;// ループを抜ける
            }
            
            // 指定した点数以上は考慮しない
            if( j == Route::numExcludePointsOfLastLine ) break;
          }
        }
        
        // _otherRoutes に値が入っているときだけ
        if( _otherRoutes )
        {
          // 他の軌跡の終点とかぶっているかチェック
          for( auto& r : *_otherRoutes )
          {
            // closed だったらとばして次へ
//            if( r.isClosed() ) continue;
            
            // かぶってたら
            if( endPoint->neighbors[ i ] == r.getEndPoint() )
            {
              bAvailable = false;// 利用不可に
              break;// ループを抜ける
            }
          }
        }
        
        // 自分の軌跡とかぶっているかチェック
        for( auto& v : line.getVertices() )
        {
          // static_cast< ofPoint >( *endPoint->neighbors[ i ] )
          // ↑ shared_ptr< GridPoint > の実体 GridPoint を ofPoint にキャスト
          // かぶってたら
          if( static_cast< ofPoint >( *endPoint->neighbors[ i ] ) == v )
          {
            bAvailable = false;// 利用不可に
            break;// ループを抜ける
          }
        }
      }
      
      // 利用可のときは隣接点の index を追加
      if( bAvailable ) indices.push_back( i );
    }
    
    // indices の総数が 0 より大きいとき
    if( indices.size() > 0 )
    {
      // ↑次に進む neighbors の index をきめる
      // indices の要素数が 1 のときは 0番目 それ以外のときはランダムにひとつ選ぶ
      int idx  = ( indices.size() == 1 ) ? 0 : static_cast< int >( ofRandom( indices.size() ) );
      
      // endPoint を次の点に更新
      endPoint = endPoint->neighbors[ indices.at( idx ) ];
      
      // line に頂点を追加
      line.addVertex( static_cast< ofPoint >( *endPoint ) );
    }
    // それ以外は行き止まりなので while を抜ける
    else
    {
      bEndRouting = true;
    }
    
    // 線数( 頂点数 - 1 )が maxNumLines に達したら while を抜ける
    if( line.getVertices().size() - 1 == maxNumLines ) bEndRouting = true;
  }
  
  // line を 1px ごとに分割した頂点配列を取得
  routePoints = line.getResampledBySpacing( 1 ).getVertices();
}


// update
//------------------------------------------------------------
void Route::update()
{
  // closing
  if( bClosing )
  {
    // closing with alpha
    if( Route::closingMode == CLOSING_ALPHA )
    {
      alpha -= 5;
      if( alpha < 5 )
      {
        bClosed = true;
      }
    }
    // closing with trace
    else if( Route::closingMode == CLOSING_TRACE )
    {
      if( drawingIndex > drawingSpeed )
      {
        drawingIndex -= drawingSpeed;
      }
      else
      {
        drawingIndex = routePoints.size() - 1;
        bClosed      = true;
      }
    }
  }
  else
  {
    // opening
    if( !bOpened )
    {
      if( routePoints.size() > 0 && drawingIndex < ( routePoints.size() - 1 ) - drawingSpeed )
      {
        drawingIndex += drawingSpeed;
      }
      else
      {
        drawingIndex = routePoints.size() - 1;
        bOpened      = true;
        openedTime   = ofGetElapsedTimef();
      }
    }
    // opened
    else
    {
      if( ofGetElapsedTimef() - openedTime >= Route::stoppingDuration )
      {
        close();
      }
    }
  }
}


// draw
//------------------------------------------------------------
void Route::draw()
{
  ofSetLineWidth( Route::lineWidth );
  
  // 線
  if( routePoints.size() > 0 )
  {
    ofSetColor( 255, alpha );
    
    ofPushStyle();
    {
      glBegin( GL_LINE_STRIP );
      
      if( bClosing )
      {
        for( int i = 0; i <= drawingIndex; ++i ) vertex2f( routePoints.at( ( routePoints.size() - 1 ) -  i ) );
      }
      else
      {
        for( int i = 0; i <= drawingIndex; ++i ) vertex2f( routePoints.at( i ) );
      }
      
      glEnd();
    }
    ofPopStyle();
  }
  
  // 終点の十字
  if( bOpened )
  {
    ofSetColor( color );
    
    ofPoint p = static_cast< ofPoint >( *endPoint );
    
    ofDrawLine( p - ofPoint( 10,  0 ), p + ofPoint( 10,  0 ) );
    ofDrawLine( p - ofPoint(  0, 10 ), p + ofPoint(  0, 10 ) );
  }
}
