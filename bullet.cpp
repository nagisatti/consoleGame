/*======================================================================================//
*  ・弾処理
*
//======================================================================================*/
//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "main.h"
#include "bullet.h"
// 敵が死んだ場合シーン移動する等で使用するため一応宣言
#include "scene.h"
#include "explosion.h"
#include "camera.h"

#define BULLET_MAX     20  //弾の最大生成数

//****************************************************************************
//　グローバル変数
//****************************************************************************
BULLET g_bullet[BULLET_MAX];     // 弾情報
CAMERA* g_cameraBullet = GetCamera();

// 弾の初期化
void InitializeBullet()
{
	memset(g_bullet, 0, sizeof(BULLET) * BULLET_MAX);

}

// 弾の終了処理
void FinalizeBullet()
{

}

// 弾の更新
void UpdateBullet()
{
	for (int cnt = 0; cnt < BULLET_MAX; cnt++)

	{
		if (g_bullet[cnt].use)

		{
			//前フレームの位置を保存

			g_bullet[cnt].posOld.x = g_bullet[cnt].pos.x;

			g_bullet[cnt].posOld.y = g_bullet[cnt].pos.y;

			//移動処理

			g_bullet[cnt].pos.x += g_bullet[cnt].speed.x;

			g_bullet[cnt].pos.y += g_bullet[cnt].speed.y;

			//画面外判定（場外）

			const bool outOfField = (g_bullet[cnt].pos.x < SCREEN_LEFT) || (g_bullet[cnt].pos.x > SCREEN_RIGHT)

				|| (g_bullet[cnt].pos.y > SCREEN_BOTTOM) || (g_bullet[cnt].pos.y < SCREEN_TOP);

			//画面外（場外）だったら、残像を消し、弾を使用可能状態に戻す

			if (outOfField == true)
			{

				gotoxy(g_bullet[cnt].posOld.x, g_bullet[cnt].posOld.y);

				std::cout << " ";

				g_bullet[cnt].use = false;

				CreateExplosion(g_bullet[cnt].posOld, 0);

			}
		}
	}

	//             ogi
	
	//for (int cnt = 0; cnt < BULLET_MAX; cnt++)
	//{
	//	 //debug
	//	std::cout << "::" << g_bullet[cnt].pos.x << "::" << g_bullet[cnt].pos.y;
	//	//弾の座標履歴保存する
	//	g_bullet[cnt].posOld.x = g_bullet[cnt].pos.x;
	//	g_bullet[cnt].posOld.y = g_bullet[cnt].pos.y;

	//	 //弾の座標位置を確定させる
	//	g_bullet[cnt].pos.x += g_bullet[cnt].speed.x;
	//	g_bullet[cnt].pos.y += g_bullet[cnt].speed.y;

	//	 //弾が画面外にある場合
	//	 //x座標、y座標まとめて判定している。見づらかったら分けてもいい
	//	 //RIGHTのバレットx座標のところを +1　してもいい、理由は、player.cpp参照
	//	if (round(g_bullet[cnt].pos.x) > SCREEN_RIGHT  || 
	//		round(g_bullet[cnt].pos.x) < SCREEN_LEFT   || 
	//	    round(g_bullet[cnt].pos.y) > SCREEN_BOTTOM || 
	//		round(g_bullet[cnt].pos.y) < SCREEN_TOP)
	//	{ // 弾の消失
	//		g_bullet[cnt].use = false;
	//		std::cout << "  ";
	//	}
	//}
	

}

// 弾の描画
void DrawBullet()
{
	float screenX;
	float screenY;
	float screenOldX;
	float screenOldY;
	for (int cnt = 0; cnt < BULLET_MAX; cnt++)
	{
		if (g_bullet[cnt].use == true)
		{
			screenX = g_bullet[cnt].pos.x = g_cameraBullet->cameraPos.x;
			screenY = g_bullet[cnt].pos.y = g_cameraBullet->cameraPos.y;

			screenOldX = g_bullet[cnt].posOld.x = g_cameraBullet->cameraOldPos.x;
			screenOldY = g_bullet[cnt].posOld.y = g_cameraBullet->cameraOldPos.y;

			//描画
			// gotoxy(g_bullet[cnt].pos.x, g_bullet[cnt].pos.y);
			WriteBuffer(screenX, screenY, '*', WHITE);
			// std::cout << "*";

			//動いていたら消す
			//後から消すことによって、無駄な処理を減らすことができる。また、画面上なのでintに直す
			if ((static_cast<int>(g_bullet[cnt].pos.x) != static_cast<int>(g_bullet[cnt].posOld.x)) ||
				(static_cast<int>(g_bullet[cnt].pos.y) != static_cast<int>(g_bullet[cnt].posOld.y)))
			{
				//gotoxy(g_bullet[cnt].posOld.x, g_bullet[cnt].posOld.y);
				//std::cout << " ";

				WriteBuffer(screenOldX, screenOldY, ' ', WHITE);
			}
		}
	}


	//            ogi
	
	//for (int cnt = 0; cnt < BULLET_MAX; cnt++)
	//{
	//	// 座標位置が変更している場合
	//	if ((round(g_bullet[0].posOld.x) != round(g_bullet[0].pos.x)) ||
	//		(round(g_bullet[0].posOld.y) != round(g_bullet[0].pos.y)))
	//	{
	//		// ひとつ前の座標を取得
	//		gotoxy(round(g_bullet[0].posOld.x), round(g_bullet[0].posOld.y));
	//		// 表示を消す
	//		std::cout << "  ";
	//	}

	//	if (g_bullet[cnt].use)
	//	{
	//		std::cout << "aaa";
	//		// 座標指定
	//		gotoxy(round(g_bullet[0].pos.x), round(g_bullet[0].pos.y));
	//		// 表示
	//		std::cout << "～";

	//	}
	//}
	
}

// 弾の作成
void CreateBullet(vec2 pos, float angle, float speedX, float speedY)
{
	// std::cout << "呼び出されました";
	for (int cnt = 0; cnt < BULLET_MAX; cnt++)
	{
		if (!g_bullet[cnt].use)
		{
			//std::cout << "ばか";
			g_bullet[cnt].pos.x = pos.x + 1.0;
			g_bullet[cnt].pos.y = pos.y;
			g_bullet[cnt].posOld.x = pos.x;
			g_bullet[cnt].posOld.y = pos.y;
			g_bullet[cnt].speed.x = speedX;
			g_bullet[cnt].speed.y = speedY;
			g_bullet[cnt].use = true;
			break;		//１個設定したら終わり
		}
	}



	// ogi
	//for (int cnt = 0; cnt < BULLET_MAX; cnt++)
	//{
	//	if (!g_bullet[cnt].use)
	//	{
	//		g_bullet[cnt].use = true;

	//		// 座標の更新
	//		g_bullet[cnt].pos.x = pos.x;
	//		g_bullet[cnt].pos.y = pos.y;
	//		g_bullet[cnt].angle = angle;

	//		// 移動量の決定
	//		if (g_bullet[cnt].angle >= 0 && g_bullet[cnt].angle <= 179)
	//		{ // 右方向へ弾が飛ぶ
	//			g_bullet[cnt].speed.x = -1.0f;
	//			g_bullet[cnt].speed.y = 0.0f;
	//		}
	//		if (g_bullet[cnt].angle >= 180 && g_bullet[cnt].angle <= 359)
	//		{ // 左方向へ弾が飛ぶ
	//			g_bullet[cnt].speed.x = 1.0f;
	//			g_bullet[cnt].speed.y = 0.0f;
	//		}

	//		// 有効の弾があるのでfot文を終了する
	//		break;

	//	}

	//}
	
}

// 弾の構造体の取得
BULLET* GetBullet(void)
{
	return g_bullet;
}

//****************************************************************************
//　消去処理
//****************************************************************************
void RemoveBullet(int num)
{
	g_bullet[num].use = false;
}
