/*======================================================================================//
*  ・ワイヤーを生成するための処理
*
//======================================================================================*/

//****************************************************************************
//　インクルードファイル
//****************************************************************************
#include "main.h"
#include "calc.h"
#include "mousePointer.h"
#include "camera.h"
#include "wireGen.h"
#include "titleBuffer.h"

//****************************************************************************
//　グローバル変数
//****************************************************************************
CALCOBJECT* calcObj = GetCalcPos();
CAMERA* g_cameraWire = GetCamera();
static WIRESTATE g_wireState = WIRE_IDLE;

// ワイヤーの初期化
void InitializWireGen()
{

}

// ワイヤーの終了処理
void FinalizeWireGen()
{

}

// ワイヤーの更新
void UpdateWireGen()
{

}

// ワイヤーの描画
void DrowWireGen()
{

}


// ワイヤーを生成
void CreateWire()
{
    // 描画処理用変数
    float x = calcObj->playPos.x;
    float y = calcObj->playPos.y;
    float oldX = calcObj->playPos.x;
    float oldY = calcObj->playPos.y;

    float screenX = calcObj->playPos.x - g_cameraWire->cameraPos.x;
    float screenY = calcObj->playPos.y - g_cameraWire->cameraPos.y;

    float screenOldX = calcObj->playOldPos.x - g_cameraWire->cameraOldPos.x;
    float screenOldY = calcObj->playOldPos.y - g_cameraWire->cameraOldPos.y;

    // 1. 今の長さを更新（1フレームごとに 1.5ずつ伸ばす）
    if (calcObj->currentLength < calcObj->length)
    {
        calcObj->currentLength += 0.5f;
        if (calcObj->currentLength >= calcObj->length)
        {
            calcObj->currentLength = calcObj->length;
            g_wireState = WIRE_READY; 
        }
    }
    else 
    {
        calcObj->currentLength = calcObj->length; // 行き過ぎ防止
    }
    
    for (int cnt = 0; cnt <= (int)calcObj->currentLength; cnt++)
    {
        screenX = x - g_cameraWire->cameraPos.x;
        screenY = y - g_cameraWire->cameraPos.y;
        //WriteTitleBuffer((int)(x - g_cameraWire->cameraPos.x + 0.5f), (int)(y - g_cameraWire->cameraPos.y), '*', { 255,255,255 }, { 0,0,0 });

        WriteBuffer((int)(x - g_cameraWire->cameraPos.x + 0.5f), (int)(y - g_cameraWire->cameraPos.y),'*',WHITE);
        //WriteBuffer((int)(x + 0.5f), (int)(y - 0.5f),'*',WHITE);

        x += calcObj->st.x;
        y += calcObj->st.y;
       
    }

    
    
    //if (MousePointer())
    //{
    //    for (int i = 0; i <= calcObj->length; i++)
    //    {
    //        // アンチエイリアシング
    //        // ぼかしてガタガタをなくす
    //        // 描画終点の計算がちょっとずれてる
    //        //gotoxy((int)(x + 0.5f), (int)y );
    //        WriteBuffer((int)(x + 0.5f), (int)y, '*', WHITE);
    //        //std::cout << "*";

    //        /*
    //        * オブジェクトのつく前に刺さった感が欲しい、これはとりあえず
    //        * ちゃんとワイヤーができてから取り掛かる
    //        if (!(i + 1 >= calcObj->length))
    //        {
    //            std::cout << "*";
    //        }
    //        else
    //        {
    //            std::cout << "+";
    //        }
    //        */

    //        x += calcObj->st.x;
    //        y += calcObj->st.y;

    //        WriteBuffer((int)(x - calcObj->st.x + 0.5f), (int)(y - calcObj->st.y), ' ', WHITE);
    //        //gotoxy((int)(x - calcObj->st.x + 0.5f), (int)(y - calcObj->st.y));

    //        //std::cout << " ";

    //    }
    //}
    

}

void ClearWire()
{
    float x = calcObj->playPos.x;
    float y = calcObj->playPos.y;

    for (int cnt = 0; cnt <= (int)calcObj->length; cnt++)
    {
        // cameraOldPos ではなく cameraPos（現在のカメラ）で消す
        float screenOldX = x - g_cameraWire->cameraPos.x;
        float screenOldY = y - g_cameraWire->cameraPos.y;

        WriteBuffer((int)screenOldX, (int)screenOldY, ' ', WHITE);
        x += calcObj->st.x;
        y += calcObj->st.y;
    }

    //float x = calcObj->playOldPos.x;
    //float y = calcObj->playOldPos.y;

    //float screenOldX = calcObj->playOldPos.x - g_cameraWire->cameraOldPos.x;
    //float screenOldY = calcObj->playOldPos.y - g_cameraWire->cameraOldPos.y;

    //for (int cnt = 0; cnt <= (int)calcObj->length; cnt++)
    //{
    //    screenOldX = x - g_cameraWire->cameraOldPos.x;
    //    screenOldY = y - g_cameraWire->cameraOldPos.y;

    //    //WriteTitleBuffer((int)screenOldX, (int)screenOldY, ' ', { 255,255,255 }, { 255,255,255 });

    //    WriteBuffer((int)screenOldX, (int)screenOldY, ' ', WHITE);
    //    x += calcObj->st.x;
    //    y += calcObj->st.y;
    //}
}

// ワイヤーを徐々に消す（根元から縮める）
void ShrinkWire()
{
    float x = calcObj->playPos.x;  // ← playOldPos → playPos
    float y = calcObj->playPos.y;  // ← playOldPos → playPos

    // 消去開始位置をcurrentLengthに合わせて進める
    /*float x = calcObj->playOldPos.x;
    float y = calcObj->playOldPos.y;*/

    // currentLength分だけ進んだ位置から先を消す
    x += calcObj->st.x * calcObj->currentLength;
    y += calcObj->st.y * calcObj->currentLength;

    // 残っている部分（currentLength?length）を1ステップ消す
    float screenX = x - g_cameraWire->cameraPos.x + 0.5f;
    float screenY = y - g_cameraWire->cameraPos.y;

    //WriteTitleBuffer(screenX, screenY, ' ', { 255,255,255 }, { 255,255,255 });

    WriteBuffer((int)screenX, (int)screenY, ' ', WHITE);
}

void ClearWireWithOldCamera()
{
    float x = calcObj->playPos.x;
    float y = calcObj->playPos.y;

    for (int cnt = 0; cnt <= (int)calcObj->length; cnt++)
    {
        // 古いカメラ座標で消す
        float screenX = x - g_cameraWire->cameraOldPos.x + 0.5f;
        float screenY = y - g_cameraWire->cameraOldPos.y;
        WriteBuffer((int)screenX, (int)screenY, ' ', WHITE);
        x += calcObj->st.x;
        y += calcObj->st.y;
    }
}

void RedrawWire()
{
    if (calcObj->length <= 0)
    {
        return;
    }

    float x = calcObj->playPos.x;
    float y = calcObj->playPos.y;

    

    // currentLengthの分だけ現在のカメラ座標で再描画
    for (int cnt = 0; cnt <= (int)calcObj->currentLength; cnt++)
    {
        float screenX = x - g_cameraWire->cameraPos.x + 0.5f;
        float screenY = y - g_cameraWire->cameraPos.y;
        WriteBuffer((int)screenX, (int)screenY, '*', WHITE);
        x += calcObj->st.x;
        y += calcObj->st.y;
    }
}


WIRESTATE* GetWireState()
{
    return &g_wireState;
}