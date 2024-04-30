#include "DxLib.h"
int G = 9.8f;


void Box_HitCheck(float Box_PlayerX1, float Box_PlayerY1, float Box_PlayerX2, float Box_PlayerY2,
    float Box_StageX1, float Box_StageY1, float Box_StageX2, float Box_StageY2, int& hit_Flag);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    

    if (DxLib_Init() == -1)    // �c�w���C�u��������������
    {
        return -1;    // �G���[���N�����璼���ɏI��
    }






    // �`���𗠉�ʂɃZ�b�g
    SetDrawScreen(DX_SCREEN_BACK);

    // ���������M����҂��Ȃ�
    SetWaitVSyncFlag(FALSE);

    // �v���C���[�̍��W��������
    float PlX = 320.0F;        float PlY = 300.0F;

    // �v���C���[�̗������x��������
    int PlDownSp = 0.0F;

    // �W�����v���t���O��|��
    int PlJumpFlag = FALSE;

    // ���͏�Ԃ̏�����
    int Input = 0;
    int EdgeInput = 0;
    
    // �U�O�e�o�r�Œ�p�A���ԕۑ��p�ϐ������݂̃^�C���J�E���g�ɃZ�b�g
    int FrameStartTime = GetNowCount();
    int GraphHandle;
    int BackHandle;
    // �}�X�N�f�[�^�����[�h���܂�
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
    // ���C�����[�v�J�n�A�d�r�b�L�[�ŊO�ɏo��
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // ��ʂ̃N���A
        ClsDrawScreen();

        // �P/�U�O�b���܂ő҂�
        while (GetNowCount() - FrameStartTime < 1000 / 60) { Sleep(1); }

        // ���݂̃^�C���J�E���g��ۑ�
        FrameStartTime = GetNowCount();

        // ���͏�Ԃ��X�V
        {
            int i;

            // �p�b�h�P�ƃL�[�{�[�h������͂𓾂�
            i = GetJoypadInputState(DX_INPUT_KEY_PAD1);

            // �G�b�W����������͂��Z�b�g
            EdgeInput = i & ~Input;

            // ���͏�Ԃ̕ۑ�
            Input = i;
        }

        // �v���C���[�̈ړ�����
        {
            float MoveX, MoveY;
            PlY += G;

            // ���E�̈ړ�������
            if ((Input & PAD_INPUT_LEFT) != 0)  PlX -= 1.5f;
            else if ((Input & PAD_INPUT_RIGHT) != 0) PlX += 1.5f;


          

         

            // ���[�h�����}�X�N�f�[�^����ʂ̍���ɕ`�悵�܂�
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
            // ��ʂ����ς��ɐԂ��l�p��`���܂�
        
        }
        // ��ʂ̍X�V
        ScreenFlip();
    }
    DxLib_End();        // �c�w���C�u�����g�p�̏I������

    return 0;        // �\�t�g�̏I��
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