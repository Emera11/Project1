#pragma once
#include "./Global.h"
namespace
{
	
	constexpr unsigned char Map_Chip_Max = 7;
	
}

class Map
{
private:
	
	int m_Map_Chip[Map_Chip_Max]{0};
	int m_Map_BackGraound{0};
	
	void Set_Map();
public:
	unsigned int m_Map_Data[Map_Y][Map_X]{ 0 };
	Map();
	~Map();
	int scroll{ 0 };
	void Init();
	void Update();
	void Render(int Plx, int Ply, int scroll);
};

