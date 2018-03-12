#pragma once

#include "ofMain.h"

class EventQueue
{
public:
  // キューで実行される関数に渡すための構造体
  // キューの経過時間と次のキューへいくためのbool
  struct Args
  {
    float time;
    bool  next;
  };
  
  // typedef std::function< void ( Args& ) > Event; と同義
  // C++11からは型エイリアス using を使う
  // 関数オブジェクト std::function< 戻り値の型 ( 引数 ) >
  using Event = std::function< void ( Args& ) >;
  
  // キュー追加
  void add( const Event& _fn )
  {
    queue.emplace_back( make_shared< Event >( _fn ) );
  }
  
  // 指定秒待つ
  void wait( float _t )
  {
    add( [ _t ]( Args& _arg ) {
      if( _arg.time >= _t ) _arg.next = true;
    } );
  }
  
  // 一度だけ実行
  void once( const function< void() >& _fn )
  {
    add( [ _fn ]( Args& _arg ){
      _fn();
      _arg.next = true;
    } );
  }
  
  // 指定秒間呼び続ける
  void repeat( float _t, const function< void() >& _fn )
  {
    add( [ _t, _fn ]( Args& _arg ){
      _fn();
      if( _arg.time >= _t ) _arg.next = true;
    } );
  }
  
  // 指定秒間呼び続ける 関数内部で args.time を使いたいとき
  void repeat( float _t, const Event& _fn )
  {
    add( [ _t, _fn ]( Args& _arg ){
      _fn( _arg );
      if( _arg.time >= _t ) _arg.next = true;
    } );
  }
  
  // 現在のキューの関数を実行して終わったら次へ
  void update()
  {
    if( queue.empty() ) return;
    
    // キュー開始時の処理
    if( initQueue )
    {
      initQueue = false;
      startTime = ofGetElapsedTimef();
      time      = 0;
    }
    
    // キュー開始からの経過時間
    time = ofGetElapsedTimef() - startTime;
    
    Args args{ time, false };
    queue.front()->operator()( args );// 参照渡しで関数内で args を書き換え
    
    // arg.next が true になったら次のキューへ
    if( args.next )
    {
      queue.pop_front();
      initQueue = true;
    }
  }
  
  // リセット
  void reset()
  {
    queue.clear();
    initQueue = true;
  }
  
  // キュー数を返す
  size_t size()
  {
    return queue.size();
  }
  
  // 現在実行中のキューの経過時間
  double getTime()
  {
    return time;
  }
  
private:
  // でっく front と back に対して push() pop() ができる 両端キュー
  // スマートポインタ shared_ptr<T> -> ofPtr<T> とおなじ
  // deque< shared_ptr< std::function< void ( Args& ) > > >
  deque< shared_ptr< Event > > queue;
  bool                         initQueue = true;
  float                        startTime = 0.;
  float                        time      = 0.;
};