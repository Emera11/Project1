#include "Game.h"
#include "Player.h"

namespace
{
	Player* gp_Player = new Player();
}
void Game::Init()
{
	//gp_Player->Key_Init();
	gp_Player->m_Init();
	
}

void Game::Update()
{
	gp_Player->m_Update();
}

void Game::Draw()
{
	gp_Player->m_Render();
}