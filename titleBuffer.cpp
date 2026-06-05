/*======================================================================================//
*  ・ゲーム画面以外のバッファ表示用の処理
*
//======================================================================================*/

//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "titleBuffer.h"
#include "main.h"

//****************************************************************************
//　グローバル変数
//****************************************************************************
TITLEBUF g_tSetBuff[SCREEN_BOTTOM + 1][SCREEN_RIGHT + 1];
TITLEBUF g_tBuffDraw[SCREEN_BOTTOM + 1][SCREEN_RIGHT + 1];

// ゲームタイトルバッファの初期化
void InitializeTitleBuffer()
{
	for (int cntY = 0; cntY < SCREEN_BOTTOM + 1; cntY++) {
		for (int cntX = 0; cntX < SCREEN_RIGHT + 1; cntX++) {
			g_tSetBuff[cntY][cntX].moji = ' ';                 // 空白で埋める
			g_tSetBuff[cntY][cntX].color = { 255, 255, 255 };  // 標準の色(白)
			g_tSetBuff[cntY][cntX].backColor = { 0,   0,   0 };
			//g_tSetBuff[cntY][SCREEN_RIGHT - 1].moji = '\n'; // 改行
			g_tBuffDraw[cntY][cntX].moji = ' ';   // g_buffDrawは初回のみ
			g_tBuffDraw[cntY][cntX].color = { 255, 255, 255 };
			g_tBuffDraw[cntY][cntX].backColor = { 0,   0,   0 };
			//g_tBuffDraw[cntY][SCREEN_RIGHT - 1].moji = '\n'; // 改行
		}
	}
}

// ゲームタイトルバッファの終了処理
void FinalizeTitleBuffer()
{

}

// ゲームタイトルバッファの更新
void UpdateTitleBuffer()
{

}

// ゲームタイトルバッファの書き込み
void WriteTitleBuffer(int x, int y, const char str, RGB color, RGB backColor)
{
	// 指定座標が範囲外だったら返す
	if (x < 0 || x >= SCREEN_RIGHT + 1 || y < 0 || y >= SCREEN_BOTTOM + 1)
	{
		return;
	}

	int index = (y * SCREEN_RIGHT + 1) + x;
	g_tSetBuff[y][x].moji = str;
	g_tSetBuff[y][x].color = { color.r, color.g, color.b };
	g_tSetBuff[y][x].backColor = { backColor.r, backColor.g, backColor.b };
}

// バッファの表示
void DrawTitleBuffer()
{
	/*static char buff[SCREEN_BOTTOM * SCREEN_RIGHT * 50] = {};
	char tmp[64] = {};
	buff[0] = '\0';*/
	///gotoxy(1, 1);

	for (int cntY = 0; cntY < SCREEN_BOTTOM + 1; cntY++)
	{
		for (int cntX = 0; cntX < SCREEN_RIGHT + 1; cntX++)
		{
			if (g_tSetBuff[cntY][cntX].moji != g_tBuffDraw[cntY][cntX].moji ||
				g_tSetBuff[cntY][cntX].color.r != g_tBuffDraw[cntY][cntX].color.r ||
				g_tSetBuff[cntY][cntX].color.g != g_tBuffDraw[cntY][cntX].color.g ||
				g_tSetBuff[cntY][cntX].color.b != g_tBuffDraw[cntY][cntX].color.b ||
				g_tSetBuff[cntY][cntX].backColor.r != g_tBuffDraw[cntY][cntX].backColor.r ||
				g_tSetBuff[cntY][cntX].backColor.g != g_tBuffDraw[cntY][cntX].backColor.g ||
				g_tSetBuff[cntY][cntX].backColor.b != g_tBuffDraw[cntY][cntX].backColor.b)
			{ // 差分があれば表示
				g_tBuffDraw[cntY][cntX] = g_tSetBuff[cntY][cntX];

				/*sprintf(tmp, "\x1b[%d;%dH\x1b[38;2;%d;%d;%d;48;2;%d;%d;%dm%c\x1b[0m",
					cntY + SCREEN_TOP, cntX + SCREEN_LEFT,
					g_tBuffDraw[cntY][cntX].color.r, g_tBuffDraw[cntY][cntX].color.g, g_tBuffDraw[cntY][cntX].color.b,
					g_tBuffDraw[cntY][cntX].backColor.r, g_tBuffDraw[cntY][cntX].backColor.g, g_tBuffDraw[cntY][cntX].backColor.b,
					g_tBuffDraw[cntY][cntX].moji);

				strcat(buff, tmp);*/

				gotoxy(cntX, cntY);
				g_tBuffDraw[cntY][cntX] = g_tSetBuff[cntY][cntX];
				printf("\x1b[38;2;%d;%d;%d;48;2;%d;%d;%dm%c\x1b[0m",
					g_tBuffDraw[cntY][cntX].color.r, g_tBuffDraw[cntY][cntX].color.g, g_tBuffDraw[cntY][cntX].color.b,
					g_tBuffDraw[cntY][cntX].backColor.r, g_tBuffDraw[cntY][cntX].backColor.g, g_tBuffDraw[cntY][cntX].backColor.b,
					g_tBuffDraw[cntY][cntX].moji);
			}
		}
	}
	
	//printf("%s", buff);
}

bool IsDiff(int x, int y)
{
	if (g_tSetBuff[y][x].moji != g_tBuffDraw[y][x].moji ||
		g_tSetBuff[y][x].color.r != g_tBuffDraw[y][x].color.r ||
		g_tSetBuff[y][x].color.g != g_tBuffDraw[y][x].color.g ||
		g_tSetBuff[y][x].color.b != g_tBuffDraw[y][x].color.b ||
		g_tSetBuff[y][x].backColor.r != g_tBuffDraw[y][x].backColor.r ||
		g_tSetBuff[y][x].backColor.g != g_tBuffDraw[y][x].backColor.g ||
		g_tSetBuff[y][x].backColor.b != g_tBuffDraw[y][x].backColor.b)
	{

		return true;
	}


	return false;
}

void ClearTitleBuffer()
{
	for (int cntY = 0; cntY < SCREEN_BOTTOM + 1; cntY++) {
		for (int cntX = 0; cntX < SCREEN_RIGHT + 1; cntX++) {
			g_tBuffDraw[cntY][cntX].moji = '\0';
			g_tBuffDraw[cntY][cntX].color.r = -1;
			g_tBuffDraw[cntY][cntX].color.g = -1;
			g_tBuffDraw[cntY][cntX].color.b = -1;
			g_tBuffDraw[cntY][cntX].backColor.r = -1;
			g_tBuffDraw[cntY][cntX].backColor.g = -1;
			g_tBuffDraw[cntY][cntX].backColor.b = -1;
		}
	}
}