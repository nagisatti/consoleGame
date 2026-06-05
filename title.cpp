/*======================================================================================//
*  ・タイトル画面の処理
*
//======================================================================================*/
//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "main.h" 
#include "conioex.h"
#include "title.h"
#include "scene.h"
#include "camera.h"
#include <fstream>
#include "titleBuffer.h"
#include "mousePointer.h"
#include "sound.h"
#include "stageManager.h"

//****************************************************************************
//　グローバル変数
//****************************************************************************
char title/*[MAX_READ_FILE]*/[SCREEN_BOTTOM + 1][SCREEN_RIGHT];      // タイトル画面を格納する変数
//char title2[SCREEN_BOTTOM][SCREEN_RIGHT];      // タイトル画面を格納する変数
//char title3[SCREEN_BOTTOM][SCREEN_RIGHT];      // タイトル画面を格納する変数
//char title4[SCREEN_BOTTOM][SCREEN_RIGHT];      // タイトル画面を格納する変数
//char title5[SCREEN_BOTTOM][SCREEN_RIGHT];      // タイトル画面を格納する変数
//char title6[SCREEN_BOTTOM][SCREEN_RIGHT];      // タイトル画面を格納する変数

TITLE g_title;
std::ifstream inFile;
bool isReadFile; // ファイル読み込みされたかどうかのフラグ
bool match[4];      // 触れているかどうかのフラグ

int* g_sNum = GetStageManager();


// ゲームタイトルの初期化
void InitializeTitle()
{

	inFile.open("C:/HAL東京/C++/進級制作/HEW2026_Project01/excel/title1.csv");	

	// 初期化はここで
	isReadFile = false;
	memset(match, 0, sizeof(bool) * 4);
	//InitializeSound();
	g_title.titleFileInx = 0;
	g_title.titleFrameCounter = 0;

	if (isReadFile)
	{
		return;
	}

	g_title.loadCnt = 0;

	LoadFile();
}

// ゲームタイトルの終了処理
void FinalizeTitle()
{
	inFile.close();
}

// ゲームタイトルの更新
void UpdateTitle()
{
	match[0] = StartPointer();
	match[1] = SavePointer();
	match[2] = ExitPointer();
	if (match[0] && inport(PM_LEFT))
	{
		//PlaySe(1);
			// シーンをゲーム本編へ移行させる''
		SetScene(SCENE_HELP);
	}
	if (match[1] && inport(PM_LEFT))
	{
		std::ifstream stage("C:/HAL東京/C++/進級制作/HEW2026_Project01/text/save.txt");

		if (stage.is_open())
		{
			stage >> *g_sNum;
			stage.close();

			SetScene(SCENE_GAME);
		}
		else
		{
			char msg[] = "NO SAVE DATA";
			for (int cnt = 0; cnt < 12; cnt++)
			{
				WriteTitleBuffer(34 + cnt, 12, msg[cnt], { 255, 0, 0 }, { 0, 0, 0 });
			}
		}
	}
	if (match[2] && inport(PM_LEFT))
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
	//}
}

// ゲームタイトルの描画
//****************************************************************************
//　・0 : 黒、1 : 白、2 : タイトル表示、3 : start文字、4 : タイトルの下線部
//  ・5 : 続きから、7～9 : 「>」を文字横に表示
// 
//　・エクセルに空白があるなら0を入れて黒塗りに変換される。
//****************************************************************************
void DrawTitle()
{
	//WriteBuffer(0, 0, ' ', WHITE, true, WHITE);
	/*std::cout << "■■ タイトル ■■\n";
	std::cout << "Enterキーを押す\n";
	std::cout << title1[0][0];*/

	char titleName[] = "GRAPPLE";
	char start[] = "START";
	char save[] = "CONTINUE";
	char exit[] = "EXIT";
	char symbol = '>';
	int tCnt[4] = {};

	for (int cntY = 0; cntY < SCREEN_BOTTOM + 1; cntY++)
	{
		for (int cntX = 0; cntX < SCREEN_RIGHT + 1; cntX++)
		{
			switch (title[cntY][cntX])
			{
			case 0x30:
				if (!match)
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
				if (!match[0])
				{
					WriteTitleBuffer(cntX, cntY, start[tCnt[1]], {180,180,180}, {50,50,50});
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
				if (!match[1])
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
				if (!match[2])
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
				if (!match[0])
				{
					WriteTitleBuffer(cntX, cntY, symbol, { 50,50,50 }, { 50,50,50 });
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, symbol, { 255,255,255 }, { 50,50,50 });
				}
				break;
			case 0x38:
				if (!match[1])
				{
					WriteTitleBuffer(cntX, cntY, symbol, { 50,50,50 }, { 50,50,50 });
				}
				else
				{
					WriteTitleBuffer(cntX, cntY, symbol, { 255,255,255 }, { 50,50,50 });
				}
				break;
			case 0x39:
				if (!match[2])
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

	WriteTitleBuffer(80,25, ' ', { 120,120,120 }, { 120,120,120 });
}

void titleBuffer()
{

}

void LoadFile()
{
	char line[SCREEN_RIGHT * 3];
	int cntY = 0;
	int i = 0;

	if (!inFile.is_open())
		return;

	
	
	// BOMをスキップ
	char bom[3];
	inFile.read(bom, 3);
	if (!((unsigned char)bom[0] == 0xEF &&
		(unsigned char)bom[1] == 0xBB &&
		(unsigned char)bom[2] == 0xBF))
	{
		// BOMでなければ先頭に戻す
		inFile.seekg(0);
	}

	while (inFile.getline(line, sizeof(line)) && cntY < SCREEN_BOTTOM + 1)
	{
		i = 0;
		int cntX = 0;
		while (line[i] != '\0' && cntX < SCREEN_RIGHT + 1)
		{
			if (line[i] != ',')
			{
				title[cntY][cntX] = line[i];
				cntX++;
				//printf("line[%d] = %s\n", cntY, line);
			}

			i++;
		}
		while (cntX < SCREEN_RIGHT + 1)
		{
			title[cntY][cntX] = '1';
			cntX++;
		}
		cntY++;
	}
	while (cntY < SCREEN_BOTTOM + 1)
	{
		for (int cntX = 0; cntX < SCREEN_RIGHT + 1; cntX++)
			title[cntY][cntX] = '1';
		cntY++;
	}
	//printf("SCREEN_RIGHT=%d  読んだ列数確認\n", SCREEN_RIGHT);
	//printf("title1[0][79] = %d\n", title1[0][79]); // 80列目が読めているか
	//printf("title1[0][49] = %d\n", title1[0][49]); // 50列目
	//getch();
	isReadFile = true;
}

//void LoadFile()
//{
//	//なんでconst char
//	// ファイル名を格納
//	// 使わない部分はヌルポインター
//	const char* fileName[MAX_READ_FILE] = { "C:/HAL東京/C++/進級制作/HEW2026_Project01/excel/title1.csv",
//											//"C:/HAL東京/C++/進級制作/HEW2026_Project01/excel/title2.csv",
//											//"C:/HAL東京/C++/進級制作/HEW2026_Project01/excel/title3.csv",
//												nullptr };
//	
//	int i = 0;
//	
//
//	for (int fileInx = 0; fileInx < MAX_READ_FILE; fileInx++)
//	{
//		if (fileName[fileInx] == nullptr)
//		{
//			continue;
//		}
//
//		std::ifstream inFile(fileName[fileInx]);
//
//		// ファイルが存在しなかったら飛ばす
//		if (!inFile)
//		{
//			continue;
//		}
//
//		// BOMをスキップ
//		char bom[3];
//		inFile.read(bom, 3);
//		if (!((unsigned char)bom[0] == 0xEF &&
//			(unsigned char)bom[1] == 0xBB &&
//			(unsigned char)bom[2] == 0xBF))
//		{
//			// BOMでなければ先頭に戻す
//			inFile.seekg(0);
//		}
//		char line[SCREEN_RIGHT * 3];
//		int cntY = 0;
//
//		while (inFile.getline(line, sizeof(line)) && cntY < SCREEN_BOTTOM)
//		{
//			i = 0;
//			int cntX = 0;
//			while (line[i] != '\0' && cntX < SCREEN_RIGHT)
//			{
//				if (line[i] != ',')
//				{
//					title[fileInx][cntY][cntX] = line[i];
//					cntX++;
//					//printf("line[%d] = %s\n", cntY, line);
//				}
//
//				i++;
//			}
//			while (cntX < SCREEN_RIGHT)
//			{
//				title[fileInx][cntY][cntX] = '1';
//				cntX++;
//			}
//			cntY++;
//		}
//		while (cntY < SCREEN_BOTTOM)
//		{
//			for (int cntX = 0; cntX < SCREEN_RIGHT; cntX++)
//			{
//				title[fileInx][cntY][cntX] = '1';
//			}
//			cntY++;
//		}
//		//printf("SCREEN_RIGHT=%d  読んだ列数確認\n", SCREEN_RIGHT);
//		//printf("title1[0][79] = %d\n", title1[0][79]); // 80列目が読めているか
//		//printf("title1[0][49] = %d\n", title1[0][49]); // 50列目
//		//getch();
//		isReadFile = true;
//		g_title.loadCnt++;
//	}
//}