
#include "../Header/Game.h"
#include "../Header/Player/Player.h"
#include "../Header/Keyboard.h"
#include "../Header/Title/Title.h"
#include "../Header/Stage/Stage1_1.h"

namespace
{
	Player* gp_Player;
	Keyboard* gp_Key;
	Title* gp_Title;
	Stage1_1* gp_Stage1_1;
}

Game::Game()
{
	s_Hit_Player_OBJ Constract = {0};
	Constract.Hit_Box.left = (g_WIN_WIDTH / 2) -94;
	Constract.Hit_Box.top = g_WIN_HEIGHT - 85 - 64;
	Constract.Hit_Box.right = (g_WIN_WIDTH / 2) - 34;
	Constract.Hit_Box.bottom = (g_WIN_HEIGHT - 85) + 64;

	gp_Player = new Player((g_WIN_WIDTH / 2) - (130 / 2), g_WIN_HEIGHT - 85,  Constract);
	gp_Key = new Keyboard();
	gp_Title = new Title();
	gp_Stage1_1 = new Stage1_1;
}

Game::~Game()
{
	/*delete gp_Key;
	delete gp_Player;
	gp_Key = 0;
	gp_Player = 0;*/
}

void Game::Init(void)
{
	
	gp_Player->init();
	gp_Title->init();
}

void Game::Update(void)
{
	gp_Key->KeyUpdate();
	//gp_Title->Update(gp_Key);
	gp_Player->Operation(gp_Key);
	gp_Stage1_1->Update(gp_Player->GetScroll_Flag_R(), gp_Player->GetScroll_Flag_L(),gp_Player->GetScroll_Flag_Dash(), gp_Player->Player_HitBox, gp_Player->m_Timmy_Pos, gp_Player->m_Timmy_ALL_Pos,gp_Player->GetJump_Flag());
}

void Game::Draw(void)
{
	gp_Stage1_1->Render();
	gp_Player->Render();
	//gp_Title->Render();
}
