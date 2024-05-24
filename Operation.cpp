#include "Operation.h"
#include "./Header/Keyboard.h"
#include <math.h>

namespace
{
    
    int WALL[] = { 0, 1,1, 0,0,0,0 };
    double sign(double A) {
        if (A > 0) return 1;
        else if (A < 0) return -1;
        else return 0;
    }
}
void Operation::Init()
{
    m_Player_Data[0] = LoadGraph("./Data/test_Data/mgirl1.png");
    m_Player_Data[1] = LoadGraph("./Data/test_Data/mgirl2.png");
    m_Player_Data[2] = LoadGraph("./Data/test_Data/mgirl3.png");

    m_Player_Data_L[0] = LoadGraph("./Data/test_Data/mgirl1_L.png");
    m_Player_Data_L[1] = LoadGraph("./Data/test_Data/mgirl2_L.png");
    m_Player_Data_L[2] = LoadGraph("./Data/test_Data/mgirl3_L.png");
}

void Operation::Update(int * Scroll,  unsigned int m_Map_Data[Map_Y][Map_X], Keyboard* Key)
{

    anim_Sleep += 6.0f;
    if (Key->KeyDown(KEY_INPUT_LEFT)) {

        if(Plxp > -32) Plxp = -3;
        plDir = true;
       
        if (plAni <= 2)
        {
            if (anim_Sleep >= 50.0f)
            {
                plAni++;
                anim_Sleep = 0;
            }
        }
        else
        {
            plAni = 0;
        }
    }

    else if (Key->KeyDown(KEY_INPUT_RIGHT)) {
        if (Plxp < 32) Plxp = 3;
        plDir = false;
      
        if (plAni <= 2)
        {
            if (anim_Sleep >= 50.0f)
            {
                plAni++;
                anim_Sleep = 0;
            }
        }
        else
        {
            plAni = 0;
        }
    }
    else
    {
        plAni = 0;
        Plxp = Plxp * 0.9;   
    }

 
    auto lr = sign(Plxp);
    auto loop = abs((int)Plxp);

    while (loop > 0)
    {
        //Plx += lr;
        if (chkWall(Plx+lr, Ply, m_Map_Data) != false)
        {
            Plxp = 0;
            break;
        }
        if (Plx <= g_WIN_WIDTH - 150)
        {
            Plx += lr;
        }
        else
        {
            m_Scroll -= lr;
        }
        loop--;
    }

   



    if (plJump == 0)
    {
        
        
        JumpFrame += 1;
        if (!chkWall(Plx, Ply + 1, m_Map_Data))
        {//°‚ª‚È‚¢‚Æ—Ž‰º
            plJump = 2;
        }
        else if (Key->KeyDown(KEY_INPUT_SPACE) && JumpFrame >= 30)
        {
            Plyp = -6.0f;
            plJump = 1;
            JumpFrame = 0;
        }
    }
    else if (plJump == 1)
    {
        if (Key->KeyDown(KEY_INPUT_SPACE) )
        {
            Plyp += 0.1;
        }
        else
        {
            Plyp += 0.3f;
        }
        if (Plyp > 0) plJump = 2;
    }

    else //—Ž‰º’†
    {
        if (Key->KeyDown(KEY_INPUT_SPACE))
        {
            Plyp += 0.1f;
        }
        else
        {
            Plyp += 0.3f;
        }
        if (Plyp > 36) Plyp = 36;
    }

   

    auto ud = sign(Plyp);
    loop = abs((int)Plyp);

    while (loop > 0)
    {
        //Plx += lr;
        if (chkWall(Plx, Ply+ud, m_Map_Data) != false)
        {
            Plyp = 0;
            if (plJump == 1)
            {
                plJump = 2;
            }
            else if (plJump == 2)
            {
                plJump = 0;
                JumpFrame += 2.5f;
            }
           
            break;
        }
        Ply += ud;
        loop--;
    }

    //Ply += Plyp;

}

void Operation::Draw()
{
    //DrawRotaGraph(Plx, Ply, 1.5, 0.0, m_Player_Data[plAni], TRUE, plDir);
    if (plDir)
    {
        if (plAni == 0)
        {
            DrawGraph(Plx, Ply, m_Player_Data_L[0], TRUE);
        }

        if (plAni == 1)
        {
            DrawGraph(Plx, Ply, m_Player_Data_L[1], TRUE);
        }

        if (plAni == 2)
        {
            DrawGraph(Plx, Ply, m_Player_Data_L[2], TRUE);
        }
    }
    else
    {
        if (plAni == 0)
        {
            DrawGraph(Plx, Ply, m_Player_Data[0], TRUE);
        }

        if (plAni == 1)
        {
            DrawGraph(Plx, Ply, m_Player_Data[1], TRUE);
        }

        if (plAni == 2)
        {
            DrawGraph(Plx, Ply, m_Player_Data[2], TRUE);
        }
    }
}

int Wall[7] = { 0, 1, 1, 0, 0, 0, 0 };
bool Operation::chkWall(int cx, int cy, unsigned int m_Map_Data[Map_Y][Map_X])
{
    bool c = false;
    if (cx < 0 || 150 * Map_Chip_Size < cx) c = true;
    for (int i = 0; i < 4; ++i)
    {
        int x = (cx + CXP[i]) / Map_Chip_Size;
        int y = (cy + CYP[i]) / Map_Chip_Size;
        if (0 <= x && x <= 149 && 0 <= y && y <= 9) {
            if (Wall[m_Map_Data[y][x]] == 1) c = true;
        }
    }
    return c;
}