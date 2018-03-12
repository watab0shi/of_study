#pragma once

#include "ofMain.h"
#include "Particle.h"


// Particles
//--------------------------------------------------------------------------------
class Particles
{
public:
  void update()
  {
    // ふつうのfor文 更新のみ
//    for( int i = 0; i < ps.size(); ++i ) ps.at( i ).update();
    
    // 範囲ベースfor文 ( Range based for loop ) 更新のみ
//    for( auto& p : ps ) p.update();
    
    // イテレータ ( iterator ) 更新 + 削除
//    for( vector< Particle >::iterator it = ps.begin(); it != ps.end(); )
//    {
//      ( *it ).update();
//      
//      if( ( *it ).isDead() ) it = ps.erase( it );
//      else                   ++it;
//    }
    
    // auto型 代入するオブジェクトから型を推論する ラムダ関数を代入するときはautoのほうが速いらしい
    // 関数オブジェクト std::function< 戻り値の型 ( 引数の型 ) > ここでは std::function< bool ( Particle& ) >
    // ラムダ関数 lambda function
    // [ キャプチャ ]( 引数 ) -> 戻り値の型{ 処理; }
    // 戻り値の型はreturnされる型によって決まるため省略可 returnがないとvoidになる
    // ついでにupdateかけちゃうので引数は参照をとる
    auto func = []( Particle& _p ){
      _p.update();
      return _p.isDead();
    };
    
    // remove_if 有効要素を左詰めして、有効要素の終端のイテレータを返す
//    ps.erase( remove_if( ps.begin(), ps.end(), func ), ps.end() );
    
    // 内部で上記と同じ処理をしている
    ofRemove( ps, func );
  }
  
  void draw()
  {
    for( auto& p : ps ) p.draw();
  }
  
  void add( ofPoint _pos )
  {
    // ofRandomf()  -> -1. ~ 1.
    // ofRandomuf() ->  0. ~ 1.
    float   angle  = ofRandomf() * 180;
    float   speed  = ofRandomuf() * 3 + 1;
    
    // A.rotate() -> Aを回して参照を返す, A.getRotated() -> Aのコピーを回したものを返す
    ofPoint vel    = ofPoint( 1, 0 ).rotate( 0, 0, angle );
    float   radius = ofRandom( 10, 30 );
    ofColor color  = ofColor::fromHsb( ofRandomuf() * 255, 120, 255 );
    float   life   = ofGetElapsedTimef() + ofRandomuf() * 1 + 0.5;
    
    // コンテナ内で直接新規オブジェクト生成
    ps.emplace_back( _pos, vel, radius, color, life );
  }
  
  int size()
  {
    return ps.size();
  }
  
  vector< Particle >& get()
  {
    return ps;
  }
  
private:
  vector< Particle > ps;
};
