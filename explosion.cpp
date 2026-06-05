#include "main.h"
#include "explosion.h"
#include "camera.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
EXPLOSION g_explosion[EXPLOSION_MAX];	// アイテム構造体配列

//爆発表示パターン（終端文字いれて3文字分）
char		g_explosionPatt[][3] =
{
	"★",
	"※",
	"×",
	"  ",
};

//=============================================================================
// 初期化処理
//=============================================================================
void InitializeExplosion()
{
	memset(&g_explosion[0], 0, sizeof(EXPLOSION) * EXPLOSION_MAX);
}
//=============================================================================
// 終了処理
//=============================================================================
void FinalizeExplosion()
{ 
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplosion()
{
	// 使用中の構造体を全て更新する
	for (int cnt = 0; cnt < EXPLOSION_MAX; cnt++)
	{
		// 構造体が未使用なら別の配列を探す
		if ( ! g_explosion[cnt].use)
		{
			continue;
		}
		// アニメーションカウンター
		g_explosion[cnt].anime += 0.1f;
		// カウンターが終了したとき
		if (g_explosion[cnt].anime >= 4.0f)
		{
			g_explosion[cnt].use = false;
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawExplosion()
{
	// 使用中の構造体を全て描画する
	for (int cnt = 0; cnt < EXPLOSION_MAX; cnt++)
	{
		// 構造体が未使用なら別の配列を探す
		if ( ! g_explosion[cnt].use)
		{
			continue;
		}
		/*
		gotoxy(g_explosion[cnt].pos.x, g_explosion[cnt].pos.y);
		textcolor(YELLOW);	//色替え
		std::cout << g_explosionPatt[(int)round(g_explosion[cnt].anime)];	// アニメ表示
		textcolor(WHITE);	//色替え
		*/

		textcolor(YELLOW);	//色替え
		// WriteBuffer(g_explosion[cnt].pos.x, g_explosion[cnt].pos.y, g_explosionPatt[(int)round(g_explosion[cnt].anime)],YELLOW);
		textcolor(WHITE);	//色替え
	}
}
//=============================================================================
// 生成処理
//=============================================================================
void CreateExplosion(vec2 pos, int type)
{
	// 生成可能な配列を探す
	for (int cnt = 0; cnt < EXPLOSION_MAX; cnt++)  
	{
		// 構造体が使用中なら別の配列を探す
		if (g_explosion[cnt].use)
		{
			continue;
		}
		// アニメーションタイマーリセット
		g_explosion[cnt].anime = 0.0f;
		// 座標関係
		g_explosion[cnt].pos.x = pos.x;
		g_explosion[cnt].pos.y = pos.y;
		// フラグ関係
		g_explosion[cnt].use = true;
		break;					//アイテムを1つ作成したら終了
	}
}