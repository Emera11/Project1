#include <DxLib.h>
#include <math.h>
#include "./Header/Global.h"
#include "Header/Game.h"

const char* g_TITLE = "Untitled";
Game* gp_Game;


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    ChangeWindowMode(TRUE);
    SetMainWindowText(g_TITLE);
    SetGraphMode(g_WIN_WIDTH, g_WIN_HEIGHT, 16);
    SetWindowSizeExtendRate(1.5);
    SetWaitVSyncFlag(TRUE); // ������������
    SetUseTransColor(FALSE);
    SetAlwaysRunFlag(TRUE);
    //SetOutApplicationLogValidFlag(FALSE);	// ���O�e�L�X�g�o�͂��Ȃ�
    SetDoubleStartValidFlag(TRUE); 
    SetWindowSizeChangeEnableFlag(TRUE);
    SetMainWindowClassName("NankaSugoiGame");
    SetBackgroundColor(35, 35, 35);
    SetDrawScreen(DX_SCREEN_BACK);
  

    if (DxLib_Init() == -1) { return -1; }

    gp_Game = new Game();
    gp_Game->Init();
 

    while (ProcessMessage() == 0)
    {
     
        ClearDrawScreen();//����ʏ���
        SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�


        gp_Game->Update();
        gp_Game->Draw();



        ScreenFlip();//����ʂ�\��ʂɃR�s�[
        if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) { break; }
        
        
    }


    delete gp_Game;
    gp_Game = 0;
    DxLib_End();
    return 0;
}