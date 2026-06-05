/*======================================================================================//
*  ・ワイヤー移動に使用するためのオブジェクトを生成する処理
*
//======================================================================================*/

//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "main.h"
#include "wireObject.h"
#include "calc.h"
#include "inputkey.h"
#include "camera.h"
#include "titleBuffer.h"

//****************************************************************************
//　グローバル変数
//****************************************************************************
WIREOBJECT g_wireObj[WIREGEN_MAX];
CAMERA* g_cameraWireObj = GetCamera();
bool isClick = false;   // 連打防止フラグ

// ワイヤーオブジェクトの座標をポインタで渡す
WIREOBJECT* GetWireObjectPos()
{
	return g_wireObj;
}

// ワイヤーオブジェクトの初期化
void InitializWireObject(int stage)
{
	// オブジェクトの初期化
	memset(g_wireObj, 0, sizeof(WIREOBJECT) * WIREGEN_MAX);

	vec2 pos;
	size scl;
	switch (stage)
	{
	case 1:
		pos = { 40.0f, 10.0f };	// 座標情報
		scl = { 2.0f, 1.0f };		// サイズ情報
		g_wireObj[0].pos = {40.0f, 10.0f};
		CreateWireObject(pos, scl);

		pos = { 60.0f, 10.0f };	// 座標情報
		scl = { 2.0f, 1.0f };		// サイズ情報
		g_wireObj[1].pos = { 60.0f, 10.0f };
		CreateWireObject(pos, scl);
		break;
	case 2:
		pos = { 30.0f, 6.0f };	// 座標情報
		scl = { 2.0f, 1.0f };		// サイズ情報
		g_wireObj[0].pos = { 30.0f, 10.0f };
		CreateWireObject(pos, scl);

		pos = { 50.0f, 6.0f };	// 座標情報
		scl = { 2.0f, 1.0f };		// サイズ情報
		g_wireObj[1].pos = { 60.0f, 10.0f };
		CreateWireObject(pos, scl);
		break;
	case 3:
		pos = { 20.0f, 10.0f };	// 座標情報
		scl = { 2.0f, 1.0f };		// サイズ情報
		g_wireObj[0].pos = { 30.0f, 10.0f };
		CreateWireObject(pos, scl);

		pos = { 40.0f, 6.0f };	// 座標情報
		scl = { 2.0f, 1.0f };		// サイズ情報
		g_wireObj[1].pos = { 60.0f, 10.0f };
		CreateWireObject(pos, scl);

		pos = { 60.0f, 4.0f };	// 座標情報
		scl = { 2.0f, 1.0f };		// サイズ情報
		g_wireObj[2].pos = { 60.0f, 10.0f };
		CreateWireObject(pos, scl);
		break;

	case 4:
		pos = { 25.0f, 6.0f };	// 座標情報
		scl = { 2.0f, 1.0f };		// サイズ情報
		g_wireObj[0].pos = { 30.0f, 10.0f };
		CreateWireObject(pos, scl);

		pos = { 40.0f, 6.0f };	// 座標情報
		scl = { 2.0f, 1.0f };		// サイズ情報
		g_wireObj[1].pos = { 60.0f, 10.0f };
		CreateWireObject(pos, scl);

		pos = { 58.0f, 10.0f };	// 座標情報
		scl = { 2.0f, 1.0f };		// サイズ情報
		g_wireObj[2].pos = { 60.0f, 10.0f };
		CreateWireObject(pos, scl);

		pos = { 70.0f, 10.0f };	// 座標情報
		scl = { 2.0f, 1.0f };		// サイズ情報
		g_wireObj[3].pos = { 60.0f, 10.0f };
		CreateWireObject(pos, scl);
		break;

	case 5:
		pos = { 20.0f, 10.0f };	// 座標情報
		scl = { 2.0f, 1.0f };		// サイズ情報
		g_wireObj[0].pos = { 30.0f, 10.0f };
		CreateWireObject(pos, scl);

		pos = { 40.0f, 6.0f };	// 座標情報
		scl = { 2.0f, 1.0f };		// サイズ情報
		g_wireObj[1].pos = { 60.0f, 10.0f };
		CreateWireObject(pos, scl);

		pos = { 50.0f, 4.0f };	// 座標情報
		scl = { 2.0f, 1.0f };		// サイズ情報
		g_wireObj[2].pos = { 60.0f, 10.0f };
		CreateWireObject(pos, scl);

		pos = { 60.0f, 4.0f };	// 座標情報
		scl = { 2.0f, 1.0f };		// サイズ情報
		g_wireObj[3].pos = { 60.0f, 10.0f };
		CreateWireObject(pos, scl);
		break;

	}

	


}

// ワイヤーの終了処理
void FinalizeWireObject()
{

}

// ワイヤーの更新
void UpdateWireObject()
{
	for (int cnt = 0; cnt < WIREGEN_MAX; cnt++)
	{
		if (g_wireObj[cnt].bUse == false)
		{// 障害物が描画状態でないならば表示しない
			continue;
		}
		// 障害物の矩形描画
//		RenderField(g_wireObj[cnt].pos, g_wireObj[cnt].width, g_wireObj[cnt].height);
		RenderWireObject(g_wireObj[cnt].pos, g_wireObj[cnt].scl);
	}
}

// オブジェクト矩形描画
void RenderWireObject(vec2 pos, size scl)
{
	// 描画処理用変数
	float screenX = pos.x - g_cameraWireObj->cameraPos.x;
	float screenY = pos.y - g_cameraWireObj->cameraPos.y;

	float oldPosX = pos.x;
	float oldPosY = pos.y;

	float screenOldX = oldPosX - g_cameraWireObj->cameraOldPos.x;
	float screenOldY = oldPosY - g_cameraWireObj->cameraOldPos.y;

	g_wireObj->posCamera.x = screenX;
	g_wireObj->posCamera.y = screenY;

	// debug用表示
	/*gotoxy(2, 10);
	std::cout << "wireScr:(" << (int)screenX << "," << (int)screenY << ")";*/
	for (int cntY = 0; cntY < scl.height; cntY++)
	{
		// gotoxy((int)(pos.x), (int)(pos.y + cntY));
		for (int cntX = 0; cntX < (scl.width / 2); cntX++)
		{
			//textcolor(GREEN);   // オブジェクト表示カラーの変更
			// 座標の初期値らへんがおかしくて、一瞬だけ左にずれて描画される
			if (screenX != screenOldX || screenY != screenOldY)
			{
				//WriteTitleBuffer((int)screenOldX, (int)(screenOldY + cntY), ' ', { 0,0,0 }, { 0,0,0 });
				//WriteTitleBuffer((int)screenX, (int)(screenY + cntY), '#', { 0,255,0 }, { 0,0,0 });
				if ((int)screenX != (int)screenOldX || (int)screenY != (int)screenOldY)
				{
					WriteBuffer((int)screenOldX + cntX, (int)(screenOldY + cntY), ' ', GREEN);
				}
				//WriteBuffer((int)screenOldX, (int)(screenOldY + cntY), ' ', GREEN);
				WriteBuffer((int)screenX, (int)(screenY + cntY), '#', GREEN);
			}
			else
			{
				//WriteTitleBuffer((int)screenX, (int)(screenY + cntY), '#', { 0,255,0 }, { 0,0,0 });

				WriteBuffer((int)screenX, (int)(screenY + cntY), '#', GREEN);
			}
			// std::cout << "■";
			//textcolor(WHITE);   // 変更した表示カラーを元に戻す、これは標準設定のにする
		}
	}
}

//****************************************************************************
//　プレイヤーを動かすのはうごかすが、動きを良くするために背景も動かす
//  そのための処理、差分描画目指す
//****************************************************************************
// ワイヤーの描画
void DrawWireObject()
{
	
	/*
	// 座標位置が変更している場合
	if (((int)(g_wireObj[0].posOld.x) != (int)(g_wireObj[0].pos.x)) ||
		((int)(g_wireObj[0].posOld.y) != (int)(g_wireObj[0].pos.y)))
	{
		// ひとつ前の座標を取得
		gotoxy((int)(g_wireObj[0].posOld.x), (int)(g_wireObj[0].posOld.y));
		// 表示を消す
		std::cout << "  ";
	}

	// 座標指定
	gotoxy((int)(g_wireObj[0].pos.x), (int)(g_wireObj[0].pos.y));
	// 表示
	textcolor(GREEN);   // オブジェクト表示カラーの変更
	std::cout << "+";
	textcolor(WHITE);   // 変更した表示カラーを元に戻す、これは標準設定のにする
	*/

}

// オブジェクト生成
void CreateWireObject(vec2 pos,size scl)
{
	for (int cnt = 0; cnt < WIREGEN_MAX; cnt++)
	{
		if (g_wireObj[cnt].bUse == false)
		{
			g_wireObj[cnt].bUse = true;

			g_wireObj[cnt].pos.x = pos.x;
			g_wireObj[cnt].pos.y = pos.y;
			g_wireObj[cnt].scl.width = scl.width;
			g_wireObj[cnt].scl.height = scl.height;
			//			g_wireObj[cnt].width = width;
			//			g_wireObj[cnt].height = height;
			break;
		}
	}
}

