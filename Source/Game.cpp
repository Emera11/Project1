#include "../Header/Game.h"
#include "../Header/Player/Player.h"
#include "../Header/Keyboard.h"
#include "../Header/Title/Title.h"

namespace
{
	Player* gp_Player;
	Keyboard* gp_Key;
	Title* gp_Title;
}

Game::Game()
{
	gp_Player = new Player((g_WIN_WIDTH / 2) - (130 / 2), (g_WIN_HEIGHT / 2) - (130 / 2));
	gp_Key = new Keyboard();
	gp_Title = new Title();
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
}

void Game::Draw(void)
{
	gp_Player->Render();
	//gp_Title->Render();
}
