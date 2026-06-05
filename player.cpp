/*======================================================================================//
*  ・プレイヤー処理
*  初期化、生成、キー入力、移動制御、描画、最大描画範囲制御　を行っている
*
//======================================================================================*/
// アクションゲームの場合はdefineをコメントアウトする

#define ACTION

//****************************************************************************
//　インクルードファイル
//****************************************************************************

#include "main.h" 
#include "player.h"
#include "scene.h"
#include "inputkey.h"
#include "bullet.h"
#include "collision.h"
#include "life.h"
#include "calc.h"
#include "wireGen.h"
#include "camera.h"
#include "mousePointer.h"
#include "goal.h"
#include "sound.h"
#include "titleBuffer.h"
#include "stageManager.h"
#include "fieldDis.h"

//debug
#include "wireObject.h"
//****************************************************************************
//　グローバル変数
//****************************************************************************
PLAYER g_player;                           // プレイヤー情報
CALCOBJECT* g_calcobj = GetCalcPos();      // オブジェクト情報
CAMERA* g_cameraPlayer = GetCamera();      // カメラの座標情報
WIREOBJECT* g_wirePos = GetWireObjectPos();
int* g_pStage = GetStageManager();
bool isUseSH = false;                      // 弾の連射防止フラグ
bool isUseJP = false;                      // ジャンプ防止フラグ(障害物あると一生しちゃう)
bool isSe = false;

WIRESTATE* g_playerWire = GetWireState();  // ワイヤー状態

// プレイヤーの座標をポインタで渡す
PLAYER* GetPlayerPos()
{
	return &g_player;
}

// 自機の初期化
void InitializePlayer()
{
	// 配列でないため「&」をつける
	memset(&g_player, 0, sizeof(PLAYER));
	g_player.pos.x = 10.0f;
	g_player.pos.y = 19.0f;
}

// 自機の終了処理
void FinalizePlayer()
{

}

// 自機の更新
void UpdatePlayer()
{
	
#ifdef ACTION

	//if (g_player.isUseWr)
	//{
	//	ClearWire();
	//}

	// 座標位置の決定
	g_player.posOld.x = g_player.pos.x;
	g_player.posOld.y = g_player.pos.y;
	g_player.speedOld.x = g_player.speed.x;
	g_player.speedOld.y = g_player.speed.y;
	//g_player.speedOld.x += g_player.speed.x;
	//g_player.speedOld.y += g_player.speed.y;

	// 移動量のリセット
	// ジャンプの場合、重力等かかるためにy軸の力をリセットしない
	// ワイヤー使用中以外は移動量リセット
	/*if (!g_player.isUseWr || WIRE_IDLE)
	{
		g_player.speed.x = 0;
	}*/

	if (!g_player.isUseWr && *g_playerWire == WIRE_IDLE)
	{
		g_player.speed.x = 0;
	}

	if (g_player.isUseWr && *g_playerWire == WIRE_IDLE)
	{
		
		ClearWire();
		/*gotoxy((int)(g_player.posOld.x + 0.5f), (int)g_player.posOld.y);
		std::cout << " ";*/
		
	}

	//**********************************
    // キー入力処理
	//if (GetKeyPress(KEYNAME::KEY_W))
	//{ // 上移動
	//	if (!isUseJP)
	//	{
	//		if (!g_player.jump) // ジャンプ中じゃないとき
	//		{
	//			g_player.speed.y = -VALUE_JUMP;  // Y方向の移動地んいジャンプ加速値をセット
	//			g_player.jump = true;            // ジャンプ中フラグON
	//		}
	//	}
	//	isUseJP = true;
	//}
	//else
	//{
	//	isUseJP = false;
	//}
	if (*g_playerWire == WIRE_IDLE)
	{
		if (GetKeyPress(KEYNAME::KEY_A))
		{
			g_player.speed.x -= PLAYER_MOVE_SPEED_X;
		}
		if (GetKeyPress(KEYNAME::KEY_D))
		{
			g_player.speed.x += PLAYER_MOVE_SPEED_X;
		}
	}
	//if (GetKeyPress(KEYNAME::KEY_SHOT))
	//{
	//	if (!isUseSH)
	//	{
	//		//                                        x      y    弾の生成時のスピード設定
	//		CreateBullet(g_player.pos, g_player.angle, 0.3f, 0.0f);
	//		// std::cout << "spが押されました";
	//	}
	//	isUseSH = true;
	//}
	//else
	//{
	//	isUseSH = false;
	//}

	// X座標の制御
	if (g_player.jump)
	{ // ジャンプ中
		g_player.speed.x = g_player.speed.x + ((-g_player.speed.x) * VALUE_RESIST_X_AIR);   // 抵抗を加える
	}
	else
	{ // ジャンプ中でない
		g_player.speed.x = g_player.speed.x + ((-g_player.speed.x) * VALUE_RESIST_X);   // 抵抗を加える
	}

	// Y座標の制御
	if (*g_playerWire != WIRE_MOVING)
	{
		g_player.speed.y += VALUE_GRAVITY;
	}
	float copyPosY = g_player.pos.y + g_player.speed.y;
	if (copyPosY > SCREEN_BOTTOM - 1)
	{ // 地面にのめりこんだ場合
		// g_player.speed.y = -((float)(SCREEN_BOTTOM - 1) - copyPosY);  // 移動量のリセット
		g_player.speed.y = 0.0f;
		g_player.jump = false;          // ジャンプフラグのリセット

	}

	// 制御処理
	//if ((int)(g_player.pos.y + g_player.speed.y) < SCREEN_TOP + 1)
	//{
	//	g_player.speed.y = 0;
	//}
	//if ((int)(g_player.pos.x + g_player.speed.x) < SCREEN_LEFT + 1)
	//{
	//	g_player.speed.x = 0;
	//}
	//if ((int)(g_player.pos.x + g_player.speed.x + 1) > SCREEN_RIGHT - 1)
	//{
	//	g_player.speed.x = 0;
	//}

	// 壁の横判定
	PLAYER copy_player;
	memcpy(&copy_player, &g_player, sizeof(PLAYER));
	copy_player.pos.x += g_player.speed.x;
	if (PlayerCollisionWall(&copy_player))
	{
		g_player.speed.x = 0;
	}
	// 壁の縦の判定
	memcpy(&copy_player, &g_player, sizeof(PLAYER));
	copy_player.pos.y += g_player.speed.y;
	if (PlayerCollisionWall(&copy_player))
	{
		g_player.speed.y = 0;
		g_player.jump = false;
	}

	// 壁の横判定
	memcpy(&copy_player, &g_player, sizeof(PLAYER));
	copy_player.pos.x += g_player.speed.x;
	if (PlayerCollisionWall(&copy_player) || PlayerCollisionMoveWall(&copy_player) || PlayerCollisionDisWall(&copy_player))
	{
		g_player.speed.x = 0;
	}
	// 壁の縦判定
	memcpy(&copy_player, &g_player, sizeof(PLAYER));
	copy_player.pos.y += g_player.speed.y;
	if (PlayerCollisionWall(&copy_player) || PlayerCollisionMoveWall(&copy_player) || PlayerCollisionDisWall(&copy_player))
	{
		g_player.speed.y = 0;
		g_player.jump = false;
	}
	// シューティング用の処理
#else  // SHOTIONG 用

	//　現在の座標位置保存する
	g_player.posOld.x = g_player.pos.x;
	g_player.posOld.y = g_player.pos.y;

	// 移動量のリセット
	g_player.speed.x = 0;
	g_player.speed.y = 0;


	//**********************************
	// キー入力処理
	if (GetKeyPress(KEYNAME::KEY_W))
	{
		g_player.speed.y -= PLAYER_MOVE_SPEED_Y;
	}
	if (GetKeyPress(KEYNAME::KEY_S))
	{
		g_player.speed.y += PLAYER_MOVE_SPEED_Y;
	}
	if (GetKeyPress(KEYNAME::KEY_A))
	{
		g_player.speed.x -= PLAYER_MOVE_SPEED_X;
	}
	if (GetKeyPress(KEYNAME::KEY_D))
	{
		g_player.speed.x += PLAYER_MOVE_SPEED_X;
	}
	// 弾の連射防止処理
	// 最初falseでキーを押したときに一回だけ弾を発射する、
	// 押している間は処理に入れないため、連射できない
	// キーを離したらfalseに戻り、弾をもう一度発射可能になる
	if (GetKeyPress(KEYNAME::KEY_SHOT))
	{
		if (!isUse)
		{
			//                                        x      y    弾の生成時のスピード設定
			CreateBullet(g_player.pos, g_player.angle, 0.3f, 0.0f);
			// std::cout << "spが押されました";
		}
		isUse = true;
	}
	else
	{
		isUse = false;
	}

	// 制御処理
	// ダブルバイト文字のため + 1や -1をする
	// プレイヤーが★(全角のため)　　半角の場合はしなくてよい
	if ((int)(g_player.pos.y + g_player.speed.y) < SCREEN_TOP + 1)
	{ // 画面上部との衝突確認
		// 衝突した場合、移動できなくする
		g_player.speed.y = 0;
	}
	if ((int)(g_player.pos.y + g_player.speed.y) > SCREEN_BOTTOM - 1)
	{ // 画面下部との衝突確認
		// 衝突した場合、移動できなくする
		g_player.speed.y = 0;
	}
	if ((int)(g_player.pos.x + g_player.speed.x) < SCREEN_LEFT + 1)
	{ // 画面左部との衝突確認
		// 衝突した場合、移動できなくする
		g_player.speed.x = 0;
	}
	// ((int)(g_player.pos.x + g_player.speed.x + 1) > SCREEN_RIGHT - 1)
	// 左と壁の差を同じにしたい場合、上記のを使用
	if ((int)(g_player.pos.x + g_player.speed.x) > SCREEN_RIGHT - 1)
	{ // 画面右部との衝突確認
		// 衝突した場合、移動できなくする
		g_player.speed.x = 0;
	}

	// 壁の横判定
	PLAYER copy_player;
	memcpy(&copy_player, &g_player, sizeof(PLAYER));
	copy_player.pos.x += g_player.speed.x;
	if (PlayerCollisionWall(&copy_player))
	{
		g_player.speed.x = 0;
	}
	// 壁の縦の判定
	memcpy(&copy_player, &g_player, sizeof(PLAYER));
	copy_player.pos.y += g_player.speed.y;
	if (PlayerCollisionWall(&copy_player))
	{
		g_player.speed.y = 0;
	}
#endif // ACTION

	// 座標位置の決定

	if (*g_playerWire != WIRE_MOVING)
	{
		g_player.pos.x += g_player.speed.x;
		g_player.pos.y += g_player.speed.y;
	}

	// 下に落ちたときの判定
	if (g_player.pos.y >= 23)
	{
		g_player.pos.x = 10.0f;
		g_player.pos.y = 19.0f;
		g_player.speed.x = 0.0f;
		g_player.speed.y = 0.0f;
		g_player.jump = false;
	}

	//****************************************************************************
	//　当たり判定
	//****************************************************************************
	// 敵キャラクターとの当たり判定
	g_player.hit = PlayerCollisionEnemy(&g_player);
	if (g_player.hit && !g_player.hitOld)
	{ // 敵に当たるとライフ減少
		DownLife();
		g_player.hitOld = g_player.hit;
	}
	else if (!g_player.hit && g_player.hitOld)
	{ // 敵に当たってないときの履歴情報を更新する
		g_player.hitOld = g_player.hit;
	}

	// アイテムの当たり判定
	if (PlayerCollisionItem(&g_player))
	{
		UpLife();
	}

	// ゲームオーバー確認
	//if (CheckZeroLife())
	//{ // ライフがゼロの時
	//	SetScene(SCENE_RESULT);  // リザルトへ遷移
 //	}

	// ゴール判定
	if (GoalCollision(&g_player))
	{
		NextStage();             
		if (*g_pStage == 6)
		{
			SetScene(SCENE_RESULT);
		}
		//SetScene(SCENE_GAME);
		//SetScene(SCENE_RESULT);  // リザルトへ遷移

		clrscr();
	}

	//if (isSe)
	//{
	//	PlaySe(1);
	//}

	//****************************************************************************
	//　ワイヤー処理
	//****************************************************************************
	//・ワイヤーが伸びきってからプレイヤーを動かす処理に変更
	// 
	// ワイヤー発射処理

	int* obj;
	int hitWireObj = -1;
	obj = &hitWireObj;
	

	for (int cnt = 0; cnt < WIREGEN_MAX; cnt++)
	{
		WIREOBJECT* wireObjs = GetWireObjectPos();
		if (wireObjs[cnt].bUse && MousePointer(cnt))
		{
			hitWireObj = cnt;
			break;
		}
	}

	if (GetKeyPress(KEYNAME::KEY_LCLICK) && hitWireObj >= 0)
	{
		isSe = true;
		// ワイヤー状態処理
		switch (*g_playerWire)
		{
		case WIRE_IDLE:
			CalcPosition(hitWireObj);
			g_calcobj->currentLength = 0.0f;// 初期化設定
			*g_playerWire = WIRE_EXTENDING;
			break;
		case WIRE_EXTENDING:
			ClearWire();
			// ワイヤー移動中、または伸ばしている途中に床があったら移動禁止
			if (CheckMoveField(g_calcobj->wireStartPos,g_calcobj->st,g_calcobj->length))
			{
				ClearWire();
				g_calcobj->currentLength = 0.0f;
				*g_playerWire = WIRE_IDLE;
				break;
			}
			CreateWire();
			break;
		case WIRE_READY:
			//ClearWire();
			// ワイヤー移動を座標計算にしたためリセットが必要
			g_calcobj->currentLength = 0.0f;
			*g_playerWire = WIRE_MOVING;
			break;
		case WIRE_MOVING:
			if (LocationConf(hitWireObj))
			{
				*g_playerWire = WIRE_IDLE;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		if (*g_playerWire == WIRE_EXTENDING || *g_playerWire == WIRE_READY)
		{
			g_player.isUseWr = true;
			*g_playerWire = WIRE_IDLE;
			return;
		}
	}
	// ワイヤー移動処理
	if (*g_playerWire == WIRE_MOVING /*&& GetKeyPress(KEYNAME::KEY_LCLICK) && MousePointer()*/)
	{
		// 使用中にする
		g_player.isUseWr = true;


		if (!GetKeyPress(KEYNAME::KEY_LCLICK))
		{
			ClearWire();
			ShrinkWire();
			*g_playerWire = WIRE_IDLE;
			g_player.isUseWr = false;
			g_player.posOld.x = g_player.pos.x;
			g_player.posOld.y = g_player.pos.y;

			return;
		}


		// ClearWire();
		// 1ステップ進むごとに根元を1つ消す
		ShrinkWire();

		g_calcobj->currentLength += 0.5f;


		// プレイヤーの移動量に計算で出したステップごとの移動量をかける
		// 書けることによってどこからでも移動できる
		//g_player.speed.x = g_calcobj->st.x * PLAYER_MOVE_SPEED_X;
		//g_player.speed.y = g_calcobj->st.y * PLAYER_MOVE_SPEED_Y;
		//if (LocationConf())
		//{
		//	*g_playerWire = WIRE_IDLE;
		//	g_player.speed.x = 0;
		//	g_player.speed.y = 0;
		//
		//}		
		// 
		// 移動スピードとかいじってたらうまくいかなくなったからワイヤーの挙動を流用

		//g_calcobj->currentLength += 0.5f;


		g_player.pos.x = g_calcobj->playPos.x + (g_calcobj->st.x * g_calcobj->currentLength);
		g_player.pos.y = g_calcobj->playPos.y + (g_calcobj->st.y * g_calcobj->currentLength);

		float dx = g_wirePos[hitWireObj].pos.x - g_player.pos.x;
		float dy = g_wirePos[hitWireObj].pos.y - g_player.pos.y;

		bool nearObj = (abs(dx) <= 1.0f && abs(dy) <= 1.0f);
		bool overShot = (g_calcobj->currentLength >= g_calcobj->length);

		if (nearObj || overShot)
		{
			// オブジェクトの1マス手前で止める
			if (nearObj)
			{
				g_player.pos.x = g_wirePos[hitWireObj].pos.x - g_calcobj->st.x;
				g_player.pos.y = g_wirePos[hitWireObj].pos.y - g_calcobj->st.y;
			}
			ClearWire();
			*g_playerWire = WIRE_IDLE;
			g_player.isUseWr = false;
			g_player.speed.x = 0;
			g_player.speed.y = 0;
			g_player.posOld.x = g_player.pos.x;
			g_player.posOld.y = g_player.pos.y;
		}

		/*g_player.pos.x = g_player.posOld.x;
		g_player.pos.y = g_player.posOld.y;*/
	

		if (g_calcobj->currentLength >= g_calcobj->length)
		{
			*g_playerWire = WIRE_IDLE;
			g_player.isUseWr = false;
			g_player.speed.x = 0;
			g_player.speed.y = 0;
		}

	}
	else
	{
		//ClearWire();
		g_player.isUseWr = false;
		g_player.speed.x = 0;
	}

	//if ((int)g_cameraPlayer->cameraPos.x != (int)g_cameraPlayer->cameraOldPos.x ||
	//	(int)g_cameraPlayer->cameraPos.y != (int)g_cameraPlayer->cameraOldPos.y)
	//{
	//	ClearWireWithOldCamera();
	//	RedrawWire();
	//	//RedrawWire();
	//}

}

void DrawPlayer()
{
	float screenX = g_player.pos.x - g_cameraPlayer->cameraPos.x;
	float screenY = g_player.pos.y - g_cameraPlayer->cameraPos.y;

	float oldScreenX = g_player.posOld.x - g_cameraPlayer->cameraPos.x;
	float oldScreenY = g_player.posOld.y - g_cameraPlayer->cameraPos.y;

	if ((int)oldScreenX != (int)screenX || (int)oldScreenY != (int)screenY)
	{
		//WriteTitleBuffer((int)oldScreenX, (int)oldScreenY, ' ', { 0,0,0 }, { 255,255,255 });

		WriteBuffer((int)oldScreenX, (int)oldScreenY, ' ', WHITE);
	}

	//WriteTitleBuffer((int)oldScreenX, (int)oldScreenY, '@', { 255,255,255 }, { 0,0,0 });

	WriteBuffer((int)screenX, (int)screenY, 'P', WHITE);
}

// 自機の描画
//void DrawPlayer()
//{
//
//	float screenX = g_player.pos.x - g_cameraPlayer->cameraPos.x;
//	float screenY = g_player.pos.y - g_cameraPlayer->cameraPos.y;
//
//	float oldScreenX = g_player.posOld.x - g_cameraPlayer->cameraOldPos.x;
//	float oldScreenY = g_player.posOld.y - g_cameraPlayer->cameraOldPos.y;
//
//	// debug用表示
//	/*gotoxy(2, 5);
//	std::cout << "pos:(" << (int)g_player.pos.x << "," << (int)g_player.pos.y << ")      ";
//	gotoxy(2, 6);
//	std::cout << "scr:(" << (int)screenX << "," << (int)screenY << ")      ";
//	gotoxy(2, 7);
//	std::cout << "oldScr:(" << (int)oldScreenX << "," << (int)oldScreenY << ")      ";
//	gotoxy(2, 8);
//	std::cout << "camOld:(" << (int)g_cameraPlayer->cameraOldPos.x << "," << (int)g_cameraPlayer->cameraOldPos.y << ")      ";*/
//
//	/*
//	// 差分描画
//	// 座標位置が変更している場合
//	if ( ((int)(g_player.posOld.x) != (int)(g_player.pos.x)) ||
//		((int)(g_player.posOld.y) != (int)(g_player.pos.y)))
//	{
//		// ひとつ前の座標を取得
//		gotoxy((int)(g_player.posOld.x), (int)(g_player.posOld.y));
//		// 表示を消す
//		std::cout << "  ";
//	}
//	*/
//	if (oldScreenX != screenX || oldScreenY != screenY)
//	{
//		WriteBuffer((int)oldScreenX,(int)oldScreenY, ' ', WHITE);
//	}
//
//
//	
//	//if (((int)(g_player.posOld.x) != (int)(g_player.pos.x)) ||
//	//	((int)(g_player.posOld.y) != (int)(g_player.pos.y)))
//	//{
//	//	float oldScreenX = g_player.posOld.x - g_cameraPlayer->cameraPos.x;
//	//	float oldScreenY = g_player.posOld.y - g_cameraPlayer->cameraPos.y;
//	//	WriteBuffer((int)oldScreenX, (int)oldScreenY, ' ', WHITE);  // 古い位置を消す
//	//	// ひとつ前の座標を取得
//	//	//WriteBuffer((int)(g_player.posOld.x), (int)(g_player.posOld.y), ' ', WHITE);
//	//}
//
//	// 座標指定
//	//gotoxy((int)(g_player.pos.x), (int)(g_player.pos.y));
//	//WriteBuffer((int)(g_player.pos.x), (int)(g_player.pos.y), '@',WHITE);
//	gotoxy(2, 3);
//	std::cout << (int)g_cameraPlayer->cameraPos.x;
//	gotoxy(5, 3);
//	std::cout << (int)g_cameraPlayer->cameraPos.y;
//
//	gotoxy(10, 3);
//	std::cout << (int)g_player.pos.x;
//	gotoxy(13, 3);
//	std::cout << (int)g_player.pos.y;
//
//	WriteBuffer((int)(screenX), (int)(screenY), '@',WHITE);
//	//std::cout << "★";
//}