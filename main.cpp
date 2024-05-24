#include <DxLib.h>
#include <math.h>
#include "Global.h"
#include "Map.h"
#include "Operation.h"
#include "./Header/Keyboard.h"

const char* g_TITLE = "Untitled";


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    ChangeWindowMode(TRUE);
    SetMainWindowText(g_TITLE);
    SetGraphMode(g_WIN_WIDTH, g_WIN_HEIGHT, 16);
    SetWindowSizeExtendRate(1.5);
    SetWaitVSyncFlag(TRUE); // 垂直同期する
    SetUseTransColor(FALSE);
    SetAlwaysRunFlag(TRUE);
    //SetOutApplicationLogValidFlag(FALSE);	// ログテキスト出力しない
    SetDoubleStartValidFlag(TRUE); 
    SetWindowSizeChangeEnableFlag(TRUE);
    SetMainWindowClassName("NankaSugoiGame");
    SetBackgroundColor(35, 35, 35);
    SetDrawScreen(DX_SCREEN_BACK);
  

    if (DxLib_Init() == -1) { return -1; }

    Map* MAP = new Map();
    Operation* OPERATION = new Operation(16, 16);
    Keyboard* KEY = new Keyboard();
    MAP->Init();
    OPERATION->Init();
  

    while (ProcessMessage() == 0)
    {
     
        ClearDrawScreen();//裏画面消す
        SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

        KEY->KeyUpdate();
   
        MAP->Update();
        MAP->Render(OPERATION->Plx, OPERATION->Ply, OPERATION->m_Scroll);
        OPERATION->Update(&MAP->scroll, MAP->m_Map_Data, KEY);
        OPERATION->Draw();

        ScreenFlip();//裏画面を表画面にコピー
        if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) { break; }
        
        
    }


    DxLib_End();
    return 0;
}