#include <DxLib.h>
#include <iostream>
#include "../../Header/Player/Player.h"
#include "../../Header/Keyboard.h"

namespace
{
    const std::string  g_TIMMY_IDLE_PATH = "./Data/Timmy/Timmy_Idle.png";
    const std::string  g_TIMMY_WALK_PATH = "./Data/Timmy/Timmy_Walk.png";
    const std::string  g_TIMMY_RUN_PATH = "./Data/Timmy/Timmy_Run.png";
    const std::string  g_TIMMY_JUMP_PATH = "./Data/Timmy/Timmy_Jump.png";
    const std::string  g_TIMMY_THROW_PATH = "./Data/Timmy/Timmy_ThrowA.png";
    const std::string  g_ERROR_SENTENCE = "が存在しません。";
    const int   g_WALK_MAXFRAME = 38;
    const int   g_IDLE_MAXFRAME = 145;
    const int   g_JUMP_MAXFRAME = 30;
    const int   g_RUN_MAXFRAME = 24;
    const int   g_THROW_MAXFRAME = 52;
    int g_Walk_image[g_WALK_MAXFRAME];
    int g_Idle_image[g_IDLE_MAXFRAME];
    int g_Jump_image[g_JUMP_MAXFRAME];
    int g_Run_image[g_RUN_MAXFRAME];
    int g_Throw_image[g_THROW_MAXFRAME];
    bool g_CanJump = TRUE;
    bool g_Reverse = FALSE;
    bool g_Throw_flag = FALSE;
    bool g_Idle_flag = TRUE;
    int g_Anim_switch = 0;
    int   g_Frame = 0;
    int   g_Frame_adjust = 0;
    
    //関数

}

void Player::init(void)
{
    LoadDivGraph(g_TIMMY_WALK_PATH.c_str(), g_WALK_MAXFRAME, 2, 19, 64, 64, g_Walk_image);
    if (g_Walk_image[0] == -1)
    {
        const std::string  Tmp =  g_TIMMY_WALK_PATH + g_ERROR_SENTENCE;
        MessageBox(NULL, TEXT(Tmp.c_str()), TEXT("ファイルエラー"), MB_OK | MB_ICONHAND);
        End();
        DxLib_End();
    }

    LoadDivGraph(g_TIMMY_IDLE_PATH.c_str(), g_IDLE_MAXFRAME, g_IDLE_MAXFRAME, 1, 64, 64, g_Idle_image);
    if (g_Idle_image[0] == -1)
    {
        const std::string  Tmp = g_TIMMY_IDLE_PATH + g_ERROR_SENTENCE;
        MessageBox(NULL, TEXT(Tmp.c_str()), TEXT("ファイルエラー"), MB_OK | MB_ICONHAND);
        End();
        DxLib_End();
    }

    LoadDivGraph(g_TIMMY_JUMP_PATH.c_str(), g_JUMP_MAXFRAME, 2, 15, 64, 64, g_Jump_image);
    if (g_Jump_image[0] == -1)
    {
        const std::string  Tmp = g_TIMMY_JUMP_PATH + g_ERROR_SENTENCE;
        MessageBox(NULL, TEXT(Tmp.c_str()), TEXT("ファイルエラー"), MB_OK | MB_ICONHAND);
        End();
        DxLib_End();
    }

    LoadDivGraph(g_TIMMY_RUN_PATH.c_str(), g_RUN_MAXFRAME, 4, 6, 64, 64, g_Run_image);
    if (g_Run_image[0] == -1)
    {
        const std::string  Tmp = g_TIMMY_RUN_PATH + g_ERROR_SENTENCE;
        MessageBox(NULL, TEXT(Tmp.c_str()), TEXT("ファイルエラー"), MB_OK | MB_ICONHAND);
        End();
        DxLib_End();
    }

    LoadDivGraph(g_TIMMY_THROW_PATH.c_str(), g_THROW_MAXFRAME, 4, 13, 64, 64, g_Throw_image);
    if (g_Throw_image[0] == -1)
    {
        const std::string  Tmp = g_TIMMY_THROW_PATH + g_ERROR_SENTENCE;
        MessageBox(NULL, TEXT(Tmp.c_str()), TEXT("ファイルエラー"), MB_OK | MB_ICONHAND);
        End();
        DxLib_End();
    }

    m_Now_Timmy = g_Idle_image;
    m_Now_Timmy_Max_Frame = g_IDLE_MAXFRAME;

}

void Player::End(void)
{
    
    m_Timmy_Pos = { 0,0 };
    m_Now_Timmy= { 0 };
}




Player::~Player()
{
    End();
}


void Player::Operation(Keyboard* Key)
{
    m_Frame_Adjust_Check(3, g_Idle_image);
    m_Frame_Adjust_Check(3, g_Walk_image);
    m_Frame_Adjust_Check(3, g_Jump_image);
    m_Frame_Adjust_Check(3, g_Run_image);
    m_Frame_Adjust_Check(3, g_Throw_image);

    /*
    if (Frame_adjust == 3 && m_Now_Timmy == g_Idle_image) {
        Frame++;
        Frame_adjust = 0;
    }

    if (Frame_adjust == 3 && m_Now_Timmy == g_Walk_image) {
        Frame++;
        Frame_adjust = 0;
    }

    if (Frame_adjust == 3 && m_Now_Timmy == g_Jump_image) {
        Frame++;
        Frame_adjust = 0;
    }

    if (Frame_adjust == 3 && m_Now_Timmy == g_Run_image) {
        Frame++;
        Frame_adjust = 0;
    }

    if (Frame_adjust == 3 && m_Now_Timmy == g_Throw_image) {
        Frame++;
        Frame_adjust = 0;
    }*/



    // 右キーを押しているとき + Shift
    /*if (Key->KeyDown(KEY_INPUT_LSHIFT) && Key->KeyDown(KEY_INPUT_RIGHT)) {

        g_Reverse = FALSE;
        g_Throw_flag = FALSE;
        if (g_Anim_switch != 3)
        {
            m_X_Move_Speed = 2.0f;
            g_Frame = 0;
            g_Anim_switch = 3;
            g_Frame_adjust = 0;

        }

        if (g_Frame == g_RUN_MAXFRAME - 1)
        {
            g_Frame = 0;
        }

        // プレイヤーを右に移動させる
        m_Timmy_Pos.x += m_X_Move_Speed;

    }



    // 左キーを押しているとき + Shift
    else if (Key->KeyDown(KEY_INPUT_LSHIFT) && Key->KeyDown(KEY_INPUT_LEFT)) {

        g_Reverse = TRUE;
        g_Throw_flag = FALSE;
        if (g_Anim_switch != 3)
        {
            m_X_Move_Speed = -2.0f;
            g_Frame = 0;
            g_Anim_switch = 3;
            g_Frame_adjust = 0;

        }

        if (g_Frame == g_RUN_MAXFRAME - 1)
        {
            g_Frame = 0;
        }

        // プレイヤーを右に移動させる
        m_Timmy_Pos.x += m_X_Move_Speed;


    }

    // 左キーで左に移動
    else if (Key->KeyDown(KEY_INPUT_LEFT)) {
        g_Reverse = TRUE;
        g_Throw_flag = FALSE;
        if (g_Anim_switch != 1)
        {
            m_X_Move_Speed = -1.0f;
            g_Frame = 0;
            g_Anim_switch = 1;
            g_Frame_adjust = 0;
        }

        if (g_Frame == g_WALK_MAXFRAME - 1)
        {
            g_Frame = 0;
        }
        m_Timmy_Pos.x += m_X_Move_Speed;
    }





    // 右キーを押しているとき
    else if (CheckHitKey(KEY_INPUT_RIGHT)) {

        g_Reverse = FALSE;
        g_Throw_flag = FALSE;

        if (g_Anim_switch != 1)
        {
            m_X_Move_Speed = 1.0f;
            g_Frame = 0;
            g_Anim_switch = 1;
            g_Frame_adjust = 0;

        }

        if (g_Frame == g_WALK_MAXFRAME - 1)
        {
            g_Frame = 0;
        }

        // プレイヤーを右に移動させる
        m_Timmy_Pos.x += m_X_Move_Speed;

    }*/

    /*
    else if (CheckHitKey(KEY_INPUT_Z)) {

        g_Throw_flag = TRUE;
        if (g_Anim_switch != 4)
        {
            g_Frame = 0;
            g_Anim_switch = 4;
            g_Frame_adjust = 0;
        }

        else if (g_Frame == g_THROW_MAXFRAME - 1)
        {
            g_Frame = 0;
        }
    }

    else if (g_Throw_flag)
    {
        if (g_Anim_switch != 4)
        {
            g_Frame = 0;
            g_Anim_switch = 4;
            g_Frame_adjust = 0;
        }

        else if (g_Frame == g_THROW_MAXFRAME - 1)
        {
            g_Frame = 0;
            g_Throw_flag = FALSE;
        }
    }*/



    // スペースキーでジャンプ

    /*else if (CheckHitKey(KEY_INPUT_SPACE))
    {

        g_Throw_flag = FALSE;
        if (g_CanJump)
        {
            m_Jumping_Power = -10.0;
            g_CanJump = FALSE;
        }
    }

    else if (!g_CanJump && m_Timmy_Pos.y <= m_Glound_y)
    {
        if (g_Anim_switch != 2)
        {
            g_Frame = 0;
            g_Anim_switch = 2;
            g_Frame_adjust = 0;
        }

        if (g_Frame == g_JUMP_MAXFRAME - 1)
        {
            g_Frame = 0;
        }

    }

    else
    {
        if (g_Anim_switch != 0)
        {
            g_Frame = 0;
            g_Anim_switch = 0;
            g_Frame_adjust = 0;
        }

        if (g_Frame == g_IDLE_MAXFRAME - 1)
        {
            g_Frame = 0;
        }
        g_Anim_switch = 0;
    }*/
    

    if (!g_Idle_flag && g_Throw_flag == FALSE && g_CanJump == TRUE)
    {
        g_Idle_flag = TRUE;
    }
    m_XMove_Key(Key);
    m_Jump_Key(Key);
    m_Throw_Key(Key);
    if(g_Idle_flag) {
        if (g_Anim_switch != 0)
        {
            g_Frame = 0;
            g_Anim_switch = 0;
            g_Frame_adjust = 0;
        }

        if (g_Frame == g_IDLE_MAXFRAME - 1)
        {
            g_Frame = 0;
        }
        g_Anim_switch = 0;
    }
    g_Frame_adjust++;



    m_Anim_Switch_Check(0, g_Idle_image, g_IDLE_MAXFRAME);
    m_Anim_Switch_Check(1, g_Walk_image, g_WALK_MAXFRAME);
    m_Anim_Switch_Check(2, g_Jump_image, g_JUMP_MAXFRAME);
    m_Anim_Switch_Check(3, g_Run_image, g_RUN_MAXFRAME);
    m_Anim_Switch_Check(4, g_Throw_image, g_THROW_MAXFRAME);

    /*
    if (g_Anim_switch == 0 && m_Now_Timmy != Idle_image)
    {
        m_Now_Timmy = Idle_image;
        m_Now_Timmy_Max_Frame = &Idle_MaxFrame;
    }
    else if (Anim_switch == 1 && Now_Timmy != Walk_image)
    {
        Now_Timmy = Walk_image;
        Now_Timmy_Max_Frame = &Walk_MaxFrame;
    }
    else if (Anim_switch == 2 && Now_Timmy != Jump_image)
    {
        Now_Timmy = Jump_image;
        Now_Timmy_Max_Frame = &Jump_MaxFrame;
    }


    else if (Anim_switch == 3 && Now_Timmy != Run_image)
    {
        Now_Timmy = Run_image;
        Now_Timmy_Max_Frame = &Run_MaxFrame;
    }

    else if (Anim_switch == 4 && Now_Timmy != Throw_image)
    {
        Now_Timmy = Throw_image;
        Now_Timmy_Max_Frame = &Throw_MaxFrame;
    }*/


    if (!g_CanJump)
    {

        float y_tmp = m_Timmy_Pos.y;
        m_Timmy_Pos.y += (m_Timmy_Pos.y - m_Timmy_PosY_Prev) + m_Jumping_Power;
        m_Timmy_PosY_Prev = y_tmp;
        m_Jumping_Power = 0.3f;

    }





    if (m_Timmy_Pos.y >= m_Glound_y)
    {
        g_CanJump = TRUE;
    }


}


void Player::Render(void) const
{
    DrawRotaGraphF(m_Timmy_Pos.x, m_Timmy_Pos.y, 2.0, 0.0, m_Now_Timmy[g_Frame], TRUE, g_Reverse, FALSE);
}

void Player::m_Frame_Adjust_Check(int Frame_Adjust, int* NowTimmy)
{
    if (g_Frame_adjust == Frame_Adjust && m_Now_Timmy == NowTimmy) {
        g_Frame++;
        g_Frame_adjust = 0;
    }
}

void Player::m_XMove_Key(Keyboard* Key)
{
    // 右キーを押しているとき + Shift
    if (CheckHitKey(KEY_INPUT_LSHIFT)) {

        if (CheckHitKey(KEY_INPUT_RIGHT))
        {
            g_Idle_flag = FALSE;
            g_Reverse = FALSE;
            g_Throw_flag = FALSE;
            if (g_Anim_switch != 3)
            {
                g_Frame = 0;
                g_Anim_switch = 3;
                g_Frame_adjust = 0;

            }

            if (g_Frame == g_RUN_MAXFRAME - 1)
            {
                g_Frame = 0;
            }

            // プレイヤーを右に移動させる
            m_Timmy_Pos.x += 2.0f;
        }


        else if (CheckHitKey(KEY_INPUT_LEFT))
        {
            g_Idle_flag = FALSE;
            g_Reverse = TRUE;
            g_Throw_flag = FALSE;
            if (g_Anim_switch != 3)
            {
                g_Frame = 0;
                g_Anim_switch = 3;
                g_Frame_adjust = 0;

            }

            if (g_Frame == g_RUN_MAXFRAME - 1)
            {
                g_Frame = 0;
            }

            // プレイヤーを右に移動させる
            m_Timmy_Pos.x -= 2.0f;
        }
    }

    // 左キーで左に移動
    else if (CheckHitKey(KEY_INPUT_LEFT)) {
        g_Idle_flag = FALSE;
        g_Reverse = TRUE;
        g_Throw_flag = FALSE;
        if (g_Anim_switch != 1)
        {
            g_Frame = 0;
            g_Anim_switch = 1;
            g_Frame_adjust = 0;
        }

        if (g_Frame == g_WALK_MAXFRAME - 1)
        {
            g_Frame = 0;
        }
        m_Timmy_Pos.x -= 1.0f;
    }

    // 右キーを押しているとき
    else if (CheckHitKey(KEY_INPUT_RIGHT)) {
        g_Idle_flag = FALSE;
        g_Reverse = FALSE;
        g_Throw_flag = FALSE;

        if (g_Anim_switch != 1)
        {
            g_Frame = 0;
            g_Anim_switch = 1;
            g_Frame_adjust = 0;

        }

        if (g_Frame == g_WALK_MAXFRAME - 1)
        {
            g_Frame = 0;
        }

        // プレイヤーを右に移動させる
        m_Timmy_Pos.x += 1.0f;

    }

}

void Player::m_Jump_Key(Keyboard* Key)
{
    if (Key->KeyDown(KEY_INPUT_SPACE) && g_CanJump)
    {
        g_Idle_flag = FALSE;
        g_Throw_flag = FALSE;
        if (g_CanJump)
        {
            m_Jumping_Power = -12.0*m_Jumping_Power_weight;
            g_CanJump = FALSE;
        }
    }

    else if (!g_CanJump && m_Timmy_Pos.y <= m_Glound_y)
    {
        if (g_Anim_switch != 2)
        {
            g_Frame = 0;
            g_Anim_switch = 2;
            g_Frame_adjust = 0;
        }

        if (g_Frame == g_JUMP_MAXFRAME - 1)
        {
            g_Frame = 0;
        }
    }

}

void Player::m_Throw_Key(Keyboard* Key)
{
    if (Key->KeyClick(KEY_INPUT_Z)) {

        g_Idle_flag = FALSE;
        g_Throw_flag = TRUE;
        if (g_Anim_switch != 4)
        {
            g_Frame = 0;
            g_Anim_switch = 4;
            g_Frame_adjust = 0;
        }

        else if (g_Frame == g_THROW_MAXFRAME - 1)
        {
            g_Frame = 0;
        }
    }

    else if (g_Throw_flag)
    {
        if (g_Anim_switch != 4)
        {
            g_Frame = 0;
            g_Anim_switch = 4;
            g_Frame_adjust = 0;
        }
        
        else if (g_Frame == g_THROW_MAXFRAME - 1)
        {
            g_Frame = 0;
            g_Throw_flag = FALSE;
        }
    }
}

void Player::m_Anim_Switch_Check(int Anim_Switch, int* NowTimmy, const int MaxFrame)
{
    if (g_Anim_switch == Anim_Switch && m_Now_Timmy != NowTimmy)
    {
        m_Now_Timmy = NowTimmy;
        m_Now_Timmy_Max_Frame = MaxFrame;
    }
}