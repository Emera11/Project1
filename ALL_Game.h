#pragma once
#include <math.h>
#include "Global.h"
#include "Map.h"
#include "Operation.h"
#include "a_Title.h"
#include "./Header/Keyboard.h"

class ALL_Game
{
private:
	int idx{0};
	Map* MAP{ 0 };
	Operation* OPERATION{0};
	Keyboard* KEY{0};
	a_Title* Title{ 0 };
public:
	ALL_Game()
	{
		MAP = new Map();
		OPERATION = new Operation(16, 16);
		KEY = new Keyboard();
		Title = new a_Title();
	};

	~ALL_Game()
	{
		delete MAP;
		delete OPERATION;
		delete KEY;

		MAP = 0;
		OPERATION = 0;
		KEY = 0;
	}
	void Init();
	void Update();
	void Draw();
};

