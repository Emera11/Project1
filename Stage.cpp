#include "Stage.h"
#include <Dxlib.h>

namespace
{
    //�}�b�v�̃T�C�Y
    constexpr int g_MAP_WIDTH = 640;
    constexpr int g_MAP_HEIGHT = 480;
    //�u���b�N�������̃T�C�Y
    constexpr int g_BLOCK_SIZE_X = 30;                           // ��̃`�b�v�̃T�C�Y
    constexpr int g_BLOCK_SIZE_Y = 34;                            // ��̃`�b�v�̃T�C�Y

        //�}�b�v�̃u���b�N�̌�
    constexpr int g_MAP_ONE_BLOCK_NUM_X = (g_MAP_WIDTH  / 32);     // �}�b�v�̉���
    constexpr int g_MAP_ONE_BLOCK_NUM_Y = (g_MAP_HEIGHT / 32);    // �}�b�v�̏c��

    
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


// �}�b�v�Ƃ̓����蔻��( �߂�l 0:������Ȃ�����  1:���ӂɓ�������  2:�E�ӂɓ�������
//                                                3:��ӂɓ�������  4:���ӂɓ�������
// ���ӁFMoveX �� MoveY �A�ǂ������Е����O����Ȃ��Ƃ܂Ƃ��ɓ��삵�܂���(��)
int Stage::MapHitCheck(float X, float Y,
    float* MoveX, float* MoveY)
{
    float afX, afY;

    // �ړ��ʂ𑫂�
    afX = X + *MoveX;
    afY = Y + *MoveY;

    // �����蔻��̂���u���b�N�ɓ������Ă��邩�`�F�b�N
    if (GetChipParam(afX, afY) == 1)
    {
        float blx, bty, brx, bby;

        // �������Ă�����ǂ��痣���������s��

        // �u���b�N�̏㉺���E�̍��W���Z�o
        blx = (float)((int)afX / g_BLOCK_SIZE_X) *     g_BLOCK_SIZE_X;        // ���ӂ� X ���W
        brx = (float)((int)afX / g_BLOCK_SIZE_X + 1) * g_BLOCK_SIZE_X;    // �E�ӂ� X ���W

        bty = (float)((int)afY / g_BLOCK_SIZE_Y)     * g_BLOCK_SIZE_Y;        // ��ӂ� Y ���W
        bby = (float)((int)afY / g_BLOCK_SIZE_Y + 1) * g_BLOCK_SIZE_Y;    // ���ӂ� Y ���W

        // ��ӂɓ������Ă����ꍇ
        if (*MoveY > 0.0F)
        {
            // �ړ��ʂ�␳����
            *MoveY = bty - Y - 1.0F;

            // ��ӂɓ��������ƕԂ�
            return 3;
        }

        // ���ӂɓ������Ă����ꍇ
        if (*MoveY < 0.0F)
        {
            // �ړ��ʂ�␳����
            *MoveY = bby - Y + 1.0F;

            // ���ӂɓ��������ƕԂ�
            return 4;
        }

        // ���ӂɓ������Ă����ꍇ
        if (*MoveX > 0.0F)
        {
            // �ړ��ʂ�␳����
            *MoveX = blx - X - 1.0F;

            // ���ӂɓ��������ƕԂ�
            return 1;
        }

        // �E�ӂɓ������Ă����ꍇ
        if (*MoveX < 0.0F)
        {
            // �ړ��ʂ�␳����
            *MoveX = brx - X + 1.0F;

            // �E�ӂɓ��������ƕԂ�
            return 2;
        }

        // �����ɗ�����K���Ȓl��Ԃ�
        return 4;
    }

    // �ǂ��ɂ�������Ȃ������ƕԂ�
    return 0;
}

// �}�b�v�`�b�v�̒l���擾����֐�
int Stage::GetChipParam(float X, float Y)
{
    int x, y;

    // �����l�֕ϊ�
    x = (int)X / g_BLOCK_SIZE_X;
    y = (int)Y / g_BLOCK_SIZE_Y;

    // �}�b�v����͂ݏo�Ă����� 0 ��Ԃ�
    if (x >= g_MAP_WIDTH || y >= g_MAP_HEIGHT || x < 0 || y < 0) return 0;

    // �w��̍��W�ɊY������}�b�v�̏���Ԃ�
    return g_MapData[y][x];
}

