#pragma once



class Player
{
private:
	const float m_G = 0.3F;                         // �L�����Ɋ|����d�͉����x
	const float m_JUMP_POWER = 9.0F;                         // �L�����̃W�����v��
	const float m_SPEED = 5.0F;                         // �L�����̈ړ��X�s�[�h
	const int   m_PLAYER_SIZE_X = 30;                           // �v���C���[�̃T�C�Y
	const int   m_PLAYER_SIZE_Y = 33;                           // �v���C���[�̃T�C�Y

	int   m_Handle{0};
	//float m_Pos_X{0.0f};
	//float m_Pos_Y{0.0f};
	float m_MoveX;
	float m_MoveY;
	float m_PlX{320.0f};
	float m_PlY{240.0f};            // �v���C���[�̍��W(���S���W)
	float m_PlDownSp{0.0f};            // �v���C���[�̗������x
	bool  m_PlJumpFlag{false};           // �v���C���[���W�����v�����A�̃t���O
;





	void PlayerMove();
	void Player_Control();
	
public:
	void Key_Init();
	void m_Init();
	void m_Update();
	void m_Render();

	Player();
	~Player();
};