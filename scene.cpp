// =============================================================================
// インクルード
// =============================================================================
#define CONIOEX      // conio.ex.hを二重呼び出しさせない
#include "conioex.h"
#include "scene.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "titleBuffer.h"
#include "help.h"

// =============================================================================
// グローバル変数
// =============================================================================
// 起動時に動作させたいシーンをセットさせておく
SCENE g_Scene = SCENE_TITLE;    // 現在動作中のシーン
SCENE g_SceneNext = SCENE_TITLE; // 移行先のシーン


// シーンの初期化　関数
void InitializeScene(void)
{
	LoadFile();
	switch (g_Scene)
	{
	case SCENE_TITLE:
		InitializeTitle();   // タイトル画面の初期化
		InitializeTitleBuffer(); // タイトルバッファの初期化
		break;
	case SCENE_HELP:
		InitializeHelp();
		InitializeTitleBuffer(); // タイトルバッファの初期化
		break;
	case SCENE_GAME:
		InitializeGame();    // ゲーム本編の初期化
		break;
	case SCENE_RESULT:
		InitializeReslut();  // リザルト画面の初期化
		InitializeTitleBuffer();
		break;
	default:
		break;
	}
}

// シーンの終了　関数
void FinalizeScene(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		FinalizeTitle();      // タイトル画面の終了
		break;
	case SCENE_HELP:
		FinalizeHelp();
		break;
	case SCENE_GAME:
		FinalizeGame();       // ゲーム本編の終了
		break;
	case SCENE_RESULT:
		FinalizeReslut();     // リザルト画面の終了
		break;
	default:
		break;
	}
}

// シーンの更新　関数
void UpdateScene(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		UpdateTitle();      // タイトル画面の更新
		break;
	case SCENE_HELP:
		UpdateHelp();
		break;
	case SCENE_GAME:
		UpdateGame();       // ゲーム本編の更新
		break;
	case SCENE_RESULT:
		UpdateReslut();     // リザルト画面の更新
		break;
	default:
		break;
	}
}

// シーンの描画　関数
void DrawScene(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		DrawTitle();      // タイトル画面の描画
		DrawTitleBuffer();
		break;
	case SCENE_HELP:
		DrawHelp();
		DrawTitleBuffer();
		break;
	case SCENE_GAME:
		DrawGame();       // ゲーム本編の描画
		break;
	case SCENE_RESULT:
		DrawReslut();     // リザルト画面の描画
		DrawTitleBuffer();
		break;
	default:
		break;
	}
}

// 移行先のシーンセット
void SetScene(SCENE next)
{
	g_SceneNext = next;
}

// シーン切り替え
void ChangeScene(void)
{
	// 移行先のシーンがセットされているかを確認する
	if (g_Scene != g_SceneNext)
	{
		FinalizeScene();        // 現在動作中のシーンを終了させる

		g_Scene = g_SceneNext;  // 現在動作中のシーンを移行先シーンで更新する

		InitializeScene();      // 更新したシーンの初期化を行う
		//InitializeTitleBuffer();
		//ClearTitleBuffer();
		clrscr();               // 画面のクリア
	}
}