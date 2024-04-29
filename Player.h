#pragma once



class Player
{
private:
	const float m_G = 0.3F;                         // キャラに掛かる重力加速度
	const float m_JUMP_POWER = 9.0F;                         // キャラのジャンプ力
	const float m_SPEED = 5.0F;                         // キャラの移動スピード
	const int   m_PLAYER_SIZE_X = 30;                           // プレイヤーのサイズ
	const int   m_PLAYER_SIZE_Y = 33;                           // プレイヤーのサイズ

	int   m_Handle{0};
	//float m_Pos_X{0.0f};
	//float m_Pos_Y{0.0f};
	float m_MoveX;
	float m_MoveY;
	float m_PlX{320.0f};
	float m_PlY{240.0f};            // プレイヤーの座標(中心座標)
	float m_PlDownSp{0.0f};            // プレイヤーの落下速度
	bool  m_PlJumpFlag{false};           // プレイヤーがジャンプ中か、のフラグ
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