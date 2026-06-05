/*======================================================================================//
*  ・当たり判定の処理のヘッダー
*
//======================================================================================*/
#pragma once

//****************************************************************************
//　インクルードファイル
//****************************************************************************
// この三つはこっちにないといけない
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "wireObject.h"

//****************************************************************************
//　マクロ
//****************************************************************************
// 
// キャラクターの矩形のサイズ
// キャラクターごとにサイズが異なるのが普通だが
// その場合は初期化で構造体に格納しておく

#define CHARACTER_COLLISION_SIZEX (1.0f)
#define CHARACTER_COLLISION_SIZEY (0.5f)

#define WIREOBJ_X (1.0f)    // ワイヤーオブジェクトのx軸の判定
#define WIREOBJ_Y (0.5f)    // ワイヤーオブジェクトのy軸の判定

// プレイヤーキャラクターと敵キャラクターの当たり判定
// プレイヤーから呼び出す関数
bool PlayerCollisionEnemy(PLAYER* player);

// 敵キャラクターとプレイヤー弾の当たり判定
// 敵から呼び出す関数
bool EnemyCollisionBullet(ENEMY* enemy);

// プレイヤーキャラクターと障害物の当たり判定
// プレイヤーから呼び出す関数
bool PlayerCollisionWall(PLAYER* player);
bool EnemyCollisionWall(ENEMY* enemy);
bool BulletCollisionWall(BULLET* bullet);

// ワイヤーオブジェクトの当たり判定
bool CollisionWireObject(WIREOBJECT* obj);

// プレイヤーキャラクターとアイテムの当たり判定
// プレイヤーから呼び出す関数
bool PlayerCollisionItem(PLAYER* player);

// 動く床の判定
bool PlayerCollisionMoveWall(PLAYER* player);

// 消える床の判定
bool PlayerCollisionDisWall(PLAYER* player);

// ゴールの当たり判定
bool GoalCollision(PLAYER* player);
