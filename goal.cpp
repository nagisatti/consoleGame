/*======================================================================================//
*  ・ゴール制御するための処理
*
//======================================================================================*/

//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "goal.h"
#include "main.h"
#include "scene.h"
#include "camera.h"
#include "titleBuffer.h"

//****************************************************************************
//　マクロ
//****************************************************************************

//****************************************************************************
//　グローバル変数
//****************************************************************************
GOALOBJECT g_goalObj[GOAL_MAX];
CAMERA* g_CameraGoal = GetCamera();
bool g_DrawGoalFlg = true;              // 描画更新

// オブジェクト初期化
void InitializGoalObject(int stage)
{
	memset(g_goalObj, 0, sizeof(GOALOBJECT) * GOAL_MAX);

	vec2 pos;
	size scl;

	switch (stage)
	{
	case 1:
		pos = { 64.0f, 19.0f };	         // 座標情報
		scl = { 2.0f, 1.0f };		     // サイズ情報
		CreateGoalObject(pos, scl);		 // 障害物生成
		break;
	case 2:
		pos = { 60.0f, 19.0f };	         // 座標情報
		scl = { 2.0f, 1.0f };		     // サイズ情報
		CreateGoalObject(pos, scl);		 // 障害物生成
		break;
	case 3:
		pos = { 64.0f, 19.0f };	         // 座標情報
		scl = { 2.0f, 1.0f };		     // サイズ情報
		CreateGoalObject(pos, scl);		 // 障害物生成
		break;

	case 4:
		pos = { 72.0f, 15.0f };	         // 座標情報
		scl = { 2.0f, 1.0f };		     // サイズ情報
		CreateGoalObject(pos, scl);		 // 障害物生成
		break;

	case 5:
		pos = { 64.0f, 19.0f };	         // 座標情報
		scl = { 2.0f, 1.0f };		     // サイズ情報
		CreateGoalObject(pos, scl);		 // 障害物生成
		break;
	}

}

// オブジェクト終了処理
void FinalizeGoalObject()
{

}

// オブジェクト更新
void UpdateGoalObject()
{
	// 2回目の描画をしない
	//if (!g_DrawGoalFlg)
	//{
	//	return;
	//}

	for (int cnt = 0; cnt < GOAL_MAX; cnt++)
	{
		if (g_goalObj[cnt].use == false)
		{// ゴールが描画状態でないならば表示しない
			continue;
		}
		// ゴールの矩形描画
//		RenderGoalObject(g_goalObj[cnt].pos, g_goalObj[cnt].width, g_goalObj[cnt].height);
		RenderGoalObject(g_goalObj[cnt].pos, g_goalObj[cnt].scl);
	}

	// 1度描画する
	//g_DrawGoalFlg = false;
}

// オブジェクト描画
void DrawGoalObject()
{
	
}

// オブジェクト生成
void CreateGoalObject(vec2 pos, size scl)
{
	for (int cnt = 0; cnt < GOAL_MAX; cnt++)
	{
		if (g_goalObj[cnt].use == false)
		{
			g_goalObj[cnt].use = true;

			g_goalObj[cnt].pos.x = pos.x;
			g_goalObj[cnt].pos.y = pos.y;
			g_goalObj[cnt].scl.width = scl.width;
			g_goalObj[cnt].scl.height = scl.height;
			//g_field[cnt].width = width;
			//g_field[cnt].height = height;
			break;
		}
	}
}

// オブジェクト矩形描画
void RenderGoalObject(vec2 pos, size scl)
{
	// 描画処理用変数
	float screenX = pos.x - g_CameraGoal->cameraPos.x;
	float screenY = pos.y - g_CameraGoal->cameraPos.y;

	float oldPosX = pos.x;
	float oldPosY = pos.y;

	float screenOldX = oldPosX - g_CameraGoal->cameraOldPos.x;
	float screenOldY = oldPosY - g_CameraGoal->cameraOldPos.y;

	//g_CameraGoal->posCamera.x = screenX;
	//g_CameraGoal->posCamera.y = screenY;

	for (int cntY = 0; cntY < scl.height; cntY++)
	{
		for (int cntX = 0; cntX < (scl.width / 2); cntX++)
		{
			if (screenX != screenOldX || screenY != screenOldY)
			{
				//WriteTitleBuffer((int)screenOldX, (int)(screenOldY + cntY), ' ', { 0,0,0 }, { 0,0,0 });
				//WriteTitleBuffer((int)screenX, (int)(screenY + cntY), 'G', { 0,0,0 }, { 0,0,255 });

				WriteBuffer((int)screenOldX, (int)(screenOldY + cntY), ' ', GREEN);
				WriteBuffer((int)screenX, (int)(screenY + cntY), 'G', BLUE);
			}
			else
			{
				//WriteTitleBuffer((int)screenX, (int)(screenY + cntY), 'G', { 0,0,0 }, { 0,0,255 });

				WriteBuffer((int)screenX, (int)(screenY + cntY), 'G', BLUE);
			}
		}
	}
}

// 障害物の消去
void RemoveGoal(int num)
{
	g_goalObj[num].use = false;
}

// 再描画
void ReDrawGoal()
{
	g_DrawGoalFlg = true;
}


// ゴールオブジェクトの座標をポインタで渡す
GOALOBJECT* GetGoalObjectPos()
{
	return g_goalObj;
}