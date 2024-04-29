#include "Stage.h"
#include <Dxlib.h>

namespace
{
    //マップのサイズ
    constexpr int g_MAP_WIDTH = 640;
    constexpr int g_MAP_HEIGHT = 480;
    //ブロック一個あたりのサイズ
    constexpr int g_BLOCK_SIZE_X = 30;                           // 一つのチップのサイズ
    constexpr int g_BLOCK_SIZE_Y = 34;                            // 一つのチップのサイズ

        //マップのブロックの個数
    constexpr int g_MAP_ONE_BLOCK_NUM_X = (g_MAP_WIDTH  / 32);     // マップの横幅
    constexpr int g_MAP_ONE_BLOCK_NUM_Y = (g_MAP_HEIGHT / 32);    // マップの縦幅

    
    char g_MapData[g_MAP_ONE_BLOCK_NUM_Y][g_MAP_ONE_BLOCK_NUM_X] =
    {
      0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
      1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
      1,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
      1,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,1,
      1,0,0,1,1, 1,1,0,0,0, 0,0,0,0,0, 0,0,1,0,1,

      1,0,0,0,0, 0,0,0,1,1, 0,0,0,0,0, 0,0,1,0,1,
      1,0,0,0,0, 0,0,0,0,0, 0,0,1,1,0, 0,0,1,0,1,
      1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,1,
      1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
      1,0,0,0,0, 0,0,1,1,0, 0,0,0,0,0, 1,0,0,0,1,

      1,0,0,0,0, 1,1,1,1,1, 0,0,0,0,1, 1,0,0,0,1,
      1,0,0,0,0, 1,1,1,1,1, 0,0,0,1,1, 1,0,0,0,1,
      1,0,0,0,0, 0,0,0,0,0, 0,0,0,1,1, 1,0,0,0,1,
      1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
      1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
    };

    const char* BLOCK1_HANDLE_NAME = "./Data/Stage/Matiko.png";
}

void Stage::m_Init()
{
    m_Block_1_Handle = LoadGraph(BLOCK1_HANDLE_NAME);
}

void Stage::m_Render()
{
    const int* Now_Block = &m_Block_1_Handle;


    for (int y = 0; y < g_MAP_ONE_BLOCK_NUM_Y; ++y)
    {
        for (int x = 0; x < g_MAP_ONE_BLOCK_NUM_X; ++x)
        {
            if(g_MapData[y][x] == 1)
            {
                DrawGraph(x * 32, y * 33, m_Block_1_Handle, TRUE);
            }
         
        }
    }
}

Stage::Stage()
{
   

}


Stage::~Stage()
{
}


// マップとの当たり判定( 戻り値 0:当たらなかった  1:左辺に当たった  2:右辺に当たった
//                                                3:上辺に当たった  4:下辺に当たった
// 注意：MoveX と MoveY 、どっちか片方が０じゃないとまともに動作しません(爆)
int Stage::MapHitCheck(float X, float Y,
    float* MoveX, float* MoveY)
{
    float afX, afY;

    // 移動量を足す
    afX = X + *MoveX;
    afY = Y + *MoveY;

    // 当たり判定のあるブロックに当たっているかチェック
    if (GetChipParam(afX, afY) == 1)
    {
        float blx, bty, brx, bby;

        // 当たっていたら壁から離す処理を行う

        // ブロックの上下左右の座標を算出
        blx = (float)((int)afX / g_BLOCK_SIZE_X) *     g_BLOCK_SIZE_X;        // 左辺の X 座標
        brx = (float)((int)afX / g_BLOCK_SIZE_X + 1) * g_BLOCK_SIZE_X;    // 右辺の X 座標

        bty = (float)((int)afY / g_BLOCK_SIZE_Y)     * g_BLOCK_SIZE_Y;        // 上辺の Y 座標
        bby = (float)((int)afY / g_BLOCK_SIZE_Y + 1) * g_BLOCK_SIZE_Y;    // 下辺の Y 座標

        // 上辺に当たっていた場合
        if (*MoveY > 0.0F)
        {
            // 移動量を補正する
            *MoveY = bty - Y - 1.0F;

            // 上辺に当たったと返す
            return 3;
        }

        // 下辺に当たっていた場合
        if (*MoveY < 0.0F)
        {
            // 移動量を補正する
            *MoveY = bby - Y + 1.0F;

            // 下辺に当たったと返す
            return 4;
        }

        // 左辺に当たっていた場合
        if (*MoveX > 0.0F)
        {
            // 移動量を補正する
            *MoveX = blx - X - 1.0F;

            // 左辺に当たったと返す
            return 1;
        }

        // 右辺に当たっていた場合
        if (*MoveX < 0.0F)
        {
            // 移動量を補正する
            *MoveX = brx - X + 1.0F;

            // 右辺に当たったと返す
            return 2;
        }

        // ここに来たら適当な値を返す
        return 4;
    }

    // どこにも当たらなかったと返す
    return 0;
}

// マップチップの値を取得する関数
int Stage::GetChipParam(float X, float Y)
{
    int x, y;

    // 整数値へ変換
    x = (int)X / g_BLOCK_SIZE_X;
    y = (int)Y / g_BLOCK_SIZE_Y;

    // マップからはみ出ていたら 0 を返す
    if (x >= g_MAP_WIDTH || y >= g_MAP_HEIGHT || x < 0 || y < 0) return 0;

    // 指定の座標に該当するマップの情報を返す
    return g_MapData[y][x];
}

