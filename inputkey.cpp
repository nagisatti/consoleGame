//=============================================================================
//＜使い方＞
//		inputkey.cpp と inputkey.h をプロジェクト内に入れる
//		キー入力するプログラムに「#include "inputkey.h"」を入れる
//
//		GetKeyPress(KEYNAME::～～～～) → ～～～～のキーが押されている間
//		GetKeyTrigger(KEYNAME::～～～～) → ～～～～のキーが押された瞬間
//		GetKeyRelease(KEYNAME::～～～～) → ～～～～のキーが解放された瞬間
//		
//=============================================================================
#define CONIOEX
#include "conioex.h"
#include <iostream>

#include "inputkey.h"

//****************************************************************************
// キー入力の種類を増やした場合は、登録数も増やす
//****************************************************************************

// キーコンフィグ設定
#define KEY_CONFIG_MAX		(9)	//キーコンフィグの登録数

// キーコンフィグ構造体配列と初期化
KEYCONFIG g_Key[KEY_CONFIG_MAX] =
{
	//	キーの種類				conioexのキー
	{KEYNAME::KEY_RIGHT		,	PK_RIGHT	},
	{KEYNAME::KEY_LEFT		,	PK_LEFT		},
	{KEYNAME::KEY_JUMP		,	PK_UP		},
	{KEYNAME::KEY_D			,	PK_D		},
	{KEYNAME::KEY_A			,	PK_A		},
	{KEYNAME::KEY_W			,	PK_W		},
	{KEYNAME::KEY_S			,	PK_S		},
	{KEYNAME::KEY_LCLICK    ,   PM_LEFT     },
	{KEYNAME::KEY_SHOT		,	PK_SP		},	

	// 必要なだけ追加
};

// キー情報が格納される構造体配列
KEYSTATE g_KeyData[KEYNAME::KEY_NUM];//GAMEKEYNAMEの登録数分作る

//=============================================================================
// 初期化処理
//=============================================================================
void InitializeKey()
{
	//キー情報を０クリアする
	memset(&g_KeyData[0], 0, sizeof(g_KeyData));

}

//=============================================================================
// 終了処理
//=============================================================================
void FinalizeKey()
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateKey()
{
	//KEYCONFIGに登録されたキーの情報を取得
	for (int nCnt = 0; nCnt < KEY_CONFIG_MAX; nCnt++)
	{
		// 前回のキー情報を保存
		g_KeyData[g_Key[nCnt].name].pressOld = g_KeyData[g_Key[nCnt].name].press;

		// 現在のキー情報を取得
		g_KeyData[g_Key[nCnt].name].press = inport(g_Key[nCnt].code);

		// トリガー情報
		g_KeyData[g_Key[nCnt].name].trigger =
			(g_KeyData[g_Key[nCnt].name].pressOld ^ g_KeyData[g_Key[nCnt].name].press) & // 状態変化発生
			g_KeyData[g_Key[nCnt].name].press;                                           // キー押下

		// リリース情報
		g_KeyData[g_Key[nCnt].name].release =
			(g_KeyData[g_Key[nCnt].name].pressOld ^ g_KeyData[g_Key[nCnt].name].press) & // 状態変化発生
			(~g_KeyData[g_Key[nCnt].name].press);                                        // キー解放

	}

}

//=============================================================================
// 描画処理 (デバッグ表示用)
//=============================================================================
void DrawKey()
{
#ifdef _DEBUG
    // ControlKey();
#endif //_DEBUG
}

//=============================================================================
// トリガーデータ取得 (押した瞬間)
//=============================================================================
int GetKeyTrigger(KEYNAME key)
{
	return g_KeyData[key].trigger;
}

//=============================================================================
// リリースデータ取得 (押した瞬間)
//=============================================================================
int GetKeyRelease(KEYNAME key)
{
	return g_KeyData[key].release;
}

//=============================================================================
// プレスデータ取得 (押し続けている状態)
//=============================================================================
int GetKeyPress(KEYNAME key)
{
	return g_KeyData[key].press;
}

#ifdef _DEBUG
//=============================================================================
// コントローラ情報 (デバッグ表示用)
//=============================================================================
void ControlKey()
{

	// キーボード操作関係 ｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰ
	int nX = 4, nY = 3;			// 座標設定
	gotoxy(nX, nY);
	textcolor(LIGHTCYAN);
	std::cout << "KEY: ";
	// 上方向キー
	if (GetKeyTrigger(KEYNAME::KEY_JUMP) || GetKeyTrigger(KEYNAME::KEY_W))
	{// キーを押したとき
		textcolor(RED);
		std::cout << "@";
	}
	else if (GetKeyPress(KEYNAME::KEY_JUMP) || GetKeyPress(KEYNAME::KEY_W))
	{// キーを押している間
		textcolor(YELLOW);
		std::cout << "@";
	}
	else if (GetKeyRelease(KEYNAME::KEY_JUMP) || GetKeyRelease(KEYNAME::KEY_W))
	{// キーを離したとき
		textcolor(RED);
		std::cout << "0";
	}
	else
	{
		textcolor(LIGHTCYAN);
		std::cout << "0";
	}
	std::cout << "   ";
	// スペースキー
	if (GetKeyTrigger(KEYNAME::KEY_SHOT))
	{// キーを押したとき
		textcolor(RED);
		std::cout << "@";
	}
	else if (GetKeyPress(KEYNAME::KEY_SHOT))
	{// キーを押している間
		textcolor(YELLOW);
		std::cout << "@";
	}
	else if (GetKeyRelease(KEYNAME::KEY_SHOT))
	{// キーを離したとき
		textcolor(RED);
		std::cout << "0";
	}
	else
	{
		textcolor(LIGHTCYAN);
		std::cout << "0";
	}
	gotoxy(nX, nY + 1);
	std::cout << "    ";
	// 左方向キー
	if (GetKeyTrigger(KEYNAME::KEY_LEFT) || GetKeyTrigger(KEYNAME::KEY_A))
	{// キーを押したとき
		textcolor(RED);
		std::cout << "@";
	}
	else if (GetKeyPress(KEYNAME::KEY_LEFT) || GetKeyPress(KEYNAME::KEY_A))
	{// キーを押している間
		textcolor(YELLOW);
		std::cout << "@";
	}
	else if (GetKeyRelease(KEYNAME::KEY_LEFT) || GetKeyRelease(KEYNAME::KEY_A))
	{// キーを離したとき
		textcolor(RED);
		std::cout << "0";
	}
	else
	{
		textcolor(LIGHTCYAN);
		std::cout << "0";
	}
	std::cout << " ";
	// 左方向キー
	if (GetKeyTrigger(KEYNAME::KEY_RIGHT) || GetKeyTrigger(KEYNAME::KEY_D))
	{// キーを押したとき
		textcolor(RED);
		std::cout << "@";
	}
	else if (GetKeyPress(KEYNAME::KEY_RIGHT) || GetKeyPress(KEYNAME::KEY_D))
	{// キーを押している間
		textcolor(YELLOW);
		std::cout << "@";
	}
	else if (GetKeyRelease(KEYNAME::KEY_RIGHT) || GetKeyRelease(KEYNAME::KEY_D))
	{// キーを離したとき
		textcolor(RED);
		std::cout << "0";
	}
	else
	{
		textcolor(LIGHTCYAN);
		std::cout << "0";
	}
	// 色を元に戻す
	textcolor(LIGHTCYAN);

	// マウス操作関係 ｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰ
	int px = inport(PM_CURX);
	int py = inport(PM_CURY);
	gotoxy(18, 3);
	std::cout << "MOUSE  X:" << px << "     ";
	gotoxy(18, 4);
	std::cout << "       Y:" << py << "      ";
	gotoxy(18, 5);
	std::cout << "      LB:" << inport(PM_LEFT) << "      ";
	gotoxy(18, 6);
	std::cout << "      MB:" << inport(PM_MID);
	gotoxy(18, 7);
	std::cout << "      RB:" << inport(PM_RIGHT) << "      ";

	// コントローラ操作関係 ｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰｰ
	// コントローラ 左アナログスティック
	gotoxy(32, 3);
	std::cout << "JOY X座標:" << inport(PJ1_XPOS) << "      ";
	gotoxy(36, 4);
	std::cout << "Y座標:" << inport(PJ1_YPOS) << "      ";
	// コントローラ アクセル(RT)、ブレーキ(LT)
	gotoxy(36, 5);
	std::cout << "Z座標:" << inport(PJ1_ZPOS) << "      ";
	// コントローラ ボタン(ビット演算)
	gotoxy(35, 6);
	std::cout << "Button:" << inport(PJ1_BTNS) << "      ";
	// コントローラ 右アナログスティック
	gotoxy(34, 8);
	std::cout << "右X座標:" << inport(PJ1_RPOS) << "      ";
	gotoxy(34, 9);
	std::cout << "右Y座標:" << inport(PJ1_UPOS) << "      ";
	gotoxy(34, 10);
	// コントローラ 非対応
	std::cout << "右Z座標:" << inport(PJ1_VPOS) << "      ";
	// 十字キー
	gotoxy(29, 11);
	std::cout << "視点方向キー:" << inport(PJ1_POV) << "      ";

}
#endif //_DEBUG
