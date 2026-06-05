/*======================================================================================//
*  ・ポーズ処理
*
*
//======================================================================================*/

//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "main.h"
#include "pause.h"
#include "field.h"
#include "goal.h"
#include "mousePointer.h"
#include "player.h"
#include "moveGround.h"
#include "inputkey.h"
#include "wireObject.h"
#include "camera.h"
#include "sound.h"
#include "titleBuffer.h"
#include "stageManager.h"
#include "moveField.h"
#include "fieldDis.h"
#include <fstream>

//*****************************************************************************
// グローバル変数
//*****************************************************************************
char pause/*[MAX_READ_FILE]*/[SCREEN_BOTTOM + 1][SCREEN_RIGHT];      // タイトル画面を格納する変数
bool g_PauseFlg = false;
std::ifstream inPauseFile;
bool isReadPauseFile;		    // ファイル読み込みされたかどうかのフラグ
bool matchPause[4];				// 触れているかどうかのフラグ

int* g_stageNum = GetStageManager();

// ポーズシーンの初期化処理
void InitializePause(void)
{
	InitializeTitleBuffer();
	if (inPauseFile.is_open())
	{
		inPauseFile.close();
	}

	inPauseFile.open("C:/HAL東京/C++/進級制作/HEW2026_Project01/excel/title3.csv");

	isReadPauseFile = false;
	memset(matchPause, 0, sizeof(bool) * 4);
	//InitializeSound();

	if (isReadPauseFile)
	{
		return;
	}

	LoadPauseFile();
}

// ポーズシーンの更新処理
void UpdatePause(void)
{
	matchPause[0] = StartPointer();
	matchPause[1] = SavePointer();
	matchPause[2] = ExitPointer();
	if (matchPause[0] && inport(PM_LEFT))
	{
		ClearTitleBuffer();
		BuffReset();
		SetPause(false);
		clrscr();
		ReDrawFeild();
		ReDrawGoal();
		ReDrawDisFeild();
	}
	if (matchPause[0] && inport(PM_LEFT))
	{
		std::ofstream outputfile("C:/HAL東京/C++/進級制作/HEW2026_Project01/text/save.txt");
		outputfile << *g_stageNum;
		outputfile.close();
	}
	if (matchPause[2] && inport(PM_LEFT))
	{
		//PlaySe(1);
		// ゲームを終了
		clrscr();   // 画面クリア
		exit(0);
	}
	//if (inport(PK_ENTER)) // Enterキーが押されたとき
	//{
	//	// シーンをゲーム本編へ移行させる
	//	SetScene(SCENE_GAME);

	//if (inport(PK_ENTER))
	//{
	//	BuffReset();
	//	SetPause(false);
	//	clrscr();
	//	ReDrawFeild();
	//	ReDrawGoal();
	//	ReDrawDisFeild();
	//}
}

//****************************************************************************
//　・0 : 黒、1 : 白、2 : ポーズ表示、3 : セーブ、4 : 終わる
//  ・5 : 続きから、7～9 : 「>」を文字横に表示
// 
//　・エクセルに空白があるなら0を入れて黒塗りに変換される。
//****************************************************************************

// ポーズシーンの描画処理
void DrawPause(void)
{
	char titleName[] = "PAUSE";
	char play[] = "PLAY";
	char save[] = "SAVE";
	char exit[] = "EXIT";
	char symbol = '>';
	int tCnt[4] = {};



	for (int cntY = 0; cntY < SCREEN_BOTTOM + 1; cntY++)
	{
		for (int cntX = 0; cntX < SCREEN_RIGHT + 1; cntX++)
		{
			switch (pause[cntY][cntX])
			{
			case 0x30:
				if (!matchPause)
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
				//if (!match)
				//{
				WriteTitleBuffer(cntX, cntY, titleName[tCnt[0]], { 0,0,0 }, { 120,120,120 });
				//}
				/*else
				{
					WriteTitleBuffer(cntX, cntY, titleName[tCnt[0]], { 200,200,200 }, { 50,50,50 });
				}*/
				tCnt[0]++;
				break;
			case 0x33:
				if (!matchPause[0])
				{
					WriteTitleBuffer(cntX, cntY, play[tCnt[1]], { 180,180,180 }, { 50,50,50 });
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, play[tCnt[1]], { 255,255,255 }, { 50,50,50 });
				}
				;
				tCnt[1]++;
				break;
			case 0x34:
				WriteTitleBuffer(cntX, cntY, ' ', { 0,0,0 }, { 60,60,60 });
				break;
			case 0x35:
				if (!matchPause[1])
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
				if (!matchPause[2])
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
				if (!matchPause[0])
				{
					WriteTitleBuffer(cntX, cntY, symbol, { 50,50,50 }, { 50,50,50 });
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, symbol, { 255,255,255 }, { 50,50,50 });
				}
				break;
			case 0x38:
				if (!matchPause[1])
				{
					WriteTitleBuffer(cntX, cntY, symbol, { 50,50,50 }, { 50,50,50 });
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, symbol, { 255,255,255 }, { 50,50,50 });
				}
				break;
			case 0x39:
				if (!matchPause[2])
				{
					WriteTitleBuffer(cntX, cntY, symbol, { 50,50,50 }, { 50,50,50 });
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, symbol, { 255,255,255 }, { 50,50,50 });
				}
				break;
			default:
				WriteTitleBuffer(cntX, cntY, ' ', { 0,0,0 }, { 0,0,0 }); // 黒
				break;
			}
		}
	}
	//for (int cntX = 0; cntX < SCREEN_RIGHT + 1; cntX++)
	//{
	//	WriteTitleBuffer(cntX, SCREEN_BOTTOM, ' ', { 50,50,50 }, { 50,50,50 });
	//}

	// debug用
	//for (int cntY = 0; cntY < SCREEN_BOTTOM; cntY++)
	//{
	//	for (int cntX = 0; cntX < SCREEN_RIGHT; cntX++)
	//	{
	//		std::cout << title1[cntY][cntX];
	//	}
	//}

	//g_title.titleFrameCounter++;

	WriteTitleBuffer(80, 25, ' ', { 120,120,120 }, { 120,120,120 });


}

void LoadPauseFile()
{
	char line[SCREEN_RIGHT * 3];
	int cntY = 0;
	int i = 0;

	if (!inPauseFile.is_open())
		return;

	// BOMをスキップ
	char bom[3];
	inPauseFile.read(bom, 3);
	if (!((unsigned char)bom[0] == 0xEF &&
		(unsigned char)bom[1] == 0xBB &&
		(unsigned char)bom[2] == 0xBF))
	{
		// BOMでなければ先頭に戻す
		inPauseFile.seekg(0);
	}

	while (inPauseFile.getline(line, sizeof(line)) && cntY < SCREEN_BOTTOM + 1)
	{
		i = 0;
		int cntX = 0;
		while (line[i] != '\0' && cntX < SCREEN_RIGHT + 1)
		{
			if (line[i] != ',')
			{
				pause[cntY][cntX] = line[i];
				cntX++;
				//printf("line[%d] = %s\n", cntY, line);
			}

			i++;
		}
		while (cntX < SCREEN_RIGHT + 1)
		{
			pause[cntY][cntX] = '1';
			cntX++;
		}
		cntY++;
	}
	while (cntY < SCREEN_BOTTOM + 1)
	{
		for (int cntX = 0; cntX < SCREEN_RIGHT + 1; cntX++)
			pause[cntY][cntX] = '1';
		cntY++;
	}
	//printf("SCREEN_RIGHT=%d  読んだ列数確認\n", SCREEN_RIGHT);
	//printf("title1[0][79] = %d\n", title1[0][79]); // 80列目が読めているか
	//printf("title1[0][49] = %d\n", title1[0][49]); // 50列目
	//getch();
	isReadPauseFile = true;
}

// ポーズシーンの終了処理
void FinalizePause(void)
{
	inPauseFile.close();
}

// セッター
void SetPause(bool flg)
{
	g_PauseFlg = flg;
}

// ゲッター
bool GetPause()
{
	return g_PauseFlg;
}