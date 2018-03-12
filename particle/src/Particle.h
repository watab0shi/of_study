// インクルードガード 複数ファイルでインクルードしていてもコンパイル時に2回目以降の展開を防ぐ
#pragma once

#include "ofMain.h"


// Particle
//--------------------------------------------------------------------------------
class Particle
{
public:
  // デフォルトコンストラクタ
  Particle();
  
  // ユーザー定義コンストラクタ
  Particle( ofPoint _pos, ofPoint _vel, float _radius, ofColor _color, float _life );
  
  void update();
  void draw();
  
  // ヘッダのクラス定義内でメンバ関数の実装まで書くと自動的にinline関数になる
  // inline -> コンパイル時に呼び出し箇所に展開される（関数呼び出しコストが低くなる）
  // setter
  void setPosition( ofPoint _pos ){ pos    = _pos; }
  void setVelocity( ofPoint _vel ){ vel    = _vel; }
  void setRadius( float _radius ){  radius = _radius; }
  void setColor( ofColor _color ){  color  = _color; }
  void setLifeSpan( float _life ){  life   = _life; }
  
  // getter
  ofPoint getPosition(){ return pos; }
  ofPoint getVelocity(){ return vel; }
  float   getRadius(){   return radius; }
  ofColor getColor(){    return color; }
  bool    isDead(){      return bDead; }
  
private:
  ofPoint pos;
  ofPoint vel;
  float   radius;
  ofColor color;
  float   life;
  bool    bDead;
};


