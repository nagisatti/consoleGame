#include "main.h"
#include "field.h"
#include "camera.h"
#include "titleBuffer.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
FIELD g_field[FIELD_MAX];			 // 障害物情報
CAMERA* g_fieldCamera = GetCamera(); // カメラ情報
bool g_DrawFlg = true;               // 描画更新

// 障害物の初期化
void InitializeField(int stage)
{
	memset(g_field, 0, sizeof(FIELD) * FIELD_MAX);
	vec2 pos;
	size scl;

	switch (stage)
	{
	case 1:
		pos = { 10.0f, 20.0f };	// 座標情報
		scl = { 8.0f, 1.0f };   // サイズ情報
		CreateField(pos, scl);	// 障害物生成

		pos = { 40.0f, 20.0f };
		scl = { 8.0f, 1.0f };
		CreateField(pos, scl);

		pos = { 58.0f, 20.0f };
		scl = { 8.0f, 1.0f };
		CreateField(pos, scl);
		break;
	case 2:
		pos = { 10.0f, 20.0f };	// 座標情報
		scl = { 8.0f, 1.0f };   // サイズ情報
		CreateField(pos, scl);	// 障害物生成

		pos = { 47.0f, 16.0f };	// 座標情報
		scl = { 8.0f, 1.0f };   // サイズ情報
		CreateField(pos, scl);	// 障害物生成

		pos = { 57.0f, 20.0f };	// 座標情報
		scl = { 8.0f, 1.0f };   // サイズ情報
		CreateField(pos, scl);	// 障害物生成

		/*pos = { 30.0f, 20.0f };
		scl = { 8.0f, 1.0f };
		CreateField(pos, scl);*/
		break;
	case 3:
		pos = { 10.0f, 20.0f };	// 座標情報
		scl = { 6.0f, 1.0f };   // サイズ情報
		CreateField(pos, scl);	// 障害物生成

		pos = { 60.0f, 20.0f };	// 座標情報
		scl = { 6.0f, 1.0f };   // サイズ情報
		CreateField(pos, scl);	// 障害物生成
		break;

	case 4:
		pos = { 10.0f, 20.0f };	// 座標情報
		scl = { 6.0f, 1.0f };   // サイズ情報
		CreateField(pos, scl);	// 障害物生成

		pos = { 20.0f, 16.0f };	// 座標情報
		scl = { 4.0f, 1.0f };   // サイズ情報
		CreateField(pos, scl);	// 障害物生成

		pos = { 52.0f, 20.0f };	// 座標情報
		scl = { 6.0f, 1.0f };   // サイズ情報
		CreateField(pos, scl);	// 障害物生成

		pos = { 68.0f, 16.0f };	// 座標情報
		scl = { 6.0f, 1.0f };   // サイズ情報
		CreateField(pos, scl);	// 障害物生成
		break;

	case 5:
		pos = { 10.0f, 20.0f };	// 座標情報
		scl = { 6.0f, 1.0f };   // サイズ情報
		CreateField(pos, scl);	// 障害物生成

		pos = { 60.0f, 20.0f };	// 座標情報
		scl = { 6.0f, 1.0f };   // サイズ情報
		CreateField(pos, scl);	// 障害物生成
		break;

	}
	

	/*pos = { 22.0f, 18.0f };
	scl = { 16.0f, 4.0f };
	CreateField(pos, scl);
	pos = { 48.0f, 17.0f };
	scl = { 10.0f, 7.0f };
	CreateField(pos, scl);
	pos = { 36.0f, 14.0f };
	scl = { 8.0f, 6.0f };
	CreateField(pos, scl);
	pos = { 18.0f, 10.0f };
	scl = { 10.0f, 4.0f };
	CreateField(pos, scl);
	pos = { 64.0f, 19.0f };
	scl = { 6.0f, 4.0f };
	CreateField(pos, scl);
	pos = { 43.0f, 8.0f };
	scl = { 30.0f, 3.0f };
	CreateField(pos, scl);*/

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
void FinalizeField()
{

}

// 障害物の更新
void UpdateField()
{
//	for (int cnt = 0; cnt < WIREGEN_MAX; cnt++)
//	{
//		if (g_wireObj[cnt].bUse == false)
//		{// 障害物が描画状態でないならば表示しない
//			continue;
//		}
//		// 障害物の矩形描画
////		RenderField(g_wireObj[cnt].pos, g_wireObj[cnt].width, g_wireObj[cnt].height);
//		RenderWireObject(g_wireObj[cnt].pos, g_wireObj[cnt].scl);
//	}
}

// 障害物の描画
void DrawField()
{
	// 2回目の描画をしない
	//if (!g_DrawFlg)
	//{
	//	return;
	//}

	for (int cnt = 0; cnt < FIELD_MAX; cnt++)
	{
		if (g_field[cnt].bUse == false)
		{// 障害物が描画状態でないならば表示しない
			continue;
		}
		// 障害物の矩形描画
//		RenderField(g_field[cnt].pos, g_field[cnt].width, g_field[cnt].height);
		RenderField(g_field[cnt].pos, g_field[cnt].scl);
	}

	// 1度描画する
	//g_DrawFlg = false;
}

// 障害物の作成
//void CreateField(vec2 pos, float width, float height)
void CreateField(vec2 pos, size scl)
{
	for (int cnt = 0; cnt < FIELD_MAX; cnt++)
	{
		if (g_field[cnt].bUse == false)
		{
			g_field[cnt].bUse = true;

			g_field[cnt].pos.x = pos.x;
			g_field[cnt].pos.y = pos.y;
			g_field[cnt].scl.width = scl.width;
			g_field[cnt].scl.height = scl.height;
//			g_field[cnt].width = width;
//			g_field[cnt].height = height;
			break;
		}
	}
}
// 障害物の矩形描画
//void RenderField(vec2 pos, float width, float height)
void RenderField(vec2 pos, size scl)
{
	// 描画処理用変数
	float screenX = pos.x - g_fieldCamera->cameraPos.x;
	float screenY = pos.y - g_fieldCamera->cameraPos.y;

	float oldPosX = pos.x;
	float oldPosY = pos.y;

	float screenOldX = oldPosX - g_fieldCamera->cameraOldPos.x;
	float screenOldY = oldPosY - g_fieldCamera->cameraOldPos.y;
	
	for (int cntY = 0; cntY < scl.height; cntY++)
	{
		//gotoxy((int)(pos.x), (int)(pos.y + cntY));
		for (int cntX = 0; cntX < scl.width; cntX++)
		{
			if (screenX != screenOldX || screenY != screenOldY)
			{
				/*WriteTitleBuffer((int)screenOldX + cntX, (int)(screenOldY + cntY), ' ', { 0,0,0 }, { 0,0,0 });
				WriteTitleBuffer((int)screenX + cntX, (int)(screenY + cntY), ' ', { 0,0,0 }, { 255,255,255 });*/

				WriteBuffer((int)screenOldX + cntX, (int)(screenOldY + cntY), ' ', GREEN);
				//WriteBuffer((int)(pos.x), (int)(pos.y + cntY), '■', WHITE);
				WriteBuffer((int)screenX + cntX, (int)(screenY + cntY), '-', WHITE);
			}
			else
			{
				//WriteTitleBuffer((int)screenX + cntX, (int)(screenY + cntY), ' ', { 0,0,0 }, { 255,255,255 });

				WriteBuffer((int)screenX + cntX, (int)(screenY + cntY), '-', WHITE);
			}
			
			//std::cout << "■";
		}
	}
}
// 障害物の消去
void RemoveField(int num)
{
	// アイテムの使用フラグをOFFにする
	g_field[num].bUse = false;
}
// 障害物構造体 ゲッター
FIELD* GetField()
{
	return &g_field[0];
}

// 障害物の再描画
void ReDrawFeild()
{
	g_DrawFlg = true;

	for (int cnt = 0; cnt < FIELD_MAX; cnt++)
	{
		if (!g_field[cnt].bUse)
		{
			continue;
		}

		RenderField(g_field[cnt].pos, g_field[cnt].scl);
	}
}