#pragma once

// 列挙体でシーンの種類を定義する
enum SCENE
{
	SCENE_TITLE,   // タイトル画面
	SCENE_HELP,    // 説明画面
	SCENE_GAME,    // ゲーム画面
	SCENE_RESULT,  // ゲーム結果表示画面

	SCENE_NUM,     // シーン終端
};

void InitializeScene();		// ゲームシーンの初期化
void FinalizeScene();		// ゲームシーンの終了処理
void UpdateScene();		    // ゲームシーンの更新
void DrawScene();		    // ゲームシーンの描画

void SetScene(SCENE next); // 移行先シーンのセット
void ChangeScene(void);     // シーンの切り替え
