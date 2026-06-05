#pragma once
#include "define.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FIELD_MAX	(40)	//障害物の最大数
//*************************************
// 障害物 構造体
//*************************************
struct FIELD
{
	vec2 pos;			// 座標情報
	vec2 posOld;		// 座標履歴
	size scl;			// サイズ
	//float width;		// 幅
	//float height;		// 高さ
	bool bUse;			// 有効かどうか
};
//*************************************
// プロトタイプ宣言
//*************************************
void InitializeField(int);		// 障害物の初期化
void FinalizeField();			// 障害物の終了処理
void UpdateField();				// 障害物の更新
void DrawField();					// 障害物の描画

void CreateField(vec2, size);// 障害物の作成
void RenderField(vec2, size);// 障害物の矩形描画

void RemoveField(int);			// 障害物の消去
FIELD* GetField();				// 障害物 構造体 ゲッター

void ReDrawFeild();             // 再描画