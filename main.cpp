#include <DxLib.h>
#include <math.h>
#include "./Header/Global.h"
#include "./Loop.h"


const char* g_TITLE = "Untitled";
Loop* gp_Loop = new Loop();

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    ChangeWindowMode(TRUE);
    SetMainWindowText(g_TITLE);
    SetGraphMode(g_WIN_WIDTH, g_WIN_HEIGHT, 16);
    SetWindowSizeExtendRate(1.5);
    SetWaitVSyncFlag(TRUE); // 垂直同期する
    SetUseTransColor(FALSE);
    SetAlwaysRunFlag(TRUE);
    SetOutApplicationLogValidFlag(FALSE);	// ログテキスト出力しない
    SetDoubleStartValidFlag(TRUE); 
    SetWindowSizeChangeEnableFlag(TRUE);
    SetMainWindowClassName("NankaSugoiGame");
    SetBackgroundColor(35, 35, 35);
    SetDrawScreen(DX_SCREEN_BACK);
  

    if (DxLib_Init() == -1) { return -1; }

    
  
    gp_Loop->Init();
    while (ProcessMessage() == 0 && gp_Loop->Pad_Read() == FALSE)
    {
     
        ClearDrawScreen();//裏画面消す
        SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

        gp_Loop->Update();
        gp_Loop->Draw();


        ScreenFlip();//裏画面を表画面にコピー
        
        
    }

    DxLib_End();
    return 0;
}