
#include "../../Header/Math/Debug.h"
#include "../../Header/Global.h"
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
 
    bool g_Reverse = FALSE;
    bool g_Throw_flag = FALSE;
    bool g_Idle_flag = TRUE;
    int g_Anim_switch = 0;
    int   g_Frame = 0;
    int   g_Frame_adjust = 0;
    
    //プレイヤーが移動できる距離
    constexpr int g_PLAYER_MOVE_MAX = (g_WIN_WIDTH - 44) / 2;
    constexpr int g_PLAYER_MOVE_MIN = 300;
    
    bool g_Scroll_flag_R = false;
    bool g_Scroll_flag_L = false;
    bool g_Scroll_flag_Dash = false;

    constexpr float g_JUMP_Y_MAX = 2.000f;
    float g_Timmy_Change_Y = 0.0f;
    int g_Jump_time1 = 0;
    int g_Jump_time2 = 0;
    double g_Jump_All_time = 0.0;
    //float g_Landing_Count = 0.0f;
    float g_Jump_X = 0.0f;
    float g_Jump_MAX_X = 0.0f;

    float g_Gravity = 9.8f;
    //関数

    
}

void Player::init(void)
{
    debug.Init();
    //debug.Debug_Kun_Init(m_Timmy_Pos.x, m_Timmy_Pos.y);

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

bool Player::GetScroll_Flag_R()
{
    return g_Scroll_flag_R;
}

bool Player::GetScroll_Flag_L()
{
    return g_Scroll_flag_L;
}

bool Player::GetScroll_Flag_Dash()
{
    return g_Scroll_flag_Dash;
}

bool Player::GetJump_Flag()
{
    return m_CanJump;
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

 

    if (!g_Idle_flag && !g_Throw_flag && !m_CanJump)
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

 



}

 

void Player::Render(void)
{
    m_Landing_Count = m_Timmy_Pos.y - g_Timmy_Change_Y;
    g_Jump_MAX_X = m_Timmy_Pos.x - g_Jump_X;
    m_Timmy_ALL_Pos.x = m_Timmy_Pos.x;
    m_Timmy_ALL_Pos.y = m_Timmy_Pos.y - g_Timmy_Change_Y;

    debug.Add(std::to_string(m_Timmy_Pos.x));
    debug.Add(std::to_string(m_Timmy_Pos.y));
    debug.Add(std::to_string(g_Timmy_Change_Y));
    //debug.Add(std::to_string(Player_HitBox.Hit_Check_flag));    
    debug.Add(std::to_string(debug.Debug_Kun_X));
    debug.Add(std::to_string(debug.Debug_Kun_Y));
    debug.Add(std::to_string(Player_HitBox.Hit_Check_flag));
    debug.Add(std::to_string(m_Landing_Count));    
    
    DrawRotaGraphF(m_Timmy_ALL_Pos.x, m_Timmy_Pos.y-g_Timmy_Change_Y, 2.0, 0.0, m_Now_Timmy[g_Frame], TRUE, g_Reverse, FALSE);
    DrawBox(Player_HitBox.Hit_Box.left, Player_HitBox.Hit_Box.top - g_Timmy_Change_Y, Player_HitBox.Hit_Box.right, Player_HitBox.Hit_Box.bottom - g_Timmy_Change_Y, 100, FALSE);
    debug.Update();
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
     if(g_Scroll_flag_R || g_Scroll_flag_L || g_Scroll_flag_Dash)
    {
        g_Scroll_flag_R = false;
        g_Scroll_flag_L = false;
        g_Scroll_flag_Dash = false;
    }

    // 右キーを押しているとき + Shift
    if (CheckHitKey(KEY_INPUT_LSHIFT)) {

        g_Scroll_flag_Dash = true;
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
            if (g_PLAYER_MOVE_MAX >= m_Timmy_Pos.x)
            {
                m_Timmy_Pos.x += 2.0f;
                Player_HitBox.Hit_Box.right += 2;
                Player_HitBox.Hit_Box.left += 2;
            }
            else
            {
                g_Scroll_flag_R = true;
            }

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
            if (g_PLAYER_MOVE_MIN <= m_Timmy_Pos.x)
            {
                m_Timmy_Pos.x -= 2.0f;
                Player_HitBox.Hit_Box.right -= 2;
                Player_HitBox.Hit_Box.left  -= 2;
            }
            else
            {
                g_Scroll_flag_L = true;
            }
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
        // プレイヤーを右に移動させる
        if (g_PLAYER_MOVE_MIN <= m_Timmy_Pos.x)
        {
            m_Timmy_Pos.x -= 1.0f;
            Player_HitBox.Hit_Box.right -= 1;
            Player_HitBox.Hit_Box.left  -= 1;
            
        }
        else
        {
            g_Scroll_flag_L = true;
        }
        debug.Debug_Kun_X -= 1;
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
        if (g_PLAYER_MOVE_MAX >= m_Timmy_Pos.x)
        {
            m_Timmy_Pos.x += 1.0f;
            Player_HitBox.Hit_Box.right += 1;
            Player_HitBox.Hit_Box.left  += 1;
            
        }
        else
        {
            g_Scroll_flag_R = true;
        }
        debug.Debug_Kun_X += 1;
    }

    
  
}

void Player::m_Jump_Key(Keyboard* Key)
{
  

    if (Key->KeyClick(KEY_INPUT_SPACE) && !m_CanJump)
    {
        g_Idle_flag = FALSE;
        //g_Reverse = FALSE;
        g_Throw_flag = FALSE;
        g_Jump_time1 = GetNowCount();           //time1にエンターが押された時の時間を格納
        m_CanJump = true;                          //飛び上がりフラグを立てる。
    }


    else if (m_CanJump)
    {
        
        if (g_Anim_switch != 2)
        {
            g_Frame = 0;
            g_Anim_switch = 2;
            g_Frame_adjust = 0;
        }

        if (g_Frame == g_JUMP_MAXFRAME - 1)
        {
            g_Frame = g_JUMP_MAXFRAME - 2;
        }

        g_Jump_time2 = GetNowCount();                  // 現在経過時間を得る
        g_Jump_All_time = (double)(g_Jump_time2 - g_Jump_time1) / 1000.000;  // ミリ秒を秒に変換して、エンターが押されてからの経過時間を計算
        
       

       

        g_Timmy_Change_Y = (float)((sqrt(1.500 * g_G * g_JUMP_Y_MAX) * g_Jump_All_time - 0.500 * g_G * g_Jump_All_time * g_Jump_All_time) * 480 / g_JUMP_Y_MAX);//y座標を計算

        if (m_Landing_Count > m_Timmy_Pos.y)
        {
            g_Timmy_Change_Y = 0;
            g_Frame = 0;
            m_CanJump = false;
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