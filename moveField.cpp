/*======================================================================================//
*  ・動く床を生成するための処理
*
//======================================================================================*/

//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "main.h"
#include "field.h"
#include "camera.h"
#include "titleBuffer.h"
#include "moveField.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
MOVEFIELD g_moveField[FIELD_MOVE_MAX];			 // 障害物情報
CAMERA* g_moveFieldCamera = GetCamera(); // カメラ情報
bool g_moveDrawFlg = true;               // 描画更新

// 障害物の初期化
void InitializeMoveField(int stage)
{
	memset(g_moveField, 0, sizeof(FIELD) * FIELD_MOVE_MAX);
	vec2 pos;
	size scl;

	switch (stage)
	{
	case 1:
		/*pos = { 40.0f, 15.0f };
		scl = { 8.0f, 1.0f };
		CreateMoveField(pos, scl, { 1.0f, 0.0f }, 0.2f, 10.0f);*/


		break;
	case 2:
		pos = { 30.0f, 19.0f };	// 座標情報
		scl = { 8.0f, 1.0f };   // サイズ情報
		CreateMoveField(pos, scl, { 1.0f, 0.0f }, 0.1f, 10.0f);	// 障害物生成

		/*pos = { 30.0f, 20.0f };
		scl = { 8.0f, 1.0f };
		CreateMoveField(pos, scl, { 1.0f, 0.0f }, 0.2f, 10.0f);*/
		break;
	case 3:
		pos = { 20.0f, 17.0f };	// 座標情報
		scl = { 8.0f, 1.0f };   // サイズ情報
		CreateMoveField(pos, scl, { 0.5f, 0.0f }, 0.1f, 8.0f);	// 障害物生成

		pos = { 40.0f, 13.0f };	// 座標情報
		scl = { 8.0f, 1.0f };   // サイズ情報
		CreateMoveField(pos, scl, { 1.0f, 0.0f }, 0.1f, 10.0f);	// 障害物生成
		break;
	case 5:
		pos = { 32.0f, 14.0f };	// 座標情報
		scl = { 6.0f, 1.0f };   // サイズ情報
		CreateMoveField(pos, scl, { 1.0f, 0.0f }, 0.05f, 5.0f);	// 障害物生成

		pos = { 40.0f, 11.0f };	// 座標情報
		scl = { 6.0f, 1.0f };   // サイズ情報
		CreateMoveField(pos, scl, { 1.0f, 0.0f }, 0.1f, 6.0f);	// 障害物生成
		break;


	}

}
// 障害物の終了処理
void FinalizeMoveField()
{

}

// 障害物の更新
void UpdateMoveField()
{
	for (int cnt = 0; cnt < FIELD_MOVE_MAX; cnt++)
	{
		if (!g_moveField[cnt].bUse)
		{
			continue;
		}
		if (!g_moveField[cnt].isMoving)
		{
			continue;
		}


		// 1フレーム前の座標を保存
		g_moveField[cnt].posOld.x = g_moveField[cnt].pos.x;
		g_moveField[cnt].posOld.y = g_moveField[cnt].pos.y;

		// 移動
		g_moveField[cnt].pos.x += g_moveField[cnt].moveDir.x * g_moveField[cnt].moveSpeed;
		g_moveField[cnt].pos.y += g_moveField[cnt].moveDir.y * g_moveField[cnt].moveSpeed;

		// 折り返し判定
		float distX = g_moveField[cnt].pos.x - g_moveField[cnt].startPos.x;
		float distY = g_moveField[cnt].pos.y - g_moveField[cnt].startPos.y;
		float dist = distX * distX + distY * distY;

		if (dist >= g_moveField[cnt].moveRange * g_moveField[cnt].moveRange)
		{
			g_moveField[cnt].moveDir.x *= -1;
			g_moveField[cnt].moveDir.y *= -1;
		}
	}
}

// 障害物の描画
void DrawMoveField()
{
	for (int cnt = 0; cnt < FIELD_MOVE_MAX; cnt++)
	{
		if (!g_moveField[cnt].bUse)
		{
			continue;
		}
		RenderMoveField(g_moveField[cnt].pos, g_moveField[cnt].posOld, g_moveField[cnt].scl);
	}
}

// 障害物の作成
//void CreateField(vec2 pos, float width, float height)
void CreateMoveField(vec2 pos, size scl, vec2 moveDir, float moveSpeed, float moveRange)
{
	for (int cnt = 0; cnt < FIELD_MOVE_MAX; cnt++)
	{
		if (!g_moveField[cnt].bUse)
		{
			g_moveField[cnt].bUse = true;
			g_moveField[cnt].pos = pos;
			g_moveField[cnt].posOld = pos;
			g_moveField[cnt].scl = scl;
			g_moveField[cnt].isMoving = true;
			g_moveField[cnt].moveDir = moveDir;
			g_moveField[cnt].moveSpeed = moveSpeed;
			g_moveField[cnt].moveRange = moveRange;
			g_moveField[cnt].startPos = pos;
			break;
		}
	}
}
// 障害物の矩形描画
//void RenderField(vec2 pos, float width, float height)
void RenderMoveField(vec2 pos, vec2 posOld, size scl)
{
	// 描画処理用変数
	float screenX = pos.x - g_moveFieldCamera->cameraPos.x;
	float screenY = pos.y - g_moveFieldCamera->cameraPos.y;
	float screenOldX = posOld.x - g_moveFieldCamera->cameraPos.x; // cameraOldPos→cameraPos
	float screenOldY = posOld.y - g_moveFieldCamera->cameraPos.y;

	for (int cntY = 0; cntY < (int)scl.height; cntY++)
	{
		for (int cntX = 0; cntX < (int)scl.width; cntX++)
		{
			if ((int)screenX != (int)screenOldX || (int)screenY != (int)screenOldY)
			{
				WriteBuffer((int)screenOldX + cntX, (int)(screenOldY + cntY), ' ', WHITE);
			}
			WriteBuffer((int)screenX + cntX, (int)(screenY + cntY), '-', YELLOW);
		}
	}
}
// 障害物の消去
void RemoveMoveField(int num)
{
	// アイテムの使用フラグをOFFにする
	g_moveField[num].bUse = false;
}
// 障害物構造体 ゲッター
MOVEFIELD* GetMoveField()
{
	return &g_moveField[0];
}

// 障害物の再描画
void ReDrawMoveFeild()
{
	g_moveDrawFlg = true;
}