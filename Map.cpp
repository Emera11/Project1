#include <random>
#include <Dxlib.h>
#include "Map.h"
#include "Global.h"

void Map::Set_Map()
{

	std::random_device rnd;     // ”ñŒˆ’è“I‚È—”¶¬Ší
	std::mt19937_64 mt(rnd());
	std::uniform_int_distribution<> rand7(0, 6);
	std::uniform_int_distribution<> rand3(0, 2);
	for (int x = 0; x < Map_X; ++x) m_Map_Data[Map_Y - 1][x] = 1;
	int x = 0;
	int y = 8;
	int n = 5;

	do {
		for (int i = 0; i < n; ++i)
		{
			m_Map_Data[y][x] = 2;
			x++;
		}
		y = 2 + rand7(mt);
		n = 2 + rand3(mt);
	} while (x < 140);

	m_Map_Data[8][149] = 6;
}

Map::Map()
{
}

Map::~Map()
{
}

void Map::Init()
{
	Set_Map();
	m_Map_BackGraound = LoadGraph("./Data/test_Data/bg.png");
	m_Map_Chip[1] = LoadGraph("./Data/test_Data/chip1.png");
	m_Map_Chip[2] = LoadGraph("./Data/test_Data/chip2.png");
	m_Map_Chip[3] = LoadGraph("./Data/test_Data/chip3.png");
	m_Map_Chip[4] = LoadGraph("./Data/test_Data/chip4.png");
	m_Map_Chip[5] = LoadGraph("./Data/test_Data/chip5.png");
	m_Map_Chip[6] = LoadGraph("./Data/test_Data/chip6.png");
}

void Map::Update()
{
}

void Map::Render(int Plx, int Ply, int scroll)
{
	int y,x, cx, cy;
	int cl = (scroll / Map_Chip_Size);
	int ofsx = (scroll % Map_Chip_Size);
	DrawGraph(0, 0, m_Map_BackGraound, TRUE);

	for (y = 0; y < Map_Y; ++y)
	{
		for (x = 0; x < Map_X; ++x)
		{
			
			if (m_Map_Data[y][x] == 1)
			{
				DrawGraph((x * Map_Chip_Size) +scroll, (y * Map_Chip_Size), m_Map_Chip[1], TRUE);
			}
			if (m_Map_Data[y][x] == 2)
			{
				DrawGraph((x * Map_Chip_Size) + scroll, (y * Map_Chip_Size), m_Map_Chip[2], TRUE);
			}
		}
	}
	


	/*for (y = 0; y < Map_Y; ++y)
	{
		for (x = 0; x < 16; ++x)
		{
			int c = m_Map_Data[y][x + cl];
			if (c > 0)
			{
				DrawGraph((x*Map_Chip_Size) - ofsx, (y*Map_Chip_Size), m_Map_Chip[c], TRUE);
			}
		}
	}*/

}
