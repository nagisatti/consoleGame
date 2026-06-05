#pragma once
#include "define.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVE_GROUND_MAX	(40)	//障害物の最大数
//*************************************
// 障害物 構造体
//*************************************
struct MOVE_GROUND
{
	vec2 pos;			// 座標情報
	vec2 posOld;		// 座標履歴
	size scl;		    // サイズ
	vec2 speed;         // 床の動くスピード
	//float width;		// 幅
	//float height;		// 高さ
	bool bUse;			// 有効かどうか
	int count;          // 移動量
};
//*************************************
// プロトタイプ宣言
//*************************************
void InitializeMoveGround(int);	     	// 障害物の初期化
void FinalizeMoveGround();			    // 障害物の終了処理
void UpdateMoveGround();				// 障害物の更新
void DrawMoveGround();					// 障害物の描画

void CreateMoveGround(vec2, vec2, size);// 障害物の作成
void RenderMoveGround(vec2, size);      // 障害物の矩形描画
void EraseMoveGround(vec2, size);       // 障害物の消去(移動のための)

void RemoveMoveGround(int);			    // 障害物の消去
MOVE_GROUND* GetMoveGround();			// 障害物 構造体 ゲッター