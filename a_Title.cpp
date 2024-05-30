#include <Dxlib.h>
#include "a_Title.h"
#include "./Header/Keyboard.h"

void a_Title::Init()
{
	m_Illust = LoadGraph("./Data/test_Data/mg_illust.png");
	m_Title = LoadGraph("./Data/test_Data/title.png");
}

void a_Title::Update(Keyboard* Key, int& idx)
{
	if (Key->KeyClick(KEY_INPUT_SPACE))
	{
		idx = 1;
	}
}

void a_Title::Draw()
{
	DrawGraph(80, 0, m_Title, TRUE);
	//DrawGraph(0, 0, m_Illust, TRUE);
}
