#include "DxLib.h"
#include "Game.h"

namespace
{
    const int SCREEN_WIDTH = 640;                          // ��ʂ̉���
    const int SCREEN_HEIGHT = 480;                          // ��ʂ̏c��

    Game* gp_Game = new Game();
    
    // �}�b�v�f�[�^
   



    
    int FrameStartTime;        // �U�O�e�o�r�Œ�p�A���ԕۑ��p�ϐ�

}
int ActMain(void);


// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    ChangeWindowMode(TRUE);

    // �c�w���C�u�����̏�����
    if (DxLib_Init() == -1) return -1;

    gp_Game->Init();
    // �A�N�V�����Q�[���̃��C���֐����Ă�
    ActMain();

    // �c�w���C�u�����̌�n��
    DxLib_End();

    // �I��
    return 0;
}

// �A�N�V�����T���v���v���O�������C��
int ActMain(void)
{
    // �`���𗠉�ʂɃZ�b�g
    SetDrawScreen(DX_SCREEN_BACK);

    // ���������M����҂��Ȃ�
    SetWaitVSyncFlag(FALSE);

 

    // �U�O�e�o�r�Œ�p�A���ԕۑ��p�ϐ������݂̃J�E���g�l�ɃZ�b�g
    FrameStartTime = GetNowCount();

    // ���C�����[�v�J�n�A�d�r�b�L�[�ŊO�ɏo��
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // ��ʂ̃N���A
        ClearDrawScreen();

        // �P/�U�O�b���܂ő҂�
        while (GetNowCount() - FrameStartTime < 1000 / 60) {}

        // ���݂̃J�E���g�l��ۑ�
        FrameStartTime = GetNowCount();


        gp_Game->Update();
        gp_Game->Draw();

       

        // ��ʂ̍X�V
        ScreenFlip();
    }

    // �I��
    return 0;
}

