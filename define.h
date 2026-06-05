/*======================================================================================//
*  ・プレイヤー情報等の共通、頻繁に使用するものはすべてここに書くこと
*
*
//======================================================================================*/
#pragma once

// 共通デファイン
#define SCREEN_TOP                 1     // 画面上部の座標
#define SCREEN_BOTTOM              25    // 画面下部の座標 (24 or 25)
#define SCREEN_LEFT                1     // 画面左部の座標
#define SCREEN_RIGHT               80    // 画面右部の座標 (79 or 80)

#define WIRE_MAX_LENGTH (30.0f)

// #define PLAYER_MOVE_SPEED_X        0.2f  // プレイヤーの移動量(x軸)
// #define PLAYER_MOVE_SPEED_Y        0.1f  // プレイヤーの移動量(y軸)

// 共通の構造体
struct size
{ // サイズ情報
	float width;   // 幅
	float height;  // 高さ

};

struct vec2
{ // 座標情報
	float x;  // x座標
	float y;  // y座標
};



//============   必要であれば使う  =================/
struct vec3
{ // 座標情報
	float x;  // x座標
	float y;  // y座標
	float z;  // z座標
};