/*======================================================================================//
*  ・計算処理関数を書くためのcpp
*
//======================================================================================*/

//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "main.h"
#include "calc.h"
#include "player.h"
#include "wireObject.h"
#include "field.h"
#include "moveField.h"
//****************************************************************************
//　グローバル変数
//****************************************************************************
CALCOBJECT c_obj;                                // ワイヤー処理の計算用
PLAYER* playerCalc = GetPlayerPos();             // 現在のプレイヤー情報
WIREOBJECT* wireObjArray = GetWireObjectPos();   // 選択されたワイヤーオブジェクト情報
FIELD* fieldArray = GetField();                  // 床の情報
MOVEFIELD* moveFieldArray = GetMoveField();      // 動く床の情報

// オブジェクトの位置を計算、ワイヤーの表示タイプを返す関数
void CalcPosition(int index)
{
	c_obj.playOldPos.x = playerCalc->posOld.x;
	c_obj.playOldPos.y = playerCalc->posOld.y;

	c_obj.wireStartPos.x = c_obj.playPos.x;
	c_obj.wireStartPos.y = c_obj.playPos.y;

	// プレイヤーの座標
	float posX = playerCalc->pos.x;
	float posY = playerCalc->pos.y;
	// ワイヤーを飛ばせるオブジェクトの座標
	float objPosX = wireObjArray[index].pos.x;
	float objPosY = wireObjArray[index].pos.y;
	// プレイヤーとオブジェクトの差分取得
	c_obj.dif.x = objPosX - posX;
	c_obj.dif.y = objPosY - posY;

	c_obj.playPos.x = posX;
	c_obj.playPos.y = posY;

	// ワイヤーを何回描画するか
	// absで絶対値だけ取得
	c_obj.length = abs(c_obj.dif.x) > abs(c_obj.dif.y) ? abs(c_obj.dif.x) : abs(c_obj.dif.y);

	// 最大長を超えていたら届かないようにする
	if (c_obj.length > WIRE_MAX_LENGTH)
	{
		c_obj.length = 0.0f;  // 長さを0にして発射させない
		return;
	}

	if (CheckField(c_obj.playPos,c_obj.st, c_obj.length))
	{
		c_obj.length = 0.0f;
		return;
	}

	// 座標が一致している場合は計算しない
	if (c_obj.length == 0)
	{
		c_obj.st.x = 0.0f;
		c_obj.st.y = 0.0f;
		return;
	}

	// 1ステップあたりに進む量を計算
	c_obj.st.x = c_obj.dif.x / c_obj.length;
	c_obj.st.y = c_obj.dif.y / c_obj.length;

}

// ワイヤーの経路上に床があるかどうか
bool CheckField(vec2 start, vec2 st, float length)
{
	
	float x = start.x;
	float y = start.y;

	for (int cnt = 0; cnt <= (int)length; cnt++)
	{
		// 経路上の各点がフィールドと重なっていないかチェック
		for (int f = 0; f < FIELD_MAX; f++)
		{
			if (!fieldArray[f].bUse) continue;

			float fieldLeft = fieldArray[f].pos.x;
			float fieldRight = fieldArray[f].pos.x + fieldArray[f].scl.width;
			float fieldUp = fieldArray[f].pos.y;
			float fieldDown = fieldArray[f].pos.y + fieldArray[f].scl.height;

			if (x >= fieldLeft && x <= fieldRight &&
				y >= fieldUp && y <= fieldDown)
			{
				return true; // 経路上に床がある
			}
		}
		x += st.x;
		y += st.y;
	}
	return false;
}

bool CheckMoveField(vec2 start, vec2 st, float length)
{
	
	float x = start.x;
	float y = start.y;

	for (int cnt = 0; cnt <= (int)length; cnt++)
	{
		for (int f = 0; f < FIELD_MOVE_MAX; f++)
		{
			if (!moveFieldArray[f].bUse) continue;

			float fieldLeft = moveFieldArray[f].pos.x;
			float fieldRight = moveFieldArray[f].pos.x + moveFieldArray[f].scl.width;
			float fieldUp = moveFieldArray[f].pos.y;
			float fieldDown = moveFieldArray[f].pos.y + moveFieldArray[f].scl.height;

			if (x >= fieldLeft && x <= fieldRight &&
				y >= fieldUp && y <= fieldDown)
			{
				return true;
			}
		}
		x += st.x;
		y += st.y;
	}
	return false;
}


// プレイヤーの位置がワイヤーオブジェクトの範囲内かどうか
bool LocationConf(int index)
{
	float diffX = fabsf(wireObjArray[index].pos.x - playerCalc[index].pos.x);
	float diffY = fabsf(wireObjArray[index].pos.y - playerCalc[index].pos.y);
	if (diffX < 1.0f && diffY < 1.0f)
	{
		playerCalc->pos.x = wireObjArray[index].pos.x;
		playerCalc->pos.y = wireObjArray[index].pos.y;
		return true;
	}

	//if ((int)(wireObjArray->posCamera.x - playerCalc->pos.x) <= 1 &&
	//	(int)(wireObjArray->posCamera.y - playerCalc->pos.y) <= 1)
	//{
	//	return true;
	//}

	return false;
}


// 計算した座標等をポインタで渡す
CALCOBJECT* GetCalcPos()
{
	return &c_obj;
}

