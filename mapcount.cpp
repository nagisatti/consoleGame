/*======================================================================================//
*  ・マップカウント描画の為のヘッダー
*
*
//======================================================================================*/

//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "mapcount.h"
#include "camera.h"
#include "stageManager.h"
#include "main.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int g_mapCnt = 1;

// マップカウントの初期化
void InitializeMapCount()
{

}

// マップカウントの終了処理
void FinalizeMapCount()
{

}

// マップカウントの更新
void UpdateMapCount()
{
	g_mapCnt = *GetStageManager();
}

// マップカウントの描画
void DrawMapCount()
{
	WriteBuffer(2, 2, 'S', WHITE);
	WriteBuffer(3, 2, 'T', WHITE);
	WriteBuffer(4, 2, 'A', WHITE);
	WriteBuffer(5, 2, 'G', WHITE);
	WriteBuffer(6, 2, 'E', WHITE);
	switch (g_mapCnt)
	{
	case 1:
		WriteBuffer(7, 2, '1', WHITE);
		break;
	case 2:
		WriteBuffer(7, 2, '2', WHITE);
		break;
	case 3:
		WriteBuffer(7, 2, '3', WHITE);
		break;
	case 4:
		WriteBuffer(7, 2, '4', WHITE);
		break;
	case 5:
		WriteBuffer(7, 2, '5', WHITE);
		break;
	}
	
}
