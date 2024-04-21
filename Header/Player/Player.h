#pragma once
#include "../Global.h"
#include "../Math/Vector2D.h"
class Player
{
private:

	

	//‰æ‘œ‚Ì•\¦À•W
	//float m_X{(g_WIN_WIDTH / 2)  - (130 / 2)};
	//float m_Y{(g_WIN_HEIGHT / 2) - (130 / 2)};

	struct Vector2D<float> Timmy;


public:
	Player(float X, float Y) : Timmy(X,Y) {}
	~Player();
	void Render() const;
};

