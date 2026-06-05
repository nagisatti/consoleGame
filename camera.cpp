/*======================================================================================//
*  ・カメラ制御するためのヘッダー
*
//======================================================================================*/

//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "camera.h"
#include "player.h"
#include "main.h"
#include "wireGen.h"
#include "calc.h"

//****************************************************************************
//　グローバル変数
//****************************************************************************
CAMERA g_camera;
PLAYER* g_playerCamera = GetPlayerPos();
CALCOBJECT* g_calcCamera = GetCalcPos();
WIRESTATE* g_cameraWire = GetWireState();

BUF g_setBuff[SCREEN_BOTTOM][SCREEN_RIGHT];
BUF g_buffDraw[SCREEN_BOTTOM][SCREEN_RIGHT];

// ダブルバッファ
char g_screenBuffer[SCREEN_BOTTOM][SCREEN_RIGHT + 1];

// バッファの初期化
void InitializeBuffer()
{
	for (int cntY = 0; cntY < SCREEN_BOTTOM; cntY++) 
	{
		for (int cntX = 0; cntX < SCREEN_RIGHT; cntX++) 
		{
			g_setBuff[cntY][cntX].moji = ' ';              // 空白で埋める
			g_setBuff[cntY][cntX].color = WHITE;           // 標準の色(白)
			g_setBuff[cntY][SCREEN_RIGHT - 1].moji = '\n'; // 改行
			g_buffDraw[cntY][cntX].moji = ' ';   
			g_buffDraw[cntY][cntX].color = WHITE;
			g_buffDraw[cntY][SCREEN_RIGHT - 1].moji = '\n'; // 改行
		}
	}
}

void BuffReset()
{
	for (int cntY = 0; cntY < SCREEN_BOTTOM; cntY++)
	{
		for (int cntX = 0; cntX < SCREEN_RIGHT; cntX++)
		{
			g_buffDraw[cntY][cntX].moji = '\0';
			g_buffDraw[cntY][cntX].color = WHITE;
			g_buffDraw[cntY][SCREEN_RIGHT - 1].moji = '\n'; // 改行
		}
	}
}

void InitializeCamera()
{
	g_camera.cameraPos.x = 20;
	g_camera.cameraPos.y = 0;
}

// 書き込み
void WriteBuffer(int x, int y, const char str, char color)
{
	// 指定座標が範囲外だったら返す
	if (x < 0 || x >= SCREEN_RIGHT || y < 0 || y >= SCREEN_BOTTOM)
	{
		return;
	}

	int index = (y * SCREEN_RIGHT) + x;
	g_setBuff[y][x].moji = str;
	g_setBuff[y][x].color = color;
}

// カメラの更新
void UpdateCamera()
{
	// 左右20近づいたらスクロールするための変数
	int margin = 10;

	// カメラの座標履歴保存
	g_camera.cameraOldPos.x = g_camera.cameraPos.x;
	g_camera.cameraOldPos.y = g_camera.cameraPos.y;

	// プレイヤーが右端に来たらカメラを右へ
	if (g_playerCamera->pos.x > g_camera.cameraPos.x + SCREEN_RIGHT - margin)
	{
		g_camera.cameraPos.x = g_playerCamera->pos.x - (SCREEN_RIGHT - margin);
	}
	// プレイヤーが左端に来たらカメラを左へ
	else if(g_playerCamera->pos.x < g_camera.cameraPos.x + margin)
	{
		g_camera.cameraPos.x = g_playerCamera->pos.x - margin;
	}

	// マップ範囲外に出ないようにする
	if (g_camera.cameraPos.x < 0)
	{
		g_camera.cameraPos.x = 0;
	}

	if (g_camera.cameraPos.x > MAP_WIDTH - SCREEN_RIGHT)
	{
		g_camera.cameraPos.x = MAP_WIDTH - SCREEN_RIGHT;
	}

	if ((int)g_camera.cameraPos.x != (int)g_camera.cameraOldPos.x ||
		(int)g_camera.cameraPos.y != (int)g_camera.cameraOldPos.y)
	{
		ClearWireWithOldCamera();

		/*g_calcCamera->playPos.x = g_playerCamera->pos.x;
		g_calcCamera->playPos.y = g_playerCamera->pos.y;*/

		//if (*g_cameraWire == WIRE_MOVING ||
		//	*g_cameraWire == WIRE_READY ||
		//	*g_cameraWire == WIRE_EXTENDING)
		//{
		//	//CalcPosition();
		//	RedrawWire();
		//}
	}
}

// バッファの表示
void DrawBuffer()
{
	float playerScreenX =g_playerCamera->pos.x - g_camera.cameraPos.x;
	float playerScreenY =g_playerCamera->pos.y - g_camera.cameraPos.y;

	gotoxy(1, 1);
	for (int cntY = 0; cntY < 24; cntY++)
	{
		for (int cntX = 0; cntX < SCREEN_RIGHT; cntX++)
		{
			if (*g_cameraWire == WIRE_IDLE && g_setBuff[cntY][cntX].moji == '*')
			{
				g_setBuff[cntY][cntX].moji = ' ';
			}

			if (g_setBuff[cntY][cntX].moji == 'P')
			{
				if (cntX != (int)playerScreenX || cntY != (int)playerScreenY)
				{
					g_setBuff[cntY][cntX].moji = ' ';
				}
			}

			if (g_setBuff[cntY][cntX].moji != g_buffDraw[cntY][cntX].moji ||
				g_setBuff[cntY][cntX].color != g_buffDraw[cntY][cntX].color
				)
			{ // 差分があれば表示
				gotoxy(cntX , cntY);
				g_buffDraw[cntY][cntX] = g_setBuff[cntY][cntX];
				textcolor(g_buffDraw[cntY][cntX].color);
				 printf("%c", g_buffDraw[cntY][cntX].moji);
				//std::cout << g_buffDraw[cntY][cntX].moji;
			}
		}
	}
}

// カメラ情報をポインタで渡す
CAMERA* GetCamera()
{
	return &g_camera;
}