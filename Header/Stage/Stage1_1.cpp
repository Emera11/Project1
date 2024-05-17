#include <DxLib.h>

#include "Stage1_1.h"
#include "../../Header/Global.h"
#include "../../Header/Player/Player.h"

namespace
{
	const char* g_STAGE_NAME = "./Data/Stage/Stage1_1.png";
	const char* g_STAGE_BACKGROUND_NAME = "./Data/Stage/Stage1_BackGround.png";
	constexpr float g_STAGE_X = 2450;
	constexpr float g_STAGE_Y = 30;
	int g_Stage_Background = 0;
	Stage* gp_Stage_OBJ;
	s_Hit_Stage_OBJ g_Floor_Hitbox1{0};
	s_Hit_Stage_OBJ g_Floor_Hitbox2{0};
	s_Hit_Stage_OBJ g_Floor_Hitbox3{0};
}


Stage1_1::Stage1_1()
{
	g_Stage_Background = LoadGraph(g_STAGE_BACKGROUND_NAME);
	gp_Stage_OBJ = new Stage(g_STAGE_X, g_STAGE_Y,g_STAGE_NAME);
	gp_Stage_OBJ->Hit_Box_Init(0, 1580, g_WIN_HEIGHT - 25, g_WIN_HEIGHT, g_Floor_Hitbox1);
	gp_Stage_OBJ->Hit_Box_Init(1750, 2000, g_WIN_HEIGHT - 25, g_WIN_HEIGHT, g_Floor_Hitbox2);
	gp_Stage_OBJ->Hit_Box_Init(-200, -100, g_WIN_HEIGHT - 95, g_WIN_HEIGHT - 35, g_Floor_Hitbox3);
}

void Stage1_1::Update(bool scroll_flag_R, bool scroll_flag_L, bool scroll_flag_Dash, s_Hit_Player_OBJ& Player_HitBox, struct Vector2D<float>& m_Timmy_Pos, struct Vector2D<float>& m_Timmy_ALL_Pos, bool Jump_flag)
{
	if (scroll_flag_Dash)
	{
		if (scroll_flag_R)
		{
			m_Scroll_S_R();
		}

		if (scroll_flag_L)
		{
			m_Scroll_S_L();
		}
	}
	else if (scroll_flag_R)
	{
		m_Scroll_R();
	}

	else if (scroll_flag_L)
	{
		m_Scroll_L();
	}

	
	gp_Stage_OBJ->Floor_Hit_Box_Check(Player_HitBox, g_Floor_Hitbox1, m_Timmy_Pos, m_Timmy_ALL_Pos, Jump_flag);
	gp_Stage_OBJ->Floor_Hit_Box_Check(Player_HitBox, g_Floor_Hitbox2, m_Timmy_Pos, m_Timmy_ALL_Pos, Jump_flag);
	gp_Stage_OBJ->Floor_Hit_Box_Check(Player_HitBox, g_Floor_Hitbox3, m_Timmy_Pos, m_Timmy_ALL_Pos, Jump_flag);


	m_Falling(Player_HitBox, m_Timmy_Pos, m_Timmy_ALL_Pos, g_Floor_Hitbox1);
	m_Falling(Player_HitBox, m_Timmy_Pos, m_Timmy_ALL_Pos, g_Floor_Hitbox2);
	m_Falling(Player_HitBox, m_Timmy_Pos, m_Timmy_ALL_Pos, g_Floor_Hitbox3);
}

void Stage1_1::Render()
{
	DrawGraph(0, 0, g_Stage_Background, TRUE);
	gp_Stage_OBJ->Render();
	gp_Stage_OBJ->Hit_Box_Render(g_Floor_Hitbox1);
	gp_Stage_OBJ->Hit_Box_Render(g_Floor_Hitbox2);
	gp_Stage_OBJ->Hit_Box_Render(g_Floor_Hitbox3);
}

Stage1_1::~Stage1_1()
{
}

void Stage1_1::m_Scroll_R()
{
	gp_Stage_OBJ->m_Stage_Data.X -= 1.0f;
	gp_Stage_OBJ->Hit_Box_Update(&g_Floor_Hitbox1, -1);
	gp_Stage_OBJ->Hit_Box_Update(&g_Floor_Hitbox2, -1);
	gp_Stage_OBJ->Hit_Box_Update(&g_Floor_Hitbox3, -1);
}

void Stage1_1::m_Scroll_L()
{
	gp_Stage_OBJ->m_Stage_Data.X += 1.0f;
	gp_Stage_OBJ->Hit_Box_Update(&g_Floor_Hitbox1, 1);
	gp_Stage_OBJ->Hit_Box_Update(&g_Floor_Hitbox2, 1);
	gp_Stage_OBJ->Hit_Box_Update(&g_Floor_Hitbox3, 1);
}

void Stage1_1::m_Scroll_S_R()
{
	gp_Stage_OBJ->m_Stage_Data.X -= 2.0f;
	gp_Stage_OBJ->Hit_Box_Update(&g_Floor_Hitbox1, -2);
	gp_Stage_OBJ->Hit_Box_Update(&g_Floor_Hitbox2, -2);
	gp_Stage_OBJ->Hit_Box_Update(&g_Floor_Hitbox3, -2);
}

void Stage1_1::m_Scroll_S_L()
{
	gp_Stage_OBJ->m_Stage_Data.X += 2.0f;
	gp_Stage_OBJ->Hit_Box_Update(&g_Floor_Hitbox1, 2);
	gp_Stage_OBJ->Hit_Box_Update(&g_Floor_Hitbox2, 2);
	gp_Stage_OBJ->Hit_Box_Update(&g_Floor_Hitbox3, 2);
}

void Stage1_1::m_Falling(s_Hit_Player_OBJ& Player_HitBox, struct Vector2D<float>& m_Timmy_Pos, struct Vector2D<float>& m_Timmy_ALL_Pos, s_Hit_Stage_OBJ& m_Stage_Hit_Box)
{
	if (!g_Floor_Hitbox1.Hit_Check_flag &&
		!g_Floor_Hitbox2.Hit_Check_flag &&
		!g_Floor_Hitbox3.Hit_Check_flag)
	{
		if (m_Timmy_ALL_Pos.y >= m_Stage_Hit_Box.Hit_Box.top - 64)
		{
			Player_HitBox.Hit_Check_flag = FALSE;
			Player_HitBox.Hit_Box.top += g_G;
			Player_HitBox.Hit_Box.bottom += g_G;
			m_Timmy_Pos.y += g_G;
		}
	}
}
