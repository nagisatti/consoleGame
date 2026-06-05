/*======================================================================================//
*  ・ステージ管理処理
*
//======================================================================================*/

//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "main.h"
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

//****************************************************************************
//　グローバル変数
//****************************************************************************
int g_currentStage = 1;

void InitializeStageManager()
{
	g_currentStage = 1;
}


int GetCurrentStage()
{
	return g_currentStage;
}

void NextStage()
{
	g_currentStage++;

	UpdateMapCount();
	InitializeBuffer();
	InitializeTitleBuffer();
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

int* GetStageManager()
{
	return &g_currentStage;
}