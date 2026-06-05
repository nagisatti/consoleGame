/*======================================================================================//
*  ・説明画面の描画の為のヘッダー
*
//======================================================================================*/
//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "help.h"
#include "titleBuffer.h"
#include <fstream>
#include "scene.h"
#include "main.h"
#include "conioex.h"
#include "mousePointer.h"

//****************************************************************************
//　グローバル変数
//****************************************************************************
char help/*[MAX_READ_FILE]*/[SCREEN_BOTTOM + 1][SCREEN_RIGHT];      // タイトル画面を格納する変数

std::ifstream inHelpFile;
bool isReadHelpFile; // ファイル読み込みされたかどうかのフラグ
bool matchHelp[5];      // 触れているかどうかのフラグ


// 説明画面の初期化
void InitializeHelp()
{

	inHelpFile.open("C:/HAL東京/C++/進級制作/HEW2026_Project01/excel/help.csv");

	isReadHelpFile = false;
	memset(matchHelp, 0, sizeof(bool) * 5);

	if (isReadHelpFile)
	{
		return;
	}

	LoadHelpFile();
}

// 説明画面の終了処理
void FinalizeHelp()
{
	inHelpFile.close();
}

// 説明画面の更新
void UpdateHelp()
{
	matchHelp[0] = PlayPointer();
	matchHelp[1] = BackPointer();
	if (matchHelp[0] && inport(PM_LEFT))
	{
		// シーンをゲーム本編へ移行させる
		SetScene(SCENE_GAME);
	}
	if (matchHelp[1] && inport(PM_LEFT))
	{
		SetScene(SCENE_TITLE);
	}
}

//****************************************************************************
//　・0 : 黒、1 : 白、2 : 罫線「左上」、3 : 罫線「右上」、4 : 罫線「左下」
//  ・5 : 罫線「右下」、6 : 罫線「横」、7 : HOWto、8 : MOVE、9 : [A]
//  ・A : WIRE、B : [Click]、C : [Hold]、D : [Release]、E : GOAL、
//  ・F : Reach、G : 罫線「縦」、H : 罫線「├」、I : 罫線「┤」
//  ・J : Back、K : Next
// 
//　・エクセルに空白があるなら0を入れて灰塗りに変換される。
//****************************************************************************
// 説明画面の描画
void DrawHelp()
{
	char line[] = {'+','-','|'};
	char how[] = "HOWTOPLAY";
	char move[] = "MOVE";
	char as[] = "[A]<<Left[D]>>Right";
	char wire[] = "WIRE";
	char click[] = "[CLICK]>#";
	char hold[] = "[Hold]Movetohook";
	char release[] = "[Release] Drop";
	char goal[] = "GOAL";
	char reach[] = "Reach[G]tonextstage";
	char title[] = "BacktoTITLE";
	char game[] = "PlaytoGAME";
	char sign = '>';
	int tCnt[11] = {};

	for (int cntY = 0; cntY < SCREEN_BOTTOM + 1; cntY++)
	{
		for (int cntX = 0; cntX < SCREEN_RIGHT + 1; cntX++)
		{
			switch (help[cntY][cntX])
			{
			case 0x30:
				WriteTitleBuffer(cntX, cntY, ' ', { 0,0,0 }, { 50,50,50 });
				break;
			case 0x31:
				WriteTitleBuffer(cntX, cntY, ' ', { 120,120,120 }, { 120,120,120 });
				break;
			case 0x32:
				WriteTitleBuffer(cntX, cntY, line[0], { 255,255,255 }, { 120,120,120 });
				break;
			case 0x33:
				WriteTitleBuffer(cntX, cntY, line[0], { 255,255,255 }, { 120,120,120 });
				break;
			case 0x34:
				WriteTitleBuffer(cntX, cntY, line[0], { 255,255,255 }, { 120,120,120 });
				break;
			case 0x35:
				WriteTitleBuffer(cntX, cntY, line[0], { 255,255,255 }, { 120,120,120 });
				break;
			case 0x36:
				WriteTitleBuffer(cntX, cntY, line[1], { 255,255,255 }, { 120,120,120 });
				break;
			case 0x37:
				WriteTitleBuffer(cntX, cntY, how[tCnt[0]], {255,255,255}, {120,120,120});
				tCnt[0]++;
				break;
			case 0x38:
				WriteTitleBuffer(cntX, cntY, move[tCnt[1]], { 255,255,255 }, { 120,120,120 });
				tCnt[1]++;
				break;
			case 0x39:
				WriteTitleBuffer(cntX, cntY, as[tCnt[2]], { 255,255,255 }, { 120,120,120 });
				tCnt[2]++;
				break;
			case 0x41:
				WriteTitleBuffer(cntX, cntY, wire[tCnt[3]], { 255,255,255 }, { 120,120,120 });
				tCnt[3]++;
				break;
			case 0x42:
				WriteTitleBuffer(cntX, cntY, click[tCnt[4]], { 255,255,255 }, { 120,120,120 });
				tCnt[4]++;
				break;
			case 0x43:
				WriteTitleBuffer(cntX, cntY, hold[tCnt[5]], { 255,255,255 }, { 120,120,120 });
				tCnt[5]++;
				break;
			case 0x44:
				WriteTitleBuffer(cntX, cntY, release[tCnt[6]], { 255,255,255 }, { 120,120,120 });
				tCnt[6]++;
				break;
			case 0x45:
				WriteTitleBuffer(cntX, cntY, goal[tCnt[7]], { 255,255,255 }, { 120,120,120 });
				tCnt[7]++;
				break;
			case 0x46:
				WriteTitleBuffer(cntX, cntY, reach[tCnt[8]], { 255,255,255 }, { 120,120,120 });
				tCnt[8]++;
				break;
			case 0x47:
				WriteTitleBuffer(cntX, cntY, line[2], { 255,255,255 }, { 120,120,120 });
				break;
			case 0x48:
				WriteTitleBuffer(cntX, cntY, line[0], { 255,255,255 }, { 120,120,120 });
				break;
			case 0x49:
				WriteTitleBuffer(cntX, cntY, line[0], { 255,255,255 }, { 120,120,120 });
				break;
			case 0x4A:
				if (!matchHelp[1])
				{
					WriteTitleBuffer(cntX, cntY, title[tCnt[9]], { 180,180,180 }, { 50,50,50 });
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, title[tCnt[9]], { 255,255,255 }, { 50,50,50 });
				}				
				tCnt[9]++;
				break;
			case 0x4B:
				if(!matchHelp[0])
				{
					WriteTitleBuffer(cntX, cntY, game[tCnt[10]], { 180,180,180 }, { 50,50,50 });
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, game[tCnt[10]], { 255,255,255 }, { 50,50,50 });
				}
				tCnt[10]++;
				break;
			case 0x4C:
				if (!matchHelp[1])
				{
					WriteTitleBuffer(cntX, cntY, sign, { 50,50,50 }, { 50,50,50 });
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, sign, { 255,255,255 }, { 50,50,50 });
				}
				break;
			case 0x4D:
				if (!matchHelp[0])
				{
					WriteTitleBuffer(cntX, cntY, sign, { 50,50,50 }, { 50,50,50 });
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, sign, { 255,255,255 }, { 50,50,50 });
				}
				break;
			default:
				WriteTitleBuffer(cntX, cntY, ' ', { 0,0,0 }, { 0,0,0 }); // 黒
				break;

			}
		}
	}
	WriteTitleBuffer(80, 25, ' ', { 120,120,120 }, { 120,120,120 });
}

void LoadHelpFile()
{
	char line[SCREEN_RIGHT * 3];
	int cntY = 0;
	int i = 0;

	if (!inHelpFile.is_open())
	{
		return;
	}

	// BOMをスキップ
	char bom[3];
	inHelpFile.read(bom, 3);
	if (!((unsigned char)bom[0] == 0xEF &&
		(unsigned char)bom[1] == 0xBB &&
		(unsigned char)bom[2] == 0xBF))
	{
		// BOMでなければ先頭に戻す
		inHelpFile.seekg(0);
	}

	while (inHelpFile.getline(line, sizeof(line)) && cntY < SCREEN_BOTTOM + 1)
	{
		i = 0;
		int cntX = 0;
		while (line[i] != '\0' && cntX < SCREEN_RIGHT + 1)
		{
			if (line[i] != ',')
			{
				help[cntY][cntX] = line[i];
				cntX++;
				//printf("line[%d] = %s\n", cntY, line);
			}

			i++;
		}
		while (cntX < SCREEN_RIGHT + 1)
		{
			help[cntY][cntX] = '1';
			cntX++;
		}
		cntY++;
	}
	while (cntY < SCREEN_BOTTOM + 1)
	{
		for (int cntX = 0; cntX < SCREEN_RIGHT + 1; cntX++)
			help[cntY][cntX] = '1';
		cntY++;
	}
	//printf("SCREEN_RIGHT=%d  読んだ列数確認\n", SCREEN_RIGHT);
	//printf("title1[0][79] = %d\n", title1[0][79]); // 80列目が読めているか
	//printf("title1[0][49] = %d\n", title1[0][49]); // 50列目
	//getch();
	isReadHelpFile = true;
}