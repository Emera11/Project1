#pragma once
#include <windows.h>
#include "../../Header/Math/Vector2D.h"

namespace
{
	typedef struct s_Stage_Information
	{
		float X {0.0f};
		float Y {0.0f};
		int   Handle{0};
	};

	
	
}
typedef struct s_Hit_Player_OBJ;
typedef struct s_Hit_Stage_OBJ
{
	bool  Hit_Check_flag{ false };
	RECT  Hit_Box{ 0 };
};

class Stage
{
private:
	
public:
	s_Stage_Information m_Stage_Data{ 0 };



	

	Stage(float X, float Y, const char* Handle_name);

	~Stage();
	
	int Init();
	void Hit_Box_Init(int Left, int Right, int Top, int Bottom, s_Hit_Stage_OBJ & Hit_Stage);
	void Hit_Box_Update(s_Hit_Stage_OBJ* Hit_Stage, LONG X, LONG Y = 0);
	void Hit_Box_Render(s_Hit_Stage_OBJ  Hit_Stage);
	void Floor_Hit_Box_Check(s_Hit_Player_OBJ& Player_Hit_Box, s_Hit_Stage_OBJ& Stage_Hit_Box, struct Vector2D<float>& m_Timmy_Pos, struct Vector2D<float>& m_Timmy_ALL_Pos, bool Jump_flag);
	void Step_Hit_Box_Check(s_Hit_Player_OBJ& Player_Hit_Box, s_Hit_Stage_OBJ& Stage_Hit_Box, struct Vector2D<float>& m_Timmy_Pos, bool Jump_flag);
	void Update();
	void Render();
	
	

};


