#pragma once
namespace
{
	int STAGE_TOTAL_Num =  3600;
	int STAGE_WIDTH_Num =  160;
	int STAGE_HEIGHT_Num = 18;

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
}



class Loop
{
private:
	int m_Pad_Inp{ 0 };
	int m_Pad_Count[e_But::But_Total];
	s_Text** m_Stage{0};
public:
	void Init();
	void Update();
	void Draw();
	bool Pad_Read();
};

