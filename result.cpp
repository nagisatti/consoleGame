/*======================================================================================//
*  ・リザルト画面の処理
*
//======================================================================================*/

//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "main.h"
#include "result.h"
#include "scene.h"
#include "conioex.h"
#include "camera.h"
#include <fstream>
#include "titleBuffer.h"
#include "mousePointer.h"

//****************************************************************************
//　グローバル変数
//****************************************************************************
char result/*[MAX_READ_FILE]*/[SCREEN_BOTTOM + 1][SCREEN_RIGHT];      // タイトル画面を格納する変数

std::ifstream inResultFile;
bool isReadResultFile;    // ファイル読み込みされたかどうかのフラグ
bool matchResult[5];      // 触れているかどうかのフラグ

// ゲームリザルトの初期化
void InitializeReslut()
{

	inResultFile.open("C:/HAL東京/C++/進級制作/HEW2026_Project01/excel/title2.csv");

	isReadResultFile = false;
	memset(matchResult, 0, sizeof(bool) * 5);

	if (isReadResultFile)
	{
		return;
	}

	LoadResultFile();
}

// ゲームリザルトの終了処理
void FinalizeReslut()
{
	inResultFile.close();
}

// ゲームリザルトの更新
void UpdateReslut()
{
	matchResult[0] = StartPointer();
	matchResult[1] = SavePointer();
	matchResult[2] = ExitPointer();
	matchResult[3] = ResultExit();
	matchResult[4] = TitlePointer();
	if (matchResult[4] && inport(PM_LEFT))
	{
		//PlaySe(1);
		msleep(1000);
		// シーンをゲーム本編へ移行させる''
		SetScene(SCENE_TITLE);
	}
	if (matchResult[3] && inport(PM_LEFT))
	{
		//PlaySe(1);
		// ゲームを終了
		clrscr();   // 画面クリア
		exit(0);
	}
}

// ゲームリザルトの描画
void DrawReslut()
{
	char titleName[] = "GRAPPLE";
	char start[] = "START";
	char save[] = "CONTINUE";
	char exit[] = "EXIT";
	char title[] = "TITLE";
	char symbol = '>';
	int tCnt[5] = {};

	for (int cntY = 0; cntY < SCREEN_BOTTOM + 1; cntY++)
	{
		for (int cntX = 0; cntX < SCREEN_RIGHT + 1; cntX++)
		{
			switch (result[cntY][cntX])
			{
			case 0x30:
				if (!matchResult)
				{
					WriteTitleBuffer(cntX, cntY, ' ', { 0,0,0 }, { 0,0,0 }); // 黒
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, ' ', { 0,0,0 }, { 50,50,50 });
				}
				break;
			case 0x31:
				WriteTitleBuffer(cntX, cntY, ' ', { 120,120,120 }, { 120,120,120 });
				break;
			case 0x32:
				WriteTitleBuffer(cntX, cntY, titleName[tCnt[0]], { 0,0,0 }, { 120,120,120 });
				tCnt[0]++;
				break;
			case 0x33:
				if (!matchResult[0])
				{
					WriteTitleBuffer(cntX, cntY, start[tCnt[1]], { 180,180,180 }, { 50,50,50 });
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, start[tCnt[1]], { 255,255,255 }, { 50,50,50 });
				}
				;
				tCnt[1]++;
				break;
			case 0x34:
				WriteTitleBuffer(cntX, cntY, ' ', { 0,0,0 }, { 60,60,60 });
				break;
			case 0x35:
				if (!matchResult[1])
				{
					WriteTitleBuffer(cntX, cntY, save[tCnt[2]], { 180,180,180 }, { 50,50,50 });
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, save[tCnt[2]], { 255,255,255 }, { 50,50,50 });
				}
				tCnt[2]++;
				break;
			case 0x36:
				if (!matchResult[3])
				{
					WriteTitleBuffer(cntX, cntY, exit[tCnt[3]], { 180,180,180 }, { 50,50,50 });
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, exit[tCnt[3]], { 255,255,255 }, { 50,50,50 });
				}
				tCnt[3]++;
				break;
			case 0x37:
				if (!matchResult[4])
				{
					WriteTitleBuffer(cntX, cntY, symbol, { 50,50,50 }, { 50,50,50 });
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, symbol, { 255,255,255 }, { 50,50,50 });
				}
				break;
			case 0x38:
				if (!matchResult[3])
				{
					WriteTitleBuffer(cntX, cntY, symbol, { 50,50,50 }, { 50,50,50 });
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, symbol, { 255,255,255 }, { 50,50,50 });
				}
				break;
			case 0x39:
				if (!matchResult[1])
				{
					WriteTitleBuffer(cntX, cntY, symbol, { 50,50,50 }, { 50,50,50 });
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, symbol, { 255,255,255 }, { 50,50,50 });
				}
				break;
			case 0x41:
				if (!matchResult[4])
				{
					WriteTitleBuffer(cntX, cntY, title[tCnt[4]], { 180,180,180 }, {50,50,50});
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, title[tCnt[4]], { 255,255,255 }, { 50,50,50 });
				}
				tCnt[4]++;
				break;
			default:
				WriteTitleBuffer(cntX, cntY, ' ', { 0,0,0 }, { 0,0,0 }); // 黒
				break;
			}
		}
	}

	WriteTitleBuffer(80, 25, ' ', { 120,120,120 }, { 120,120,120 });
}

void LoadResultFile()
{
	char line[SCREEN_RIGHT * 3];
	int cntY = 0;
	int i = 0;

	if (!inResultFile.is_open())
	{
		return;
	}

	// BOMをスキップ
	char bom[3];
	inResultFile.read(bom, 3);
	if (!((unsigned char)bom[0] == 0xEF &&
		(unsigned char)bom[1] == 0xBB &&
		(unsigned char)bom[2] == 0xBF))
	{
		// BOMでなければ先頭に戻す
		inResultFile.seekg(0);
	}

	while (inResultFile.getline(line, sizeof(line)) && cntY < SCREEN_BOTTOM + 1)
	{
		i = 0;
		int cntX = 0;
		while (line[i] != '\0' && cntX < SCREEN_RIGHT + 1)
		{
			if (line[i] != ',')
			{
				result[cntY][cntX] = line[i];
				cntX++;
			}
			i++;
		}
		while (cntX < SCREEN_RIGHT + 1)
		{
			result[cntY][cntX] = '1';
			cntX++;
		}
		cntY++;
	}
	while (cntY < SCREEN_BOTTOM + 1)
	{
		for (int cntX = 0; cntX < SCREEN_RIGHT + 1; cntX++)
			result[cntY][cntX] = '1';
		cntY++;
	}
	isReadResultFile = true;
}