#include <Dxlib.h>
#include <iostream>
#include "../../Header/Title/Title.h"
#include "../../Header/Keyboard.h"
#include "../../Header/Global.h"
#include "../../Header/Math/Fader.h"


namespace
{
	const std::string g_TIMMY_LOGO_PATH = "./Data/Timmy/Timmy_logo256.png";
	const std::string g_TITLE_UI_PATH = "./Data/UI/Title_UI.png";
	const std::string g_TITLE_UI_TIMMY_PATH = "./Data/UI/Timmy_UI_Face.png";
	const std::string g_TITLE_UI_BIG_VEGA_PATH = "./Data/UI/BicVega_UI_Face.png";
	const std::string g_TITLE_UI_CLAIRE_PATH = "./Data/UI/Claire_UI_Face.png";
	const std::string g_TIMMY_LOGO_BACKGROUND_PATH = "./Data/BackGround/Logo_BackGround.png";
	const std::string g_TITLE_BACKGROUND_PATH = "./Data/BackGround/Title_BackGround.png";
	const std::string g_TITLE_LOGO_PATH = "./Data/UI/Title_Logo.png";
    const std::string  g_ERROR_SENTENCE = "が存在しません。";
	const int   g_LOGO_MAXFRAME = 70;
    const int   g_LOGO_BACKGROUND_MAXFRAME = 250;
    const int   g_TITLE_BACKGROUND_MAXFRAME = 309;
    const int   g_TITLE_UI_MAXFRAME = 6;
    const int g_LOGO_PROGRESS_MAXFRAME = 200;
    const int g_TITLE_UI_CHARACTER_MAXFRAME = 39;
    const float g_logo_X = (g_WIN_WIDTH / 2.0f);
    const float g_Elastic = -0.6;

    int g_Title_Logo_image = 0;
    int g_Logo_image[g_LOGO_MAXFRAME];
    int g_Logo_BackGround_image[g_LOGO_BACKGROUND_MAXFRAME];
    int g_Title_BackGround_image[g_TITLE_BACKGROUND_MAXFRAME];
    int g_Title_Ui_image[g_TITLE_UI_MAXFRAME];

    int g_Title_Ui_Timmy_image[g_TITLE_UI_CHARACTER_MAXFRAME];
    int g_Title_Ui_Big_Vega_image[g_TITLE_UI_CHARACTER_MAXFRAME];
    int g_Title_Ui_Claire_image[g_TITLE_UI_CHARACTER_MAXFRAME];


    float g_Title_Ui_Timmy_Frame{0.0f};
    float g_Title_Ui_Big_Vega_Frame{0.0f};
    float g_Title_Ui_Claire_Frame{0.0f};

    int g_Frame_Logo_Adjust = 0;
    int g_Frame_Logo = 0;
    int g_Frame_Logo_BackGround_Adjust = 0;
    int g_Frame_Logo_BackGround = 0;
    float g_Frame_Title_BackGround = 0.0f;

    int g_Logo_Progress_Frame = 0;
    float g_Gravity = 0.0f;
    float g_logo_Y = -500.0f;
    float g_Logo_Fade_Frame = 360.0f;
    bool g_Logo_Renderflag = TRUE;


    enum e_TITLE_SELECT_NUM
    {
        NEW=0,
        NEW_SELECT,
        NEXT,
        NEXT_SELECT,
        OPTION,
        OPTION_SELECT,

        eMenuNum
    };

    e_TITLE_SELECT_NUM e_New_Title_Select = NEW;
    e_TITLE_SELECT_NUM e_Next_Title_Select = NEXT;
    e_TITLE_SELECT_NUM e_Option_Title_Select = OPTION;

    int e_Now_Title_Select = 0;


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

    //切り替え先画面をアルファブレンディング
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, Angle_Sin(g_Logo_Fade_Frame) * 255);
    DrawRotaGraphF((g_WIN_WIDTH / 2.0f), (g_WIN_HEIGHT / 2.0f), 2.0, 0.0, g_Logo_BackGround_image[g_Frame_Logo_BackGround], TRUE, FALSE, FALSE);
    DrawRotaGraphF(g_logo_X, g_logo_Y, 1.5, 0.0, g_Logo_image[g_Frame_Logo], TRUE, FALSE, FALSE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


}

void Title::m_Logo_Update(void)
{

    
    g_Gravity += 0.4f;
    if (g_logo_Y >= (g_WIN_HEIGHT / 2))
    {
        g_Gravity *= g_Elastic;
    }
    g_logo_Y += g_Gravity;
    m_Anim_Frame_Update(g_Frame_Logo_BackGround_Adjust, 5, g_Frame_Logo_BackGround, g_LOGO_BACKGROUND_MAXFRAME);
    m_Anim_Frame_Update(g_Frame_Logo_Adjust, 5, g_Frame_Logo, g_LOGO_MAXFRAME);

    if (g_Logo_Progress_Frame < g_LOGO_PROGRESS_MAXFRAME)
    {
        ++g_Logo_Progress_Frame;
    }
    else
    {
        g_Logo_Progress_Frame = g_LOGO_PROGRESS_MAXFRAME;
    }

    if (g_Logo_Progress_Frame == g_LOGO_PROGRESS_MAXFRAME)
    {
        if (g_Logo_Fade_Frame > 0)
        {
            g_Logo_Fade_Frame -= 0.5f;
        }
        else
        {
            g_Logo_Fade_Frame = 0;
            g_Logo_Renderflag = FALSE;
            m_Title_Renderflag = TRUE;
        }
    };

  

}

void Title::m_Title_Render(void)
{
    //切り替え先画面をアルファブレンディング
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, Angle_Sin(m_Title_Frame) * 255);

    DrawRotaGraphF((g_WIN_WIDTH / 2.0f), (g_WIN_HEIGHT / 2.0f), 2.0, 0.0,  g_Title_BackGround_image[(int)g_Frame_Title_BackGround], TRUE, FALSE, FALSE);
    DrawRotaGraphF((g_WIN_WIDTH / 2.0f)+10, (g_WIN_HEIGHT / 2.0f), 1.0, 0.0, g_Title_Ui_image[e_New_Title_Select], TRUE, FALSE, FALSE);
    DrawRotaGraphF((g_WIN_WIDTH / 2.0f)+10, (g_WIN_HEIGHT / 2.0f)+100.0f, 1.0, 0.0, g_Title_Ui_image[e_Next_Title_Select], TRUE, FALSE, FALSE);
    DrawRotaGraphF((g_WIN_WIDTH / 2.0f)+10, (g_WIN_HEIGHT / 2.0f)+200.0f, 1.0, 0.0, g_Title_Ui_image[e_Option_Title_Select], TRUE, FALSE, FALSE);
    DrawRotaGraphF((g_WIN_WIDTH / 2.0f)-150, (g_WIN_HEIGHT / 2.0f), 0.5, 0.0,          g_Title_Ui_Timmy_image[(int)g_Title_Ui_Timmy_Frame], TRUE, FALSE, FALSE);
    DrawRotaGraphF((g_WIN_WIDTH / 2.0f)-150, (g_WIN_HEIGHT / 2.0f) + 100.0f, 0.5, 0.0, g_Title_Ui_Big_Vega_image[(int)g_Title_Ui_Big_Vega_Frame], TRUE, FALSE, FALSE);
    DrawRotaGraphF((g_WIN_WIDTH / 2.0f)-150, (g_WIN_HEIGHT / 2.0f) + 200.0f, 0.5, 0.0, g_Title_Ui_Claire_image[(int)g_Title_Ui_Claire_Frame], TRUE, FALSE, FALSE);
    DrawRotaGraphF((g_WIN_WIDTH / 2.0f)+20, (g_WIN_HEIGHT / 2.0f)-150, 1.7, 0.0, g_Title_Logo_image, TRUE, FALSE, FALSE);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Title::m_Title_Update(Keyboard* Key)
{
    if (g_Frame_Title_BackGround < g_TITLE_BACKGROUND_MAXFRAME - 1)
    {
        g_Frame_Title_BackGround += 0.1f;
    }
    else
    {
        g_Frame_Title_BackGround = 0;
    }

    if (100.0f>= m_Title_Frame)
    {
        m_Title_Frame += 0.3f;
    }
    else
    {

        if (Key->KeyClick(KEY_INPUT_UP))
        {
            e_Now_Title_Select = (e_Now_Title_Select + (3 - 1)) % 3;
            g_Title_Ui_Timmy_Frame = 0 ;
            g_Title_Ui_Big_Vega_Frame = 0 ;
            g_Title_Ui_Claire_Frame =  0 ;
        }
        else if (Key->KeyClick(KEY_INPUT_DOWN))
        {
            e_Now_Title_Select = (e_Now_Title_Select + 1) % 3;//選択状態を一つ下げる
            g_Title_Ui_Timmy_Frame = 0;
            g_Title_Ui_Big_Vega_Frame = 0;
            g_Title_Ui_Claire_Frame = 0;
        }

        switch (e_Now_Title_Select)
        {
        case 0:
            e_New_Title_Select = NEW_SELECT;
            e_Next_Title_Select = NEXT;
            e_Option_Title_Select = OPTION;
            if (g_Title_Ui_Timmy_Frame < g_TITLE_UI_CHARACTER_MAXFRAME-1)
            {
                g_Title_Ui_Timmy_Frame += 0.5f;
            }
            break;
        case 1:
            e_New_Title_Select = NEW;
            e_Next_Title_Select = NEXT_SELECT;
            e_Option_Title_Select = OPTION;
            if (g_Title_Ui_Big_Vega_Frame < g_TITLE_UI_CHARACTER_MAXFRAME - 1)
            {
                g_Title_Ui_Big_Vega_Frame += 0.5f;
            }
            break;
        case 2:
            e_New_Title_Select = NEW;
            e_Next_Title_Select = NEXT;
            e_Option_Title_Select = OPTION_SELECT;
            if (g_Title_Ui_Claire_Frame < g_TITLE_UI_CHARACTER_MAXFRAME - 1)
            {
                g_Title_Ui_Claire_Frame += 0.5f;
            }
            break;
        default:
            break;
        }
    }
}



void Title::init(void)
{

    g_Title_Logo_image =  LoadGraph(g_TITLE_LOGO_PATH.c_str());
    if (g_Title_Logo_image == -1)
    {
        const std::string  Tmp = g_TITLE_LOGO_PATH + g_ERROR_SENTENCE;
        MessageBox(NULL, TEXT(Tmp.c_str()), TEXT("ファイルエラー"), MB_OK | MB_ICONHAND);
        DxLib_End();
    }


    LoadDivGraph(g_TITLE_BACKGROUND_PATH.c_str(), g_TITLE_BACKGROUND_MAXFRAME, 3, 103, 400, 300, g_Title_BackGround_image);
    if (g_Title_BackGround_image[0] == -1)
    {
        const std::string  Tmp = g_TITLE_BACKGROUND_PATH + g_ERROR_SENTENCE;
        MessageBox(NULL, TEXT(Tmp.c_str()), TEXT("ファイルエラー"), MB_OK | MB_ICONHAND);
        DxLib_End();
    }

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

    LoadDivGraph(g_TITLE_UI_PATH.c_str(), g_TITLE_UI_MAXFRAME, 2, 3, 300, 70, g_Title_Ui_image);
    if (g_Title_Ui_image[0] == -1)
    {
        const std::string  Tmp = g_TITLE_UI_PATH + g_ERROR_SENTENCE;
        MessageBox(NULL, TEXT(Tmp.c_str()), TEXT("ファイルエラー"), MB_OK | MB_ICONHAND);
        DxLib_End();
    }

    LoadDivGraph(g_TITLE_UI_TIMMY_PATH.c_str(), g_TITLE_UI_CHARACTER_MAXFRAME, 3, 13, 128, 128, g_Title_Ui_Timmy_image);
    if (g_Title_Ui_Timmy_image[0] == -1)
    {
        const std::string  Tmp = g_TITLE_UI_TIMMY_PATH + g_ERROR_SENTENCE;
        MessageBox(NULL, TEXT(Tmp.c_str()), TEXT("ファイルエラー"), MB_OK | MB_ICONHAND);
        DxLib_End();
    }

    LoadDivGraph(g_TITLE_UI_BIG_VEGA_PATH.c_str(), g_TITLE_UI_CHARACTER_MAXFRAME, 3, 13, 128, 128, g_Title_Ui_Big_Vega_image);
    if (g_Title_Ui_Big_Vega_image[0] == -1)
    {
        const std::string  Tmp = g_TITLE_UI_BIG_VEGA_PATH + g_ERROR_SENTENCE;
        MessageBox(NULL, TEXT(Tmp.c_str()), TEXT("ファイルエラー"), MB_OK | MB_ICONHAND);
        DxLib_End();
    }

    LoadDivGraph(g_TITLE_UI_CLAIRE_PATH.c_str(), g_TITLE_UI_CHARACTER_MAXFRAME, 3, 13, 128, 128, g_Title_Ui_Claire_image);
    if (g_Title_Ui_Claire_image[0] == -1)
    {
        const std::string  Tmp = g_TITLE_UI_CLAIRE_PATH + g_ERROR_SENTENCE;
        MessageBox(NULL, TEXT(Tmp.c_str()), TEXT("ファイルエラー"), MB_OK | MB_ICONHAND);
        DxLib_End();
    }
}

Title::~Title()
{
}

void Title::Update(Keyboard* Key)
{
 
    /*if (g_Logo_Renderflag)
    {
        m_Logo_Update();
    }*/

    if (m_Title_Renderflag)
    {
        m_Title_Update(Key);
    }
}

void Title::Render(void)
{
    /*if (g_Logo_Renderflag)
    {
        m_Logo_Render();
    }*/

    if (m_Title_Renderflag)
    {
        m_Title_Render();
    }
}

