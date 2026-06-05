/*======================================================================================//
*  ・サウンド処理用
*
//======================================================================================*/

//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "main.h"
#include "sound.h"

//****************************************************************************
//　グローバル変数
//****************************************************************************
//----------- 効果音 -------------//
static unsigned long long g_wireSe = 0;          // ワイヤー発射
static unsigned long long g_titleSelectSe = 0;   // タイトルセレクト
static unsigned long long g_clickSe = 0;         // クリック音

//----------- BGM -------------//
static unsigned long long g_bgm = 0;           // BGM
//static int g_select = 0;                       // どのBGMか

// ワイヤーの初期化
void InitializeSound()
{
	g_wireSe = opensound((char*)"C:/HAL東京/C++/進級制作/HEW2026_Project01/se_hit_003.wav");
	g_bgm = opensound((char*)"C:/HAL東京/C++/進級制作/HEW2026_Project01/sound/mizunishizumupiano.mp3");
}

// ワイヤーの終了処理
void FinalizeSound()
{
	if (g_wireSe != 0)
	{
		closesound(g_wireSe);
	}
	else if (g_titleSelectSe != 0)
	{
		closesound(g_titleSelectSe);
	}
}

// ワイヤーの更新
void UpdateSound()
{
	if (g_wireSe != 0)
	{
		updatesound(g_wireSe);
	}
}

void PlaySe(int num)
{
	if (num == SOUND_SE_WIRE)
	{
		if (g_wireSe != 0)
		{
			stopsound(g_wireSe);
			playsound(g_wireSe, 0);
		}
	}
	else if (g_titleSelectSe != 0)
	{
		if (g_titleSelectSe != 0)
		{
			stopsound(g_titleSelectSe);
			playsound(g_titleSelectSe, 0);
		}
	}
	
}

void PlayBGM(int num)
{
	if (g_bgm != 0)
	{
		// ループ再生
		playsound(g_bgm, 1);
		
	}
}