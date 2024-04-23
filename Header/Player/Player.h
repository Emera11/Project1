#pragma once
#include "../Global.h"
#include "../Math/Vector2D.h"
class Keyboard;
class Player
{
private:
	
	void End(void);
public:
	Player(float X, float Y) : m_Timmy_Pos(X, Y), m_Glound_y(Y) {}
	~Player();
	void Operation(Keyboard* Key);
	void Render(void) const;
	void init(void);
private:
	//画像の表示座標
	//float m_X{(g_WIN_WIDTH / 2)  - (130 / 2)};
	//float m_Y{(g_WIN_HEIGHT / 2) - (130 / 2)};

	struct Vector2D<float> m_Timmy_Pos;
	int* m_Now_Timmy{ nullptr };
	int m_Now_Timmy_Max_Frame{ 0 };


	//アニメーション再生用変数
	float m_Timmy_PosY_Prev{m_Timmy_Pos.y};
	float m_Jumping_Power{ -1.0f };
	float m_Jumping_Power_weight{ 1.0f };
	float m_X_Move_Speed{ 1.0f };
	float m_Glound_y;

	void m_Frame_Adjust_Check(int Frame_Adjust, int* NowTimmy);
	void m_Anim_Switch_Check(int Anim_Switch, int* NowTimmy, const int MaxFrame);
	void m_XMove_Key(Keyboard* Key);
	void m_Jump_Key(Keyboard* Key);
	void m_Throw_Key(Keyboard* Key);
};

