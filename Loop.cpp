#include "Loop.h"
#include <Dxlib.h>

bool Loop::Pad_Read()
{
	m_Pad_Inp = GetJoypadInputState(DX_INPUT_PAD1);

	for (int b = 0; b < e_But::But_Total; ++b)
	{
		if (m_Pad_Inp & (1 << b))
		{
			++m_Pad_Count[b];
		}
		else m_Pad_Count[b] = 0;
	}
	return false;
}

void Loop::Init()
{
	m_Stage = new s_Text * [STAGE_HEIGHT_Num];
	for (int i = 0; i < STAGE_HEIGHT_Num; ++i)
	{
		m_Stage[i] = new s_Text[STAGE_WIDTH_Num];
	}

	for (int x = 0; x < STAGE_WIDTH_Num; ++x)m_Stage[9][x].k = e_Type::e_Ground;
	

	for (int y = 0; y < STAGE_HEIGHT_Num; ++y)
	{
		for (int x = 0; x < STAGE_WIDTH_Num; ++x)
		{
			m_Stage[y][x].x = x;
			m_Stage[y][x].x = y;
		}
	}
} 

void Loop::Update()
{
}

void Loop::Draw()
{
}
