#include "ALL_Game.h"

void ALL_Game::Init()
{
	MAP->Init();
	OPERATION->Init();
	Title->Init();
}

void ALL_Game::Update()
{

    KEY->KeyUpdate();

	switch (idx)
	{
	case 0:
		Title->Update(KEY, idx);
		break;
	case 1:
		MAP->Update(KEY);
		OPERATION->Update(&MAP->scroll, MAP->m_Map_Data, KEY, MAP->m_Stage_Num);
		break;
	default:
		break;
	}
  

}

void ALL_Game::Draw()
{
	switch (idx)
	{
	case 0:
		Title->Draw();
		break;
	case 1:
		MAP->Render(OPERATION->Plx, OPERATION->Ply, OPERATION->cx, OPERATION->cy);
		OPERATION->Draw();
		break;
	default:
		break;
	}

}
