/*======================================================================================//
*  ・消える床の処理用のヘッダー
*
//======================================================================================*/

//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "fieldDis.h"
#include "camera.h"
#include "titleBuffer.h"
#include "main.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
FIELDDIS g_fieldDis[FIELD_DIS_MAX];
CAMERA* g_fieldDisCamera = GetCamera();
bool g_DrawDisFlg;

 // ゲームタイトルの初期化
void InitializeFieldDis(int stage)
{
	memset(g_fieldDis, 0, sizeof(FIELDDIS) * FIELD_DIS_MAX);
	g_DrawDisFlg = true;

	vec2 pos;
	size scl;

	switch (stage)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;

	case 4:
		pos = { 38.0f, 13.0f };	// 座標情報
		scl = { 6.0f, 1.0f };   // サイズ情報
		CreateDisField(pos, scl, 240, 60);	// 障害物生成

		//pos = { 60.0f, 20.0f };	// 座標情報
		//scl = { 6.0f, 1.0f };   // サイズ情報
		//CreateDisField(pos, scl);	// 障害物生成
		break;

	case 5:
		pos = { 19.0f, 16.0f };	// 座標情報
		scl = { 5.0f, 1.0f };   // サイズ情報
		CreateDisField(pos, scl, 240, 60);	// 障害物生成

		//pos = { 60.0f, 20.0f };	// 座標情報
		//scl = { 6.0f, 1.0f };   // サイズ情報
		//CreateDisField(pos, scl);	// 障害物生成
		break;

	}

}

// ゲームタイトルの終了処理
void FinalizeFieldDis()
{

}

// ゲームタイトルの更新
void UpdateFieldDis()
{
	for (int cnt = 0; cnt < FIELD_DIS_MAX; cnt++)
	{
		if (!g_fieldDis[cnt].bUse)
		{
			continue;
		}

		g_fieldDis[cnt].timer--;

		if (g_fieldDis[cnt].timer <= 0)
		{
			g_fieldDis[cnt].isActive = !g_fieldDis[cnt].isActive;

			if (g_fieldDis[cnt].isActive)
			{
				g_fieldDis[cnt].timer = g_fieldDis[cnt].activeTime;
			}
			else
			{
				g_fieldDis[cnt].timer = g_fieldDis[cnt].inactiveTime;

				// ★消えるタイミングで空白を書いて画面から消す
				float screenX = g_fieldDis[cnt].pos.x - g_fieldDisCamera->cameraPos.x;
				float screenY = g_fieldDis[cnt].pos.y - g_fieldDisCamera->cameraPos.y;
				for (int cntY = 0; cntY < g_fieldDis[cnt].scl.height; cntY++)
				{
					for (int cntX = 0; cntX < g_fieldDis[cnt].scl.width; cntX++)
					{
						WriteBuffer((int)screenX + cntX, (int)(screenY + cntY), ' ', GREEN);
					}
				}
			}
		}
	}
}

// ゲームタイトルの描画
void DrawFieldDis()
{
	for (int cnt = 0; cnt < FIELD_DIS_MAX; cnt++)
	{
		if (!g_fieldDis[cnt].bUse|| !g_fieldDis[cnt].isActive)
		{// 障害物が描画状態でないならば表示しない
			continue;
		}
		// 障害物の矩形描画
		RenderDisField(g_fieldDis[cnt].pos, g_fieldDis[cnt].scl);
	}
}

void CreateDisField(vec2 pos, size scl,int activeTime, int inactiveTime)
{
	for (int cnt = 0; cnt < FIELD_DIS_MAX; cnt++)
	{
		if (!g_fieldDis[cnt].bUse)
		{
			g_fieldDis[cnt].bUse = true;

			g_fieldDis[cnt].pos.x = pos.x;
			g_fieldDis[cnt].pos.y = pos.y;
			g_fieldDis[cnt].scl.width = scl.width;
			g_fieldDis[cnt].scl.height = scl.height; 
			g_fieldDis[cnt].isActive = true;   // 最初は出現状態
			g_fieldDis[cnt].activeTime = activeTime;
			g_fieldDis[cnt].inactiveTime = inactiveTime;
			g_fieldDis[cnt].timer = activeTime; // activeTimeからカウント
			//			g_field[cnt].width = width;
			//			g_field[cnt].height = height;
			break;
		}
	}
}

void RenderDisField(vec2 pos, size scl)
{
	float screenX = pos.x - g_fieldDisCamera->cameraPos.x;
	float screenY = pos.y - g_fieldDisCamera->cameraPos.y;

	float oldPosX = pos.x;
	float oldPosY = pos.y;

	float screenOldX = oldPosX - g_fieldDisCamera->cameraOldPos.x;
	float screenOldY = oldPosY - g_fieldDisCamera->cameraOldPos.y;

	for (int cntY = 0; cntY < scl.height; cntY++)
	{
		//gotoxy((int)(pos.x), (int)(pos.y + cntY));
		for (int cntX = 0; cntX < scl.width; cntX++)
		{
			if (screenX != screenOldX || screenY != screenOldY)
			{
				WriteBuffer((int)screenOldX + cntX, (int)(screenOldY + cntY), ' ', GREEN);
				WriteBuffer((int)screenX + cntX, (int)(screenY + cntY), '-', RED);
			}
			else
			{
				WriteBuffer((int)screenX + cntX, (int)(screenY + cntY), '-', RED);
			}
		}
	}
}

// 障害物の消去
void RemoveDisField(int num)
{
	// アイテムの使用フラグをOFFにする
	g_fieldDis[num].bUse = false;
}
// 障害物構造体 ゲッター
FIELDDIS* GetDisField()
{
	return g_fieldDis;
}

// 障害物の再描画
void ReDrawDisFeild()
{
	g_DrawDisFlg = true;
}