#pragma once
#include "define.h"

#define LIFE_MAX				3		// ライフの最大値

// 構造体宣言
struct LIFE
{// ライフ情報
	vec2 pos;			// 座標情報
	vec2 posOld;	// 座標履歴
	int point;		// 得点
	int pointOld;	// 得点履歴
};

// プロトタイプ宣言
void InitializeLife();		// ライフの初期化
void FinalizeLife();			// ライフの終了処理
void UpdateLife();				// ライフの更新
void DrawLife();					// ライフの描画

LIFE* GetLife();					// ライフの構造体 ゲッター
void SetLife(LIFE*);			// ライフの構造体 セッター

void UpLife();						// ライフ上昇
void DownLife();					// ライフ下降

bool CheckZeroLife();			// ライフの確認