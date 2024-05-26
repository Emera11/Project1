#pragma once
namespace
{
	int STAGE_TOTAL_Num =  1600;
	int STAGE_WIDTH_Num =  160;
	int STAGE_HEIGHT_Num = 10;
	constexpr int MAP_CHIP_SIZE = 36;
	constexpr int Move_X = 5;
	constexpr int Move_Max_Y = 150;

	struct Color
	{
		unsigned int r;
		unsigned int g;
		unsigned int b;
	};

	enum e_But
	{
		But_Down,
		But_Left,
		But_Right,
		But_Up,
		But_A,
		But_B,
		But_X,
		But_Y,
		But_L,
		But_R,
		But_Select,
		But_Start,
		But_L3,
		But_R3,
		But_Total
	};

	enum e_Type
	{
		e_Empty = 0,
		e_Ground,
		e_Block,
		e_Thorn,
		e_Enemy1,
		e_Coin,
		e_Goal,
		e_Player
	};

	struct  s_Image
	{
		int Handle;
		int Width;
		int Height;
	};

	enum e_Ani
	{
		e_Normal,
		e_Walk1,
		e_Walk2,
		e_Jump,
		e_End,
		e_Ani_Total
	};

	struct  s_Rect
	{
		int x;
		int y;
		int Width;
		int Height;
		int k;
		bool d;
		double r;
		s_Image Handle[e_Ani::e_Ani_Total];
		int Animation;
		int JumpCount;
		bool Character_Check;
	};

	struct s_Text
	{
		int k;
		int x;
		int y;
	};

	enum e_Jump
	{
		e_Land,
		e_Jumping,
		e_Fall
	};

}



class Loop
{
private:
	int m_Pad_Inp{ 0 };
	int m_Pad_Count[e_But::But_Total];
	int m_Camera_x{ 0 };
	int m_Player_x{ 0 };
	int m_Plyer_i{ 0 };
	int Jump_State{ 0 };
	int Jump_Ymem{ 0 };
	int Animation_Count{ 0 };
	s_Text** m_Stage{0};
	s_Rect* m_Block{ 0 };
	s_Rect* m_Player{ 0 };
	void Player_Copy();
	bool HitJudg(s_Rect c, int i_c, bool d);
	void Block_Init(s_Rect* m_rect);


public:
	void Init();
	void Update();
	void Draw();
	bool Pad_Read();
};

