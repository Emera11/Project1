#include <Dxlib.h>
#include "Stage.h"
#include "Player.h"

namespace
{
	const char* HANDLE_NAME = "./Data/Player/Takao.png";
    // ���͏�Ԃ̏�����
    int g_Input{ 0 };
    int g_EdgeInput{ 0 };
    int g_JumpFlag = FALSE;
    Stage* g_Stage = new Stage();
}


void Player::Key_Init()
{
    // ���͏�Ԃ��X�V
    
    int i;

    // �p�b�h�P�ƃL�[�{�[�h������͂𓾂�
    i = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // �G�b�W����������͂��Z�b�g
    g_EdgeInput = i & ~g_Input;

    // ���͏�Ԃ̕ۑ�
    g_Input = i;
    
}






void Player::PlayerMove()
{

    //Player_Control();

    float Dummy = 0.0f;
    float hsize_X;
    float hsize_Y;

    // �L�����N�^�̍���A�E��A�����A�E�������������蔻��̂���
    // �}�b�v�ɏՓ˂��Ă��邩���ׁA�Փ˂��Ă�����␳����

    // �����̃T�C�Y���Z�o
    hsize_X = m_PLAYER_SIZE_X * 0.5f;
    hsize_Y = m_PLAYER_SIZE_Y * 0.5f;

    // �悸�㉺�ړ����������Ń`�F�b�N
        // �����̃`�F�b�N�A�����u���b�N�̏�ӂɒ����Ă����痎�����~�߂�
        if (g_Stage->MapHitCheck(m_PlX - hsize_X, m_PlY + hsize_Y, &Dummy, &m_MoveY) == 3) m_PlDownSp = 0.0F;

        // �E���̃`�F�b�N�A�����u���b�N�̏�ӂɒ����Ă����痎�����~�߂�
        if (g_Stage->MapHitCheck(m_PlX + hsize_X, m_PlY + hsize_Y, &Dummy, &m_MoveY) == 3) m_PlDownSp = 0.0F;

        // ����̃`�F�b�N�A�����u���b�N�̉��ӂɓ������Ă����痎��������
        if (g_Stage->MapHitCheck(m_PlX - hsize_X, m_PlY - hsize_Y, &Dummy, &m_MoveY) == 4) m_PlDownSp *= -1.0F;

        // �E��̃`�F�b�N�A�����u���b�N�̉��ӂɓ������Ă����痎��������
        if (g_Stage->MapHitCheck(m_PlX + hsize_X, m_PlY - hsize_Y, &Dummy, &m_MoveY) == 4) m_PlDownSp *= -1.0F;

        // �㉺�ړ����������Z
        m_PlY += m_MoveY;

    // ��ɍ��E�ړ����������Ń`�F�b�N
        // �����̃`�F�b�N
        g_Stage->MapHitCheck(m_PlX - hsize_X, m_PlY + hsize_Y, &m_MoveX, &Dummy);

        // �E���̃`�F�b�N
        g_Stage->MapHitCheck(m_PlX + hsize_X, m_PlY + hsize_Y, &m_MoveX, &Dummy);

        // ����̃`�F�b�N
        g_Stage->MapHitCheck(m_PlX - hsize_X, m_PlY - hsize_Y, &m_MoveX, &Dummy);

        // �E��̃`�F�b�N
        g_Stage->MapHitCheck(m_PlX + hsize_X, m_PlY - hsize_Y, &m_MoveX, &Dummy);

        // ���E�ړ����������Z
        m_PlX += m_MoveX;
    


    // �ڒn����
  
        // �L�����N�^�̍����ƉE���̉��ɒn�ʂ����邩���ׂ�
        if (g_Stage->GetChipParam(m_PlX - m_PLAYER_SIZE_X  * 0.5F, m_PlY + m_PLAYER_SIZE_Y * 0.5F + 1.0F) == 0 &&
            g_Stage->GetChipParam(m_PlX + m_PLAYER_SIZE_X * 0.5F, m_PlY + m_PLAYER_SIZE_Y * 0.5F + 1.0F) == 0)
        {
            // ���ꂪ����������W�����v���ɂ���
            g_JumpFlag= TRUE;
           
        }   
        else
        {
            // ���ꂪ�݂�����ڒn���ɂ���
            g_JumpFlag= FALSE;
        }
}

void Player::Player_Control()
{
    Key_Init();
   

    // �ړ��ʂ̏�����
    m_MoveX = 0.0F;
    m_MoveY = 0.0F;

    // ���E�̈ړ�������
    if ((g_Input & PAD_INPUT_LEFT) != 0)  m_MoveX -= m_SPEED;
    if ((g_Input & PAD_INPUT_RIGHT) != 0) m_MoveX += m_SPEED;

    // �n�ɑ��������Ă���ꍇ�̂݃W�����v�{�^��(�{�^���P or �y�L�[)������
    if (g_JumpFlag == FALSE && (g_EdgeInput & PAD_INPUT_A) != 0)
    {
        m_PlDownSp = -m_JUMP_POWER;
        g_JumpFlag= TRUE;
    }

    // ��������
    m_PlDownSp += m_G;

    // �������x���ړ��ʂɉ�����
    m_MoveY = m_PlDownSp;

    PlayerMove();
}

void Player::m_Init()
{
    g_Stage->m_Init();
    m_Handle = LoadGraph(HANDLE_NAME);
}

void Player::m_Update()
{
    Player_Control();
    //PlayerMove();
}

void Player::m_Render()
{
    g_Stage->m_Render();
	DrawGraph(m_PlX, m_PlY, m_Handle, TRUE);
}

Player::Player()
{
    g_JumpFlag= FALSE;
}