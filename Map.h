#pragma once
#include "./Global.h"
class Keyboard;
class Operation;

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
	int m_Stage_Num{ 0 };
	unsigned int m_Map_Data[Map_Y][Map_X]{ 0 };
	Map();
	~Map();
	int scroll{ 0 };
	void Init();
	void Update(Keyboard* Key);
	void Render(int Plx, int Ply, int &cx, int& cy);
};

