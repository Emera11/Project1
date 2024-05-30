#include <random>
#include <Dxlib.h>
#include "Map.h"
#include "Global.h"
#include "./Header/Keyboard.h"

namespace
{
	int Old_Stage{ 0 };
	std::random_device rnd;     // 非決定的な乱数生成器
	std::mt19937_64 mt(rnd());
	std::uniform_int_distribution<> rand7(0, 6);
	std::uniform_int_distribution<> rand3(0, 2);
	std::uniform_int_distribution<> rand15(0, 14);
	std::uniform_int_distribution<> rand100(0, 99);
	int x = 0;
	int y = 8;
	int n = 5;
	int i = 0;
}
void Map::Set_Map()
{



	for (y = 0; y < Map_Y; ++y)
	{
		for (x = 0; x < Map_X; ++x)
		{
			m_Map_Data[y][x] = 0;
		}
	}
	
	n = 21 - m_Stage_Num;//最下段の地面の幅
	if (n < 6) n = 6;//最も短くなると6マス
	for (x = 0; x < 150; x++) {//地面を配置する
		if (x % 20 < n) {
			m_Map_Data[9][x] = 1;
			if (m_Stage_Num % 2 == 0 && x > 20 && x % 4 == 0 && rand100(mt) < 5 * m_Stage_Num) m_Map_Data[8][x] = 3;//針
		}
	}

	
	


	


	for (i = 1; i < 9; ++i)
	{
		x = 15 * i + rand15(mt);
		y = 1 * i + rand7(mt);
		m_Map_Data[y][x] = 5;
		m_Map_Data[y-1][x] = 5;
		m_Map_Data[y+1][x] = 5;
		m_Map_Data[y][x-1] = 5;
		m_Map_Data[y][x+1] = 5;

	}
	x = 0;
	y = 8;
	n = 5;
	do {
		for (i = 0; i < n; ++i)
		{
			m_Map_Data[y][x] = 2;
			//if (rand100(mt) < 5) m_Map_Data[y - 1][x] = 4;
			if (x > 20 && x % 3 == 0 && rand100(mt) < 5 * m_Stage_Num) m_Map_Data[y - 1][x] = 4;//食虫植物
			x++;
		}

		y = 2 + rand7(mt);
		n = 2 + rand3(mt);
	} while (x < 140);

	m_Map_Data[8][149] = 6;

	//Old_Stage = m_Stage_Num;
}



Map::Map()
{
	m_Stage_Num = 1;
	Old_Stage = m_Stage_Num;
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

void Map::Update(Keyboard* Key)
{

	if (m_Stage_Num != Old_Stage)
	{
		Set_Map();
	}

	Old_Stage = m_Stage_Num;
}

void Map::Render(int Plx, int Ply, int& cx, int& cy)
{
	int y, x;
	int cl = (scroll / Map_Chip_Size);
	int ofsx = (scroll % Map_Chip_Size);

	DrawGraph(0, 0, m_Map_BackGraound, TRUE);

	/*for (y = 0; y < Map_Y; ++y)
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
	}*/

	for (y = 0; y < 10; ++y)
	{
		for (x = 0; x < 16; ++x)
		{
			int c = m_Map_Data[y][x + cl];
			if (c > 0)
			{
				DrawGraph((x * Map_Chip_Size) - ofsx, (y * Map_Chip_Size), m_Map_Chip[c], TRUE);
			}
		}
	}

	cx = Plx - scroll;
	cy = Ply;

	if (cx < Map_Chip_Size * 5)
	{
		scroll = Plx - (Map_Chip_Size * 5);
		if (scroll < 0) scroll = 0;
	}
	if (cx > Map_Chip_Size * 10)
	{
		scroll = Plx - (Map_Chip_Size * 10);
		if (scroll > Map_Chip_Size * 135) scroll = Map_Chip_Size * 135;
	}




}
