#include <DxLib.h>
#include "Stage.h"
#include "Stage1_1.h"
#include "../../Header/Global.h"
namespace
{
	const char* g_STAGE_NAME = "./Data/Stage/Stage1_1.png";
	const char* g_STAGE_BACKGROUND_NAME = "./Data/Stage/Stage1_BackGround.png";
	constexpr float g_STAGE_X = 2450;
	constexpr float g_STAGE_Y = 30;
	int g_Stage_Background = 0;
	Stage* gp_Stage_OBJ;
	s_Hit_Stage_OBJ g_Floor_Hitbox1{0};
}


Stage1_1::Stage1_1()
{
	g_Stage_Background = LoadGraph(g_STAGE_BACKGROUND_NAME);
	gp_Stage_OBJ = new Stage(g_STAGE_X, g_STAGE_Y,g_STAGE_NAME);
	gp_Stage_OBJ->Hit_Box_Init(0, 600, g_WIN_HEIGHT - 25, g_WIN_HEIGHT, g_Floor_Hitbox1);
}

void Stage1_1::Update(bool scroll_flag_R, bool scroll_flag_L, bool scroll_flag_Dash)
{
	if (scroll_flag_Dash)
	{
		if (scroll_flag_R)
		{
			gp_Stage_OBJ->m_Stage_Data.X -= 2.0f;
			gp_Stage_OBJ->Hit_Box_Update(&g_Floor_Hitbox1, -2);
		}

		if (scroll_flag_L)
		{
			gp_Stage_OBJ->m_Stage_Data.X += 2.0f;
			gp_Stage_OBJ->Hit_Box_Update(&g_Floor_Hitbox1, 2);
		}
	}
	else if (scroll_flag_R)
	{
		gp_Stage_OBJ->m_Stage_Data.X -= 1.0f;
		gp_Stage_OBJ->Hit_Box_Update(&g_Floor_Hitbox1, -1);
	}

	else if (scroll_flag_L)
	{
		gp_Stage_OBJ->m_Stage_Data.X += 1.0f;
		gp_Stage_OBJ->Hit_Box_Update(&g_Floor_Hitbox1, 1);
	}
}

void Stage1_1::Render()
{
	DrawGraph(0, 0, g_Stage_Background, TRUE);
	gp_Stage_OBJ->Render();
	gp_Stage_OBJ->Hit_Box_Render(g_Floor_Hitbox1);
}

Stage1_1::~Stage1_1()
{
}
