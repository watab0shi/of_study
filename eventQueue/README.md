# EventQueue
---
ラムダ関数を用いたキューイングのサンプル。  
  
![screenshot_00](screenshot_00.png)  
![screenshot_01](screenshot_01.png)  
![screenshot_02](screenshot_02.png)  
![screenshot_03](screenshot_03.png)  

## Point
---
- 型エイリアスで型の名前を簡略化できる`using To = From;` typedefと同義`typedef From To;`
- `EventQueue::add( const Event& _fn )`でキューを追加していく
- 関数内で`arg.next == true`になったら現在のキューを削除して次のキューにいく
- `EventQueue::add( const Event& _fn )`に渡すラムダ関数に`this`キャプチャを用いることでofAppのメンバ変数をEventQueueクラス内で変更できる