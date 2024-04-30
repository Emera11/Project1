#include "DxLib.h"
int G = 9.8f;


void Box_HitCheck(float Box_PlayerX1, float Box_PlayerY1, float Box_PlayerX2, float Box_PlayerY2,
    float Box_StageX1, float Box_StageY1, float Box_StageX2, float Box_StageY2, int& hit_Flag);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    

    if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
    {
        return -1;    // エラーが起きたら直ちに終了
    }






    // 描画先を裏画面にセット
    SetDrawScreen(DX_SCREEN_BACK);

    // 垂直同期信号を待たない
    SetWaitVSyncFlag(FALSE);

    // プレイヤーの座標を初期化
    float PlX = 320.0F;        float PlY = 300.0F;

    // プレイヤーの落下速度を初期化
    int PlDownSp = 0.0F;

    // ジャンプ中フラグを倒す
    int PlJumpFlag = FALSE;

    // 入力状態の初期化
    int Input = 0;
    int EdgeInput = 0;
    
    // ６０ＦＰＳ固定用、時間保存用変数を現在のタイムカウントにセット
    int FrameStartTime = GetNowCount();
    int GraphHandle;
    int BackHandle;
    // マスクデータをロードします
    GraphHandle = LoadGraph("man.png");
    BackHandle = LoadGraph("a.png");



    float BoxX1 = 200.0f;
    float BoxX2 = 400.0f;
    float BoxY1 = 450.0f;
    float BoxY2 = 650.0f;
    int   Hit_Flag = FALSE;
    float a_BoxX1 = 400.0f;
    float a_BoxX2 = 600.0f;
    float a_BoxY1 = 460.0f;
    float a_BoxY2 = 650.0f;
    int   a_Hit_Flag = FALSE;
    // メインループ開始、ＥＳＣキーで外に出る
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // 画面のクリア
        ClsDrawScreen();

        // １/６０秒立つまで待つ
        while (GetNowCount() - FrameStartTime < 1000 / 60) { Sleep(1); }

        // 現在のタイムカウントを保存
        FrameStartTime = GetNowCount();

        // 入力状態を更新
        {
            int i;

            // パッド１とキーボードから入力を得る
            i = GetJoypadInputState(DX_INPUT_KEY_PAD1);

            // エッジを取った入力をセット
            EdgeInput = i & ~Input;

            // 入力状態の保存
            Input = i;
        }

        // プレイヤーの移動処理
        {
            float MoveX, MoveY;
            PlY += G;

            // 左右の移動を見る
            if ((Input & PAD_INPUT_LEFT) != 0)  PlX -= 1.5f;
            else if ((Input & PAD_INPUT_RIGHT) != 0) PlX += 1.5f;


          

         

            // ロードしたマスクデータを画面の左上に描画します
            //DrawMask(0, 0, MaskHandle, DX_MASKTRANS_NONE);
         
            Box_HitCheck(PlX, PlY + 120, PlX + 35, PlY + 120 + 1, BoxX1, BoxY1, BoxX2, BoxY2, Hit_Flag);
            Box_HitCheck(PlX, PlY + 120, PlX + 35, PlY + 120 + 1, a_BoxX1, a_BoxY1, a_BoxX2, a_BoxY2, a_Hit_Flag);


            if (Hit_Flag)
            {
                G = 0.0f;
                PlY = BoxY1-120;
            }
            else if (a_Hit_Flag)
            {
                G = 0.0f;
                PlY = a_BoxY1-120;
            }
            else
                G = 9.8f;

            DrawGraph(0, 0, BackHandle, TRUE);
            DrawGraphF(PlX, PlY, GraphHandle, TRUE);
            DrawBox(PlX, PlY+120, PlX + 35, PlY +120 +1, 255, FALSE);
            DrawBox(BoxX1, BoxY1, BoxX2, BoxY2, 100, FALSE);
            DrawBox(a_BoxX1, a_BoxY1, a_BoxX2, a_BoxY2, 100, FALSE);
            // 画面いっぱいに赤い四角を描きます
        
        }
        // 画面の更新
        ScreenFlip();
    }
    DxLib_End();        // ＤＸライブラリ使用の終了処理

    return 0;        // ソフトの終了
}



void Box_HitCheck(float Box_PlayerX1, float Box_PlayerY1, float Box_PlayerX2, float Box_PlayerY2,
                  float Box_StageX1, float Box_StageY1, float Box_StageX2, float Box_StageY2, int& hit_Flag)
{
    if (((Box_PlayerX1 > Box_StageX1 && Box_PlayerX1 < Box_StageX2) ||
        (Box_StageX1 < Box_PlayerX2 && Box_StageX2 > Box_PlayerX2)) &&
        ((Box_PlayerY1 > Box_StageY1 && Box_PlayerY1 < Box_StageY2) ||
        (Box_StageY1 > Box_PlayerY1 && Box_StageY1 < Box_PlayerY2)))
    {        
       
        hit_Flag = TRUE;
    }
    else
    {
        hit_Flag = FALSE;
    }
}