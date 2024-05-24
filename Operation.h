#pragma once
#include "./Global.h"
class Keyboard;

class Operation
{
private:
	bool  plDir{0}; //Œü‚«‚ğŠÇ—
	float  JumpFrame{ 0.0f };
	int plAni{ 0 };
	float anim_Sleep{ 0.0f };
	int MG_ANIMA[8]{ 0, 0, 1,1, 0, 0, 2,2 };

	double Plxp{ 0.0f };
	double Plyp{ 0.0f };
	int plJump{ 2 };
	int CXP[4]{ 1, 35, 1, 35 };
	int CYP[4]{ 1, 1, 35, 35 };
	int m_Player_Data[3]{ 0 };
	int m_Player_Data_L[3]{ 0 };
	bool chkWall(int cx, int cy, unsigned int m_Map_Data[Map_Y][Map_X]);
public:
	int Plx{ 0 };
	int Ply{ 0 };
	int m_Scroll{ 0 };
	Operation(int x, int y) :Plx(x), Ply(y) {
	
	};
	void Init();
	void Update(int* Scroll, unsigned int m_Map_Data[Map_Y][Map_X], Keyboard* Key);
	void Draw();
};

