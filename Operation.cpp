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
    int old_stage_num = { 0 };
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


void Operation::Update(int * Scroll,  unsigned int m_Map_Data[Map_Y][Map_X], Keyboard* Key, int& Stage_Num)
{
    

    anim_Sleep += 6.0f;


    if (Key->KeyDown(KEY_INPUT_LEFT)) {

        if(Plxp > -32) Plxp = -2;
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
        if (Plxp < 32) Plxp = 2;
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
        
        Plx += lr;
        loop--;
    }

   



    if (plJump == 0)
    {
        
        
        JumpFrame += 1;
        if (!chkWall(Plx, Ply + 1, m_Map_Data))
        {//è∞Ç™Ç»Ç¢Ç∆óéâ∫
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

    else //óéâ∫íÜ
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

    //if (Ply > g_WIN_HEIGHT) Ply = 0;

    if (Ply > g_WIN_HEIGHT) exit(1);//åäÇ…óéÇøÇΩ

    
    //ñÇñ@è≠èóÇÃà íuÇ…âΩÇ™Ç†ÇÈÇ©í≤Ç◊ÇÈ
    /*int cx = int(Plx / Map_Chip_Size);
    int cy = int(Ply / Map_Chip_Size);
    int chip = 0;
    if (0 <= cx && cx < 150 && 0 <= cy && cy < 9) chip = m_Map_Data[cy][cx];
    if (chip == 3) InitVar();
    if(chip == 4)  InitVar();//ìGÇ…êGÇÍÇÈ
    if (chip == 5) {//ÉSÅ[ÉãÉhÉpÅ[ÉãÇéÊÇÈ
        m_Map_Data[cy][cx] = 0;
    }
    if (Ply > g_WIN_HEIGHT) exit(1);//åäÇ…óéÇøÇΩ
    if (chip == 6)//Plx > Map_Chip_Size * 149)
    {
        InitVar();
        Stage_Num += 1;//ÉSÅ[ÉãÇµÇΩ
    }*/
    //Ply += Plyp;

    
    /*if (Stage_Num != old_stage_num)
    {
        InitVar();
    }

     old_stage_num = Stage_Num;*/
}

void Operation::Draw()
{
    //DrawRotaGraph(Plx, Ply, 1.5, 0.0, m_Player_Data[plAni], TRUE, plDir);
    if (plDir)
    {
        if (plAni == 0)
        {
            DrawGraph(cx, cy, m_Player_Data_L[0], TRUE);
        }

        if (plAni == 1)
        {
            DrawGraph(cx, cy, m_Player_Data_L[1], TRUE);
        }

        if (plAni == 2)
        {
            DrawGraph(cx, cy, m_Player_Data_L[2], TRUE);
        }
    }
    else
    {
        if (plAni == 0)
        {
            DrawGraph(cx, cy, m_Player_Data[0], TRUE);
        }

        if (plAni == 1)
        {
            DrawGraph(cx, cy, m_Player_Data[1], TRUE);
        }

        if (plAni == 2)
        {
            DrawGraph(cx, cy, m_Player_Data[2], TRUE);
        }
    }
}

int Wall[7] = { 0, 1, 1, 0, 0, 0, 0 };
bool Operation::chkWall(int cx, int cy, unsigned int m_Map_Data[Map_Y][Map_X])
{
    bool c = false;
    if (cx < 0 || 149 * Map_Chip_Size < cx) c = true;
    for (int i = 0; i < 4; ++i)
    {
        int x = int((cx + CXP[i]) / Map_Chip_Size);
        int y = int((cy + CYP[i]) / Map_Chip_Size);
        if (0 <= x && x <= 149 && 0 <= y && y <= 9) {
            if (Wall[m_Map_Data[y][x]] == 1) c = true;
            if (m_Map_Data[y][x] == 3)  exit(1);
            if (m_Map_Data[y][x] == 4)  exit(1);//ìGÇ…êGÇÍÇÈ
            if (m_Map_Data[y][x] == 5) {//ÉSÅ[ÉãÉhÉpÅ[ÉãÇéÊÇÈ
                m_Map_Data[y][x] = 0;
            }
           
            if (m_Map_Data[y][x] == 6)//Plx > Map_Chip_Size * 149)
            {
                InitVar();
                //Stage_Num += 1;//ÉSÅ[ÉãÇµÇΩ
            }
        }
    }
    return c;
}

void Operation::InitVar(void)
{
    Plx = 0;
    Ply = 0;
    Plxp = 0;
    Plyp = 0;
    plJump = 0;
    plDir = 0;
    plAni = 0;
}
