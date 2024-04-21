#include <DxLib.h>
#include <math.h>
#include "./Header/Global.h"



const int JUMP_COUNT_MAX = 30;
// �萔
const double  G = 9.8067;
const double  Y_MAX = 2.000;

const char* g_TITLE = "Untitled";


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


    // �؂�o���n�_��X���W
    int animOffsetX = 0;

    // �W�����v

    bool CanJump = TRUE;


    //int Adjust_CenterY = 480;

    float Adjust_SpeedY = 0.0f;



    //�摜�̕����ǂݍ���
    const int Walk_MaxFrame = 38;
    int Walk_image[Walk_MaxFrame];

    const int Idle_MaxFrame = 145;
    int Idle_image[Idle_MaxFrame];

    const int Jump_MaxFrame = 30;
    int Jump_image[Jump_MaxFrame];

    const int Run_MaxFrame = 24;
    int Run_image[Run_MaxFrame];

    const int Throw_MaxFrame = 52;
    int Throw_image[Throw_MaxFrame];

    int* Now_Timmy = nullptr;
    const int* Now_Timmy_Max_Frame = nullptr;

    Now_Timmy = Idle_image;
    Now_Timmy_Max_Frame = &Idle_MaxFrame;

    LoadDivGraph(TIMMY_WALK_PATH, Walk_MaxFrame, 2, 19, 64, 64, Walk_image);
    LoadDivGraph(TIMMY_IDLE_PATH, Idle_MaxFrame, Idle_MaxFrame, 1, 64, 64, Idle_image);
    LoadDivGraph(TIMMY_JUMP_PATH, Jump_MaxFrame, 2, 15, 64, 64, Jump_image);
    LoadDivGraph(TIMMY_RUN_PATH, Run_MaxFrame, 4, 6, 64, 64, Run_image);
    LoadDivGraph(TIMMY_THROW_PATH, Throw_MaxFrame, 4, 13, 64, 64, Throw_image);


    //�A�j���[�V�����Đ��p�ϐ�
    int Frame = 0;
    int Frame_adjust = 0;

    int Anim_switch = 0;
    bool Reverse = FALSE;
    bool Throw_flag = FALSE;
    float Adjust_CenterY_Prev = Adjust_CenterY;
    float F = -1.0f;
    while (ProcessMessage() == 0)
    {
     

        if (Frame_adjust == 3 &&  Now_Timmy == Idle_image) {
            Frame++;
            Frame_adjust = 0;
        }

        if (Frame_adjust == 3 &&  Now_Timmy == Walk_image) {
            Frame++;
            Frame_adjust = 0;
        }

        if (Frame_adjust == 3 &&  Now_Timmy == Jump_image) {
            Frame++;
            Frame_adjust = 0;
        }

        if (Frame_adjust == 3 && Now_Timmy == Run_image) {
            Frame++;
            Frame_adjust = 0;
        }

        if (Frame_adjust == 3 && Now_Timmy == Throw_image) {
            Frame++;
            Frame_adjust = 0;
        }



        // �E�L�[�������Ă���Ƃ� + Shift
        if ( CheckHitKey(KEY_INPUT_LSHIFT)&& CheckHitKey(KEY_INPUT_RIGHT)) {

            Reverse = FALSE;
            Throw_flag = FALSE;
            if (Anim_switch != 3)
            {
                Frame = 0;
                Anim_switch = 3;
                Frame_adjust = 0;

            }

            if (Frame == Run_MaxFrame - 1)
            {
                Frame = 0;
            }

            // �v���C���[���E�Ɉړ�������
            Adjust_CenterX += 2.0f;


        }



        // ���L�[�������Ă���Ƃ� + Shift
        else if ( CheckHitKey(KEY_INPUT_LSHIFT)&& CheckHitKey(KEY_INPUT_LEFT)) {

            Reverse = TRUE;
            Throw_flag = FALSE;
            if (Anim_switch != 3)
            {
                Frame = 0;
                Anim_switch = 3;
                Frame_adjust = 0;

            }

            if (Frame == Run_MaxFrame - 1)
            {
                Frame = 0;
            }

            // �v���C���[���E�Ɉړ�������
            Adjust_CenterX -= 2.0f;


        }

        // ���L�[�ō��Ɉړ�
        else if (CheckHitKey(KEY_INPUT_LEFT)) {
            Reverse = TRUE;
            Throw_flag = FALSE;
            if (Anim_switch != 1)
            {
                Frame = 0;
                Anim_switch = 1;
                Frame_adjust = 0;
            }

            if (Frame == Walk_MaxFrame - 1)
            {
                Frame = 0;
            }
            Adjust_CenterX -= 1.0f;
        }





        // �E�L�[�������Ă���Ƃ�
        else if (CheckHitKey(KEY_INPUT_RIGHT)) {

            Reverse = FALSE;
            Throw_flag = FALSE;
            if (Anim_switch != 1)
            {
                Frame = 0;
                Anim_switch = 1;
                Frame_adjust = 0;
                
            }

            if (Frame == Walk_MaxFrame - 1)
            {
                Frame = 0;
            }

            // �v���C���[���E�Ɉړ�������
            Adjust_CenterX += 1.0f;
     
     
        }
        // ���L�[�ō��Ɉړ�
        else if (CheckHitKey(KEY_INPUT_LEFT)) {
            Reverse = TRUE;
            Throw_flag = FALSE;
            if (Anim_switch != 1)
            {
                Frame = 0;
                Anim_switch = 1;
                Frame_adjust = 0;
            }

            if (Frame == Walk_MaxFrame - 1)
            {
                Frame = 0;
            }
            Adjust_CenterX -= 1.0f;
        }

        // ���L�[�ō��Ɉړ�
        else if (CheckHitKey(KEY_INPUT_Z)) {
 
            Throw_flag = TRUE;
            if (Anim_switch != 4)
            {
                Frame = 0;
                Anim_switch = 4;
                Frame_adjust = 0;
            }

            else if (Frame == Throw_MaxFrame - 1)
            {
                Frame = 0;
            }
        }

        else if (Throw_flag)
        {
            if (Anim_switch != 4)
            {
                Frame = 0;
                Anim_switch = 4;
                Frame_adjust = 0;
            }

            else if (Frame == Throw_MaxFrame - 1)
            {
                Frame = 0;
                Throw_flag = FALSE;
            }
        }
       


        // �X�y�[�X�L�[�ŃW�����v

        else if (CheckHitKey(KEY_INPUT_SPACE))
        {

            Throw_flag = FALSE;
            if (CanJump)
            {
                F = -10.0;
                CanJump = FALSE;
            }
        }

        else if (!CanJump && Adjust_CenterY <= (WIN_HEIGHT / 2) - (130 / 2))
        {
            if (Anim_switch != 2)
            {
                Frame = 0;
                Anim_switch = 2;
                Frame_adjust = 0;
            }

            if (Frame == Jump_MaxFrame - 1)
            {
                Frame = 0;
            }

        }
  
        else
        {
            if (Anim_switch != 0)
            {
                Frame = 0;
                Anim_switch = 0;
                Frame_adjust = 0;
            }

            if (Frame == Idle_MaxFrame - 1)
            {
                Frame = 0;
            }
            Anim_switch = 0;
        }
        Frame_adjust++;

        

        if (Anim_switch == 0 &&  Now_Timmy != Idle_image)
        {
             Now_Timmy = Idle_image;
             Now_Timmy_Max_Frame = &Idle_MaxFrame;
        }
        else if (Anim_switch == 1 &&  Now_Timmy != Walk_image)
        {
             Now_Timmy = Walk_image;
             Now_Timmy_Max_Frame = &Walk_MaxFrame;
        }
        else if (Anim_switch == 2 &&  Now_Timmy != Jump_image)
        {
             Now_Timmy = Jump_image;
             Now_Timmy_Max_Frame = &Jump_MaxFrame;
        }

       
        else if (Anim_switch == 3 && Now_Timmy != Run_image)
        {
            Now_Timmy = Run_image;
            Now_Timmy_Max_Frame = &Run_MaxFrame;
        }

        else if (Anim_switch == 4 && Now_Timmy != Throw_image)
        {
            Now_Timmy = Throw_image;
            Now_Timmy_Max_Frame = &Throw_MaxFrame;
        }

       
        if (!CanJump)
        {

            float y_tmp = Adjust_CenterY;
            Adjust_CenterY += (Adjust_CenterY - Adjust_CenterY_Prev) + F;
            Adjust_CenterY_Prev = y_tmp;
            F = 0.3f;

        }

       



        if (Adjust_CenterY >= (WIN_HEIGHT / 2) - (130 / 2))
        {
            CanJump = TRUE;
        }


        ClearDrawScreen();//����ʏ���
        SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�


       

   
       //�摜�̕\��
        //DrawReverseGraph(Adjust_CenterX, Adjust_CenterY,  Now_Timmy[Frame], true, Reverse, FALSE);
        DrawRotaGraphF(Adjust_CenterX, Adjust_CenterY, 2.0, 0.0, Now_Timmy[Frame],TRUE, Reverse, FALSE);
      
        //Jump_flag = 0;                              // ��ʊO�ɗ���ƁA��яオ��t���O��߂�
        //�摜�̕\��
 
        

       



        ScreenFlip();//����ʂ�\��ʂɃR�s�[
        if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) { break; }
        
        
    }


    DxLib_End();
    return 0;
}