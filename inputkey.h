#ifndef _INPUTKEY_H_
#define _INPUTKEY_H_

enum	KEYNAME	//ゲーム内で使うキーの種類
{
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_W,
	KEY_S,
	KEY_A,
	KEY_D,
	KEY_JUMP,
	KEY_SHOT,
	KEY_LCLICK,

	KEY_NUM,	// キーの種類数
};

struct	KEYSTATE		//キー状態(各キー設定1つに対して構造体１つ)
{
	int		trigger;	//押した瞬間
	int		release;	//離した瞬間
	int		press;		//現在のキー状態
	int		pressOld;	//前回のPressの値
};

struct	KEYCONFIG			//ゲーム内のキーとキーボードキーの割り当て
{
	KEYNAME		name;		//ゲーム内のキー種類
	int			code;		//conioex.hのキーボードのキーコード
};

//プロトタイプ宣言
void	InitializeKey();	//初期化
void	FinalizeKey();		//終了処理
void	UpdateKey();		//キー情報の更新
void	DrawKey();			//描画処理（デバッグ等で使う）

int		GetKeyTrigger(KEYNAME);	//キーのトリガー情報を取得
int		GetKeyPress(KEYNAME);	//キーのプレス情報を取得
int		GetKeyRelease(KEYNAME);	//キーのリリース情報を取得

#ifdef _DEBUG
void	ControlKey();			//コントローラ情報（デバッグ用）
#endif //_DEBUG

#endif //_INPUTKEY_H_
