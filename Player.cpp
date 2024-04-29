#include <Dxlib.h>
#include "Stage.h"
#include "Player.h"

namespace
{
	const char* HANDLE_NAME = "./Data/Player/Takao.png";
    // 入力状態の初期化
    int g_Input{ 0 };
    int g_EdgeInput{ 0 };
    int g_JumpFlag = FALSE;
    Stage* g_Stage = new Stage();
}


void Player::Key_Init()
{
    // 入力状態を更新
    
    int i;

    // パッド１とキーボードから入力を得る
    i = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // エッジを取った入力をセット
    g_EdgeInput = i & ~g_Input;

    // 入力状態の保存
    g_Input = i;
    
}






void Player::PlayerMove()
{

    //Player_Control();

    float Dummy = 0.0f;
    float hsize_X;
    float hsize_Y;

    // キャラクタの左上、右上、左下、右下部分が当たり判定のある
    // マップに衝突しているか調べ、衝突していたら補正する

    // 半分のサイズを算出
    hsize_X = m_PLAYER_SIZE_X * 0.5f;
    hsize_Y = m_PLAYER_SIZE_Y * 0.5f;

    // 先ず上下移動成分だけでチェック
        // 左下のチェック、もしブロックの上辺に着いていたら落下を止める
        if (g_Stage->MapHitCheck(m_PlX - hsize_X, m_PlY + hsize_Y, &Dummy, &m_MoveY) == 3) m_PlDownSp = 0.0F;

        // 右下のチェック、もしブロックの上辺に着いていたら落下を止める
        if (g_Stage->MapHitCheck(m_PlX + hsize_X, m_PlY + hsize_Y, &Dummy, &m_MoveY) == 3) m_PlDownSp = 0.0F;

        // 左上のチェック、もしブロックの下辺に当たっていたら落下させる
        if (g_Stage->MapHitCheck(m_PlX - hsize_X, m_PlY - hsize_Y, &Dummy, &m_MoveY) == 4) m_PlDownSp *= -1.0F;

        // 右上のチェック、もしブロックの下辺に当たっていたら落下させる
        if (g_Stage->MapHitCheck(m_PlX + hsize_X, m_PlY - hsize_Y, &Dummy, &m_MoveY) == 4) m_PlDownSp *= -1.0F;

        // 上下移動成分を加算
        m_PlY += m_MoveY;

    // 後に左右移動成分だけでチェック
        // 左下のチェック
        g_Stage->MapHitCheck(m_PlX - hsize_X, m_PlY + hsize_Y, &m_MoveX, &Dummy);

        // 右下のチェック
        g_Stage->MapHitCheck(m_PlX + hsize_X, m_PlY + hsize_Y, &m_MoveX, &Dummy);

        // 左上のチェック
        g_Stage->MapHitCheck(m_PlX - hsize_X, m_PlY - hsize_Y, &m_MoveX, &Dummy);

        // 右上のチェック
        g_Stage->MapHitCheck(m_PlX + hsize_X, m_PlY - hsize_Y, &m_MoveX, &Dummy);

        // 左右移動成分を加算
        m_PlX += m_MoveX;
    


    // 接地判定
  
        // キャラクタの左下と右下の下に地面があるか調べる
        if (g_Stage->GetChipParam(m_PlX - m_PLAYER_SIZE_X  * 0.5F, m_PlY + m_PLAYER_SIZE_Y * 0.5F + 1.0F) == 0 &&
            g_Stage->GetChipParam(m_PlX + m_PLAYER_SIZE_X * 0.5F, m_PlY + m_PLAYER_SIZE_Y * 0.5F + 1.0F) == 0)
        {
            // 足場が無かったらジャンプ中にする
            g_JumpFlag= TRUE;
           
        }   
        else
        {
            // 足場が在ったら接地中にする
            g_JumpFlag= FALSE;
        }
}

void Player::Player_Control()
{
    Key_Init();
   

    // 移動量の初期化
    m_MoveX = 0.0F;
    m_MoveY = 0.0F;

    // 左右の移動を見る
    if ((g_Input & PAD_INPUT_LEFT) != 0)  m_MoveX -= m_SPEED;
    if ((g_Input & PAD_INPUT_RIGHT) != 0) m_MoveX += m_SPEED;

    // 地に足が着いている場合のみジャンプボタン(ボタン１ or Ｚキー)を見る
    if (g_JumpFlag == FALSE && (g_EdgeInput & PAD_INPUT_A) != 0)
    {
        m_PlDownSp = -m_JUMP_POWER;
        g_JumpFlag= TRUE;
    }

    // 落下処理
    m_PlDownSp += m_G;

    // 落下速度を移動量に加える
    m_MoveY = m_PlDownSp;

    PlayerMove();
}

void Player::m_Init()
{
    g_Stage->m_Init();
    m_Handle = LoadGraph(HANDLE_NAME);
}

void Player::m_Update()
{
    Player_Control();
    //PlayerMove();
}

void Player::m_Render()
{
    g_Stage->m_Render();
	DrawGraph(m_PlX, m_PlY, m_Handle, TRUE);
}

Player::Player()
{
    g_JumpFlag= FALSE;
}