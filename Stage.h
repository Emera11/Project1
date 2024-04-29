#pragma once
class Stage
{
private:
	int m_Block_1_Handle{0};
	int m_Block_2_Handle{0};
  
	
public:
	void m_Init();
	void m_Render();
	int MapHitCheck(float X, float Y,
		float* MoveX, float* MoveY);
	int GetChipParam(float X, float Y);

	Stage();
	~Stage();
};

