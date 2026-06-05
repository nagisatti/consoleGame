/*======================================================================================//
*  ・プレイヤーの体力処理
*
//======================================================================================*/

//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "main.h"
#include "life.h"
#include "camera.h"
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LIFE g_life;			// ライフ情報
CAMERA* g_cameraLife = GetCamera();   // カメラの座標情報

// ライフの初期化
void InitializeLife()
{
	memset(&g_life, 0, sizeof(LIFE));		      // 構造体の初期化
	g_life.pos.x = 8.0f;					      // X座標
	g_life.pos.y = 1.0f;						  // Y座標
	g_life.point = LIFE_MAX;					  // ライフの設定
	g_life.pointOld = 0;						  // ライフの過去の状態
}
// ライフの終了処理
void FinalizeLife()
{
}
// ライフの更新
void UpdateLife()
{
//	g_life.pointOld = g_life.point;
}
// ライフの描画
void DrawLife()
{
	float screenX = g_life.pos.x - g_cameraLife->cameraPos.x;
	float screenY = g_life.pos.y - g_cameraLife->cameraPos.y;
	
	// 過去のライフと変更があった場合
	if (g_life.point != g_life.pointOld)
	{
		/*
		gotoxy(g_life.pos.x, g_life.pos.y);
		std::cout << "ライフ：";
		*/
		//WriteBuffer(g_life.pos.x, g_life.pos.y, 'ラ',WHITE);
		//WriteBuffer(g_life.pos.x + 1, g_life.pos.y, 'イ',WHITE);
		//WriteBuffer(g_life.pos.x + 2, g_life.pos.y, 'フ',WHITE);
		//WriteBuffer(g_life.pos.x + 3, g_life.pos.y, ' ',WHITE);
		//WriteBuffer(g_life.pos.x + 4, g_life.pos.y, ':',WHITE);
		//WriteBuffer(g_life.pos.x + 5, g_life.pos.y, ' ',WHITE);

		textcolor(RED);
		
		for (int cnt = 0; cnt < g_life.point; cnt++)
		{
			WriteBuffer(screenX + cnt, screenY, '$',RED);
			// std::cout << "◆";
		}
		for (int cnt = g_life.point; cnt < LIFE_MAX; cnt++)
		{
			WriteBuffer(screenX + cnt, screenY, ' ', WHITE);
			//std::cout << "  ";
		}
		textcolor(WHITE);
		// ライフポイントの履歴更新
		g_life.pointOld = g_life.point;
	}
}
// ライフの構造体 ゲッター
LIFE* GetLife() 
{
	return &g_life;
}
// ライフの構造体 セッター
void SetLife(LIFE* life)
{
	memcpy(&g_life, life, sizeof(LIFE));
}
// ライフの上昇
void UpLife()
{
	g_life.point++;
}
// ライフの下降
void DownLife()
{
	g_life.point--;
}

// ライフの確認
// true : ライフが０   false : ライフがある
bool CheckZeroLife()
{
	bool result = false;
	if (g_life.point <= 0)
	{
		result = true;
	}
	return result;
}