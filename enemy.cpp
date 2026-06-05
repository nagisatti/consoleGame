/*======================================================================================//
*  ・敵の処理
* 初期化、生成、移動制御、描画、最大描画範囲制御　を行っている
*
//======================================================================================*/
//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "main.h"
#include "enemy.h"
#include "collision.h"
#include "life.h"
// 敵が死んだ場合シーン移動する等で使用するため一応宣言
#include "scene.h"


//****************************************************************************
//　グローバル変数
//****************************************************************************
ENEMY g_enemy[ENEMY_MAX];   // エネミー情報

// 敵の初期化
void InitializeEnemy()
{
	// 一括初期化
	memset(g_enemy, 0, sizeof(ENEMY) * ENEMY_MAX);
	// 座標情報
	g_enemy[0].pos.x   = 20.0f;
	g_enemy[0].pos.y   = 10.0f;
	// 移動量
	g_enemy[0].speed.x = 0.1f;
	g_enemy[0].speed.y = 0.04f;
	// 敵が存在する
	g_enemy[0].use = true;
	
}

// 敵の終了処理
void FinalizeEnemy()
{

}

// 敵の更新
void UpdateEnemy()
{
	for (int cnt = 0; cnt < ENEMY_MAX; cnt++)
	{
		if (g_enemy[cnt].use == false)
		{// 配列の敵の情報が有効でない
			continue;
		}

		// 現在の座標位置を保存する
		g_enemy[cnt].posOld.x = g_enemy[cnt].pos.x;
		g_enemy[cnt].posOld.y = g_enemy[cnt].pos.y;
		// 制御処理
		if (round(g_enemy[cnt].pos.y + g_enemy[cnt].speed.y) < SCREEN_TOP + 1)
		{// 画面上部との衝突確認
			g_enemy[cnt].speed.y *= -1;
		}
		if (round(g_enemy[cnt].pos.y + g_enemy[cnt].speed.y) > SCREEN_BOTTOM - 1)
		{// 画面下部との衝突確認
			g_enemy[0].speed.y *= -1;
		}
		if (round(g_enemy[cnt].pos.x + g_enemy[cnt].speed.x) < SCREEN_LEFT + 2)
		{// 画面左部との衝突確認
			g_enemy[cnt].speed.x *= -1;
		}
		if (round(g_enemy[cnt].pos.x + g_enemy[cnt].speed.x + 1) > SCREEN_RIGHT - 2)
		{// 画面右部との衝突確認
			g_enemy[cnt].speed.x *= -1;
		}

		// 壁の横判定
		ENEMY copy_enemy;
		memcpy(&copy_enemy, &g_enemy[cnt], sizeof(ENEMY));
		copy_enemy.pos.x += g_enemy[cnt].speed.x;
		if (EnemyCollisionWall(&copy_enemy))
		{
			g_enemy[cnt].speed.x *= -1;
		}
		// 壁の縦の判定
		memcpy(&copy_enemy, &g_enemy[cnt], sizeof(ENEMY));
		copy_enemy.pos.y += g_enemy[cnt].speed.y;
		if (EnemyCollisionWall(&copy_enemy))
		{
			g_enemy[cnt].speed.y *= -1;
		}
		g_enemy[cnt].pos.x += g_enemy[cnt].speed.x;
		g_enemy[cnt].pos.y += g_enemy[cnt].speed.y;
		//---------------------------------------------------------
		// 当たり判定
		//---------------------------------------------------------
		// 敵キャラクターとの当たり判定
		if (EnemyCollisionBullet(&g_enemy[cnt]))
		{
			g_enemy[cnt].use = false;
		}
	}
	// 敵の生存チェック
	if (CheckZeroEnemy())
	{
		SetScene(SCENE_RESULT); // 画面タイトル
	}
}

// 敵の描画
void DrawEnemy()
{
	// 座標位置が変更している場合
	if (((int)(g_enemy[0].posOld.x) != (int)(g_enemy[0].pos.x)) ||
		((int)(g_enemy[0].posOld.y) != (int)(g_enemy[0].pos.y)))
	{
		// ひとつ前の座標を取得
		gotoxy((int)(g_enemy[0].posOld.x), (int)(g_enemy[0].posOld.y));
		// 表示を消す
		std::cout << "  ";
	}

	// 座標指定
	gotoxy((int)(g_enemy[0].pos.x), (int)(g_enemy[0].pos.y));
	// 表示
	textcolor(RED);
	std::cout << "▼";
	// デバッグモードだと、FPS表示のとこで白に戻してくれてるから赤にならない。
	// ただ、リリーズモードだとそれがないため下記の文を入れる必要がある
	// textcolor(WHITE);
}

// 敵の構造体
ENEMY* GetENEMY()
{ // 敵の構造体配列の戦闘ポインターを返す
	return g_enemy;
}

// 敵の生存チェック
// true : 敵がいない false : 敵がいる
bool CheckZeroEnemy()
{
	bool result = true;
	for (int cnt = 0; cnt < ENEMY_MAX; cnt++)
	{
		if (g_enemy[cnt].use)
		{
			result = false;
			break;
		}
	}
	return result;
}