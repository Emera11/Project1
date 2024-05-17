#pragma once
#include "../../Header/Math/Vector2D.h"
#include "Stage.h"
class Stage1_1
{
public:
	
	Stage1_1();
	void Render();
	void Update(bool scroll_flag_R, bool scroll_flag_L, bool scroll_flag_Dash, s_Hit_Player_OBJ& Player_HitBox, struct Vector2D<float>& m_Timmy_Pos, struct Vector2D<float>& m_Timmy_ALL_Pos, bool Jump_flag);
	~Stage1_1();

private:
	void m_Scroll_R();
	void m_Scroll_L();
	void m_Scroll_S_R();
	void m_Scroll_S_L();
	void m_Falling(s_Hit_Player_OBJ& Player_HitBox, struct Vector2D<float>& m_Timmy_Pos, struct Vector2D<float>& m_Timmy_ALL_Pos, s_Hit_Stage_OBJ& m_Stage_Hit_Box);
};

