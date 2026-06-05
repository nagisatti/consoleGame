//=============================================================================
// [game.cpp] ゲームシーン管理
// 
// 制作者：土居秀顕/花山大貴	制作日：2026/01/08
//=============================================================================
#include "main.h"

#define CONIOEX
#include "conioex.h"
#include "mousePointer.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "field.h"
#include "moveGround.h"
#include "life.h"
#include "inputkey.h"
#include "explosion.h"
#include "item.h"
#include "wireObject.h"
#include "pause.h"
#include "camera.h"
#include "goal.h"
#include "sound.h"
#include "titleBuffer.h"
#include "stageManager.h"
#include "moveField.h"
#include "fieldDis.h"
#include "mapcount.h"

// =============================================================================
// ゲームシーン初期化
// =============================================================================
void InitializeGame(void)
{
	InitializeBuffer();
	InitializeSound();
	InitializePlayer();
	InitializeCamera();
	InitializeField(GetCurrentStage());
	InitializeMoveField(GetCurrentStage());
	InitializWireObject(GetCurrentStage());
	InitializGoalObject(GetCurrentStage());
	InitializeFieldDis(GetCurrentStage());
	InitializeKey();
	InitializePause();
	PlayBGM(1);
}

// =============================================================================
// ゲームシーン更新
// =============================================================================
void UpdateGame(void)
{
	// ポーズ押された時にポーズ状態に入る
	// それ以外はゲームシーンはいる
	if (GetPause())
	{
		UpdatePause();
	}
	else
	{

		// 移動量が少ない処理を上の方にあると良い
		UpdateField();
		UpdateSound();
		UpdateWireObject();
		UpdateGoalObject();
		UpdateMoveField();
		UpdateFieldDis();
		UpdateKey();
		UpdatePlayer();		
		UpdateCamera();
		if (inport(PK_0))
		{ // ポーズ画面へ遷移する
			SetPause(true);
		}
	}
	
}

// =============================================================================
// ゲームシーン描画
// =============================================================================
void DrawGame(void)
{
	if (GetPause())
	{ // ポーズ状態
		DrawPause();
		DrawTitleBuffer();
	}
	else
	{
		// 一番下が一番上に表示される	
		DrawMapCount();
		DrawField();
		DrawMoveField();
		DrawGoalObject();
		DrawFieldDis();
		DrawKey();
		DrawPlayer();
		// ここでまとめて表示
		DrawBuffer();
	}
}

// =============================================================================
// ゲームシーン終了処理
// =============================================================================
void FinalizeGame(void)
{
	FinalizePlayer();
	FinalizeSound();
	FinalizeField();
	FinalizeMoveGround();
	FinalizeWireObject();
	FinalizeGoalObject();
	FinalizeFieldDis();
	FinalizeKey();
	FinalizePause();
}