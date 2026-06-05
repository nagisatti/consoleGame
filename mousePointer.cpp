/*======================================================================================//
*  ・マウス入力等の情報取得は別のファイルで行っているため、その他の処理を行う
*
*
//======================================================================================*/

//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "main.h" 
#include "player.h"
#include "mousePointer.h"
#include "inputkey.h"
#include "wireObject.h"
#include "camera.h"
#include "title.h"
#include "wireGen.h"
#include "result.h"
#include "help.h"

//****************************************************************************
//　グローバル変数
//****************************************************************************
MOUSE g_mouse;
WIREOBJECT* wireObj = GetWireObjectPos();
PLAYER* playerArray = GetPlayerPos();
CAMERA* g_cameraMouse = GetCamera();

bool MousePointer(int index)
{
	float screenX = wireObj[index].pos.x - g_cameraMouse->cameraPos.x;
	float screenY = wireObj[index].pos.y - g_cameraMouse->cameraPos.y;

	// マウスカーソルの座標取得
	int px = inport(PM_CURX);
	int py = inport(PM_CURY);

	if (abs((int)screenX - px) <= WIRE_HIT_RANGE &&
		abs((int)screenY - py) <= WIRE_HIT_RANGE)
	{
		return true;
	}

	/*if ((int)screenX == px && (int)screenY == py)
	{
		return true;
	}*/

	return false;
}

bool StartPointer()
{
	// マウスカーソルの座標取得
	int px = inport(PM_CURX);
	int py = inport(PM_CURY);

	if (START_Y == py && START_RIGHT >= px && START_LEFT <= px)
	{
		return true;
	}

	return false;
}

bool SavePointer()
{
	// マウスカーソルの座標取得
	int px = inport(PM_CURX);
	int py = inport(PM_CURY);

	if (SAVE_Y == py && SAVE_RIGHT >= px && SAVE_LEFT <= px)
	{
		return true;
	}

	return false;
}

bool ExitPointer()
{
	// マウスカーソルの座標取得
	int px = inport(PM_CURX);
	int py = inport(PM_CURY);

	if (EXIT_Y == py && EXIT_RIGHT >= px && EXIT_LEFT <= px)
	{
		return true;
	}

	return false;
}

bool ResultExit()
{
	// マウスカーソルの座標取得
	int px = inport(PM_CURX);
	int py = inport(PM_CURY);

	if (EXIT_RESULT_Y == py && EXIT_RESULT_RIGHT >= px && EXIT_RESULT_LEFT <= px)
	{
		return true;
	}

	return false;
}

bool TitlePointer()
{
	// マウスカーソルの座標取得
	int px = inport(PM_CURX);
	int py = inport(PM_CURY);

	if (TITLE_Y == py && TITLE_RIGHT >= px && TITLE_LEFT <= px)
	{
		return true;
	}

	return false;
}

bool PlayPointer()
{
	// マウスカーソルの座標取得
	int px = inport(PM_CURX);
	int py = inport(PM_CURY);

	if (PLAY_Y == py && PLAY_RIGHT >= px && TITLE_LEFT <= px)
	{
		return true;
	}

	return false;
}

bool BackPointer()
{
	// マウスカーソルの座標取得
	int px = inport(PM_CURX);
	int py = inport(PM_CURY);

	if (BACK_Y == py && BACK_RIGHT >= px && BACK_LEFT <= px)
	{
		return true;
	}

	return false;
}

// ワイヤーの初期化
void InitializePointer()
{

}

// ワイヤーの終了処理
void FinalizePointer()
{

}

// ワイヤーの更新
void UpdatePointer()
{

}

// ワイヤーの描画
void DrowPointer()
{
	//gotoxy(playerArray->pos.x, playerArray->pos.y);

}
