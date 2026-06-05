#include "main.h"
#include "moveGround.h"
#include "camera.h"
//*****************************************************************************
// グローバル変数
//*****************************************************************************
MOVE_GROUND g_moveGround[MOVE_GROUND_MAX];			// 障害物情報
CAMERA* g_moveGrundCamera = GetCamera();

// 障害物の初期化
void InitializeMoveGround(int stage)
{
	memset(g_moveGround, 0, sizeof(MOVE_GROUND) * MOVE_GROUND_MAX);

	vec2 pos;
	vec2 speed;
	size scl;

	switch (stage)
	{
	case 1:
		pos = { 10.0f, 8.0f };	// 座標情報
		speed = { 40.0f,9.0f };   // 移動量情報
		scl = { 8.0f, 1.0f };		// サイズ情報
		CreateMoveGround(pos, speed, scl);				// 障害物生成
		break;
	case 2:
		break;
	case 3:
		break;

	}




	//vec2 pos = { 10.0f, 19.0f };
	//CreateField(pos, 8.0f, 4.0f);
	//pos = { 22.0f, 18.0f };
	//CreateField(pos, 16.0f, 4.0f);
	//pos = { 48.0f, 17.0f };
	//CreateField(pos, 10.0f, 7.0f);
	//pos = { 36.0f, 14.0f };
	//CreateField(pos, 8.0f, 6.0f);
	//pos = { 18.0f, 10.0f };
	//CreateField(pos, 10.0f, 4.0f);
	//pos = { 64.0f, 19.0f };
	//CreateField(pos, 6.0f, 4.0f);
	//pos = { 43.0f, 8.0f };
	//CreateField(pos, 30.0f, 3.0f);

}
// 障害物の終了処理
void FinalizeMoveGround()
{

}

// 障害物の更新
void UpdateMoveGround()
{
	for (int cnt = 0; cnt < MOVE_GROUND_MAX; cnt++)
	{
		// 座標情報の保存
		g_moveGround[cnt].pos.x = g_moveGround[cnt].pos.x;
		g_moveGround[cnt].pos.y = g_moveGround[cnt].pos.y;
		// 座標情報の変更
		g_moveGround[cnt].pos.x += g_moveGround[cnt].speed.x;
		g_moveGround[cnt].pos.y += g_moveGround[cnt].speed.y;
		// 移動フレームの制御
		g_moveGround[cnt].count++;
		if (g_moveGround[cnt].count > 80)
		{
			g_moveGround[cnt].speed.x *= -1.0f;   // 反転
			g_moveGround[cnt].speed.y *= -1.0f;   // 反転
			g_moveGround[cnt].count = 0;          // リセット
				
		}
	}
}

// 障害物の描画
void DrawMoveGround()
{
	for (int cnt = 0; cnt < MOVE_GROUND_MAX; cnt++)
	{
		if (g_moveGround[cnt].bUse == false)
		{// 障害物が描画状態でないならば表示しない
			continue;
		}

		if ((g_moveGround[cnt].pos.x != g_moveGround[cnt].pos.x) ||
			(g_moveGround[cnt].posOld.y != g_moveGround[cnt].pos.y))
		{
			EraseMoveGround(g_moveGround[cnt].posOld, g_moveGround[cnt].scl);
		}
		// 障害物の矩形描画
//		RenderMoveGround(g_moveGround[cnt].pos, g_moveGround[cnt].width, g_moveGround[cnt].height);
		RenderMoveGround(g_moveGround[cnt].pos, g_moveGround[cnt].scl);
	}

}

// 障害物の作成
//void CreateField(vec2 pos, float width, float height)
void CreateMoveGround(vec2 pos, vec2 speed, size scl)
{
	for (int cnt = 0; cnt < MOVE_GROUND_MAX; cnt++)
	{
		if (g_moveGround[cnt].bUse == false)
		{
			g_moveGround[cnt].bUse = true;
			g_moveGround[cnt].speed.x = speed.x;
			g_moveGround[cnt].speed.y = speed.y;
			g_moveGround[cnt].pos.x = pos.x;
			g_moveGround[cnt].pos.y = pos.y;
			g_moveGround[cnt].scl.width = scl.width;
			g_moveGround[cnt].scl.height = scl.height;
			//			g_moveGround[cnt].width = width;
			//			g_moveGround[cnt].height = height;
			break;
		}
	}
}
// 障害物の矩形描画
//void RenderField(vec2 pos, float width, float height)
void RenderMoveGround(vec2 pos, size scl)
{
	for (int cntY = 0; cntY < scl.height; cntY++)
	{
		//gotoxy((int)(pos.x), (int)(pos.y + cntY));
		for (int cntX = 0; cntX < (scl.width / 2); cntX++)
		{
			WriteBuffer((int)(pos.x) , (int)(pos.y + cntY), '-', WHITE);
			//std::cout << "■";
		}
	}

	//float screenX = pos.x - g_moveGrundCamera->cameraPos.x;
	//float screenY = pos.y - g_moveGrundCamera->cameraPos.y;

	//float oldPosX = pos.x;
	//float oldPosY = pos.y;

	//float screenOldX = oldPosX - g_moveGrundCamera->cameraOldPos.x;
	//float screenOldY = oldPosY - g_moveGrundCamera->cameraOldPos.y;

	//for (int cntY = 0; cntY < scl.height; cntY++)
	//{
	//	//gotoxy((int)(pos.x), (int)(pos.y + cntY));
	//	for (int cntX = 0; cntX < scl.width; cntX++)
	//	{
	//		if (screenX != screenOldX || screenY != screenOldY)
	//		{
	//			/*WriteTitleBuffer((int)screenOldX + cntX, (int)(screenOldY + cntY), ' ', { 0,0,0 }, { 0,0,0 });
	//			WriteTitleBuffer((int)screenX + cntX, (int)(screenY + cntY), ' ', { 0,0,0 }, { 255,255,255 });*/

	//			WriteBuffer((int)screenOldX + cntX, (int)(screenOldY + cntY), ' ', GREEN);
	//			//WriteBuffer((int)(pos.x), (int)(pos.y + cntY), '■', WHITE);
	//			WriteBuffer((int)screenX + cntX, (int)(screenY + cntY), '-', WHITE);
	//		}
	//		else
	//		{
	//			//WriteTitleBuffer((int)screenX + cntX, (int)(screenY + cntY), ' ', { 0,0,0 }, { 255,255,255 });

	//			WriteBuffer((int)screenX + cntX, (int)(screenY + cntY), '-', WHITE);
	//		}

	//		//std::cout << "■";
	//	}
	//}
}

void EraseMoveGround(vec2 pos, size scl)
{
	//float screenX = pos.x - g_moveGrundCamera->cameraPos.x;
	//float screenY = pos.y - g_moveGrundCamera->cameraPos.y;

	//float oldPosX = pos.x;
	//float oldPosY = pos.y;

	//float screenOldX = oldPosX - g_moveGrundCamera->cameraOldPos.x;
	//float screenOldY = oldPosY - g_moveGrundCamera->cameraOldPos.y;

	//for (int cntY = 0; cntY < scl.height; cntY++)
	//{
	//	//gotoxy((int)(pos.x), (int)(pos.y + cntY));
	//	for (int cntX = 0; cntX < scl.width; cntX++)
	//	{
	//		if (screenX != screenOldX || screenY != screenOldY)
	//		{
	//			/*WriteTitleBuffer((int)screenOldX + cntX, (int)(screenOldY + cntY), ' ', { 0,0,0 }, { 0,0,0 });
	//			WriteTitleBuffer((int)screenX + cntX, (int)(screenY + cntY), ' ', { 0,0,0 }, { 255,255,255 });*/

	//			WriteBuffer((int)screenOldX + cntX, (int)(screenOldY + cntY), ' ', GREEN);
	//			//WriteBuffer((int)(pos.x), (int)(pos.y + cntY), '■', WHITE);
	//			WriteBuffer((int)screenX + cntX, (int)(screenY + cntY), '-', WHITE);
	//		}
	//		else
	//		{
	//			//WriteTitleBuffer((int)screenX + cntX, (int)(screenY + cntY), ' ', { 0,0,0 }, { 255,255,255 });

	//			WriteBuffer((int)screenX + cntX, (int)(screenY + cntY), '-', WHITE);
	//		}

	//		//std::cout << "■";
	//	}
	//}

	for (int cntY = 0; cntY < scl.height; cntY++)
	{
		//gotoxy((int)(pos.x), (int)(pos.y + cntY));
		for (int cntX = 0; cntX < (scl.width / 2); cntX++)
		{
			//std::cout << "  ";
			WriteBuffer((int)(pos.x), (int)(pos.y + cntY), ' ', GREEN);
		}
	}

}
// 障害物の消去
void RemoveMoveGround(int num)
{
	// アイテムの使用フラグをOFFにする
	g_moveGround[num].bUse = false;
}
// 障害物構造体 ゲッター
MOVE_GROUND* GetMoveGround()
{
	return &g_moveGround[0];
}