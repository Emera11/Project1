#include <Dxlib.h>
#include <iostream>
#include "../../Header/Title/Title.h"
#include "../../Header/Keyboard.h"
#include "../../Header/Global.h"
#include "../../Header/Math/Fader.h"
namespace
{
	const std::string g_TIMMY_LOGO_PATH = "./Data/Timmy/Timmy_logo256.png";
	const std::string g_TIMMY_LOGO_BACKGROUND_PATH = "./Data/BackGround/Logo_BackGround.png";
    const std::string  g_ERROR_SENTENCE = "が存在しません。";
	const int   g_LOGO_MAXFRAME = 70;
    int g_Logo_image[g_LOGO_MAXFRAME];
    const int   g_LOGO_BACKGROUND_MAXFRAME = 250;
    int g_Logo_BackGround_image[g_LOGO_BACKGROUND_MAXFRAME];
    const float g_logo_X = (g_WIN_WIDTH / 2.0f);

    float g_logo_Y = -500.0f;
    int g_Frame_Logo_Adjust = 0;
    int g_Frame_Logo = 0;
    int g_Frame_Logo_BackGround_Adjust = 0;
    int g_Frame_Logo_BackGround = 0;
    const float g_Elastic = -0.6;
    float g_Gravity = 0.0f;

    bool g_Logo_Renderflag = TRUE;

    int g_Logo_Progress_Frame = 0;
    const int g_LOGO_PROGRESS_MAXFRAME = 500;
    void m_Anim_Frame_Update(int& Subject_Frame_Adjust, int Frame_Adjust, int& Subject_Frame, const int MaxFrame)
    {
        if (Subject_Frame_Adjust == Frame_Adjust) {
            ++Subject_Frame;
            Subject_Frame_Adjust = 0;
        }
        if (Subject_Frame == MaxFrame - 1) {
            Subject_Frame = 0;
        }
        ++Subject_Frame_Adjust;
    }

 }                          

void Title::m_Logo_Render(void)
{
    if (g_Logo_Renderflag)
    {
        DrawRotaGraphF((g_WIN_WIDTH / 2.0f), (g_WIN_HEIGHT / 2.0f), 2.0, 0.0, g_Logo_BackGround_image[g_Frame_Logo_BackGround], TRUE, FALSE, FALSE);
        DrawRotaGraphF(g_logo_X, g_logo_Y, 1.5, 0.0, g_Logo_image[g_Frame_Logo], TRUE, FALSE, FALSE);
    }
}

void Title::m_Logo_Update(void)
{


    if (g_Logo_Renderflag)
    {
        ++g_Logo_Progress_Frame;
        g_Gravity += 0.4f;
        if (g_logo_Y >= (g_WIN_HEIGHT / 2))
        {
            g_Gravity *= g_Elastic;
        }
        g_logo_Y += g_Gravity;
        m_Anim_Frame_Update(g_Frame_Logo_BackGround_Adjust, 5, g_Frame_Logo_BackGround, g_LOGO_BACKGROUND_MAXFRAME);
        m_Anim_Frame_Update(g_Frame_Logo_Adjust, 5, g_Frame_Logo, g_LOGO_MAXFRAME);
    }
    if (g_Logo_Progress_Frame > g_LOGO_PROGRESS_MAXFRAME)
    {
        g_Logo_Renderflag = FALSE;
        g_Logo_Progress_Frame = g_LOGO_PROGRESS_MAXFRAME;
    }

    if (!g_Logo_Renderflag && g_Logo_Progress_Frame == g_LOGO_PROGRESS_MAXFRAME)
    {
        
    }
}



void Title::init(void)
{


    LoadDivGraph(g_TIMMY_LOGO_PATH.c_str(), g_LOGO_MAXFRAME, 5, 14, 256, 256, g_Logo_image);
    if (g_Logo_image[0] == -1)
    {
        const std::string  Tmp = g_TIMMY_LOGO_PATH + g_ERROR_SENTENCE;
        MessageBox(NULL, TEXT(Tmp.c_str()), TEXT("ファイルエラー"), MB_OK | MB_ICONHAND);
        DxLib_End();
    }

    LoadDivGraph(g_TIMMY_LOGO_BACKGROUND_PATH.c_str(), g_LOGO_BACKGROUND_MAXFRAME, 5, 50, 400, 300, g_Logo_BackGround_image);
    if (g_Logo_BackGround_image[0] == -1)
    {
        const std::string  Tmp = g_TIMMY_LOGO_BACKGROUND_PATH + g_ERROR_SENTENCE;
        MessageBox(NULL, TEXT(Tmp.c_str()), TEXT("ファイルエラー"), MB_OK | MB_ICONHAND);
        DxLib_End();
    }

}

Title::~Title()
{
}

void Title::Update(Keyboard* Key)
{
 
    m_Logo_Update();

}

void Title::Render(void)
{
    m_Logo_Render();
}

