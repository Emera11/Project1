#include <Dxlib.h>
#include "./Stage.h"
#include "../../Header/Player/Player.h"


Stage::Stage(float X, float Y, const char* Handle_name)
{
	m_Stage_Data.Handle = LoadGraph(Handle_name);
	m_Stage_Data.X = X;
	m_Stage_Data.Y = Y;
}

Stage::~Stage()
{
}

int Stage::Init()
{
	return 0;
}

void Stage::Hit_Box_Init(int Left, int Right, int Top, int Bottom, s_Hit_Stage_OBJ& Hit_Stage)
{
	Hit_Stage.Hit_Box.left = Left;
	Hit_Stage.Hit_Box.right = Right;
	Hit_Stage.Hit_Box.top = Top;
	Hit_Stage.Hit_Box.bottom = Bottom;
}

void Stage::Hit_Box_Update(s_Hit_Stage_OBJ* Hit_Stage, LONG X, LONG Y)
{
	Hit_Stage->Hit_Box.left  += X;
	Hit_Stage->Hit_Box.right += X;
	//Hit_Stage->Hit_Box.top += Y;
	//Hit_Stage->Hit_Box.bottom += Y;
}

void Stage::Hit_Box_Render(s_Hit_Stage_OBJ Hit_Stage)
{
	DrawBox(Hit_Stage.Hit_Box.left, Hit_Stage.Hit_Box.top, Hit_Stage.Hit_Box.right, Hit_Stage.Hit_Box.bottom, 100, FALSE);
}

void Stage::Floor_Hit_Box_Check(s_Hit_Player_OBJ& Player_Hit_Box, s_Hit_Stage_OBJ& Stage_Hit_Box, struct Vector2D<float>& m_Timmy_Pos,struct Vector2D<float>& m_Timmy_ALL_Pos, bool Jump_flag)
{
	
	if (((Player_Hit_Box.Hit_Box.left > Stage_Hit_Box.Hit_Box.left && Player_Hit_Box.Hit_Box.left < Stage_Hit_Box.Hit_Box.right) ||
		(Stage_Hit_Box.Hit_Box.left  < Player_Hit_Box.Hit_Box.right && Stage_Hit_Box.Hit_Box.right > Player_Hit_Box.Hit_Box.right)) &&
		((Player_Hit_Box.Hit_Box.top > Stage_Hit_Box.Hit_Box.top && Player_Hit_Box.Hit_Box.top < Stage_Hit_Box.Hit_Box.bottom) ||
			(Stage_Hit_Box.Hit_Box.top > Player_Hit_Box.Hit_Box.top && Stage_Hit_Box.Hit_Box.top < Player_Hit_Box.Hit_Box.bottom)))
	{
		
		if (m_Timmy_ALL_Pos.y >= Stage_Hit_Box.Hit_Box.top - 64)
		{
			Stage_Hit_Box.Hit_Check_flag = TRUE;
			Player_Hit_Box.Hit_Box.top = Stage_Hit_Box.Hit_Box.top - 28;
			Player_Hit_Box.Hit_Box.bottom = Stage_Hit_Box.Hit_Box.top + 1;
			m_Timmy_ALL_Pos.y = 0;
			m_Timmy_Pos.y = Stage_Hit_Box.Hit_Box.top - 64;
		}

	}
	else if(!Jump_flag)
	{
		Stage_Hit_Box.Hit_Check_flag = FALSE;
	}
}

void Stage::Step_Hit_Box_Check(s_Hit_Player_OBJ& Player_Hit_Box, s_Hit_Stage_OBJ& Stage_Hit_Box, Vector2D<float>& m_Timmy_Pos, bool Jump_flag)
{
	if (((Player_Hit_Box.Hit_Box.top > Stage_Hit_Box.Hit_Box.top && Player_Hit_Box.Hit_Box.top < Stage_Hit_Box.Hit_Box.bottom) ||
			(Stage_Hit_Box.Hit_Box.top > Player_Hit_Box.Hit_Box.top && Stage_Hit_Box.Hit_Box.top < Player_Hit_Box.Hit_Box.bottom )))
	{

		Stage_Hit_Box.Hit_Check_flag = TRUE;
		Player_Hit_Box.Hit_Box.top = Stage_Hit_Box.Hit_Box.top - 20;
		Player_Hit_Box.Hit_Check_flag = TRUE;
		Player_Hit_Box.Hit_Box.bottom = Stage_Hit_Box.Hit_Box.top + 1;
		m_Timmy_Pos.y = Stage_Hit_Box.Hit_Box.top - 64;
	}
	else if (!Jump_flag)
	{
		Stage_Hit_Box.Hit_Check_flag = FALSE;
	}
}

void Stage::Update()
{
}

void Stage::Render()
{
	DrawRotaGraphF(m_Stage_Data.X, m_Stage_Data.Y, 2.0, 0.0, m_Stage_Data.Handle, TRUE);
	//DrawGraph(m_Stage_Data.X, m_Stage_Data.Y, m_Stage_Data.Handle, TRUE);
}
