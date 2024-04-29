#include "DxLib.h"
#include "Game.h"

namespace
{
    const int SCREEN_WIDTH = 640;                          // 画面の横幅
    const int SCREEN_HEIGHT = 480;                          // 画面の縦幅

    Game* gp_Game = new Game();
    
    // マップデータ
   



    
    int FrameStartTime;        // ６０ＦＰＳ固定用、時間保存用変数

}
int ActMain(void);


// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    ChangeWindowMode(TRUE);

    // ＤＸライブラリの初期化
    if (DxLib_Init() == -1) return -1;

    gp_Game->Init();
    // アクションゲームのメイン関数を呼ぶ
    ActMain();

    // ＤＸライブラリの後始末
    DxLib_End();

    // 終了
    return 0;
}

// アクションサンプルプログラムメイン
int ActMain(void)
{
    // 描画先を裏画面にセット
    SetDrawScreen(DX_SCREEN_BACK);

    // 垂直同期信号を待たない
    SetWaitVSyncFlag(FALSE);

 

    // ６０ＦＰＳ固定用、時間保存用変数を現在のカウント値にセット
    FrameStartTime = GetNowCount();

    // メインループ開始、ＥＳＣキーで外に出る
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // 画面のクリア
        ClearDrawScreen();

        // １/６０秒立つまで待つ
        while (GetNowCount() - FrameStartTime < 1000 / 60) {}

        // 現在のカウント値を保存
        FrameStartTime = GetNowCount();


        gp_Game->Update();
        gp_Game->Draw();

       

        // 画面の更新
        ScreenFlip();
    }

    // 終了
    return 0;
}

