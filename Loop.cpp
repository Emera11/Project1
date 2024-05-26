#include <Dxlib.h>
#include <random>
#include "Loop.h"
#include "./Header/Global.h"
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

void Loop::Player_Copy()
{
	for (int i = 0; i < STAGE_TOTAL_Num; ++i)
	{
		if (m_Block[i].k == e_Type::e_Player)
		{
			//マリオをコピー
			m_Player = &m_Block[i];

			m_Player_x = m_Block->x;

			m_Plyer_i = i;

			break;
		}
	}
}

bool Loop::HitJudg(s_Rect c, int i_c, bool d)
{
	for (int i = 0; i < STAGE_TOTAL_Num; ++i)
	{
		if (i != i_c)
		{
			if (((m_Block[i].x <= c.x &&
				c.x < m_Block[i].x + m_Block[i].Width) ||

				(m_Block[i].x <= c.x + c.Width &&
					c.x + c.Width < m_Block[i].x + m_Block[i].Width)) &&

				((m_Block[i].y <= c.y &&
					c.y < m_Block[i].y + m_Block[i].Height) ||

					(m_Block[i].y <= c.y + c.Height &&
						c.y + c.Height < m_Block[i].y + m_Block[i].Height)))
			{
				//マリオが敵キャラと接触した場合
				if ((c.k == e_Type::e_Player || m_Block[i].k == e_Type::e_Player)
					&& c.Character_Check == true &&
					m_Block[i].Character_Check == true)
				{
					switch (d)
					{
					case false:
						break;

					case true:
							Block_Init(&m_Block[i]);
					default:
						break;
					}

				}
				//ゴールに接触した場合
				else if (c.k == e_Type::e_Player &&
					m_Block[i].k == e_Type::e_Goal)
				{

				}
					return true;
			}
		}
	}
	return false;
}

void Loop::Block_Init(s_Rect* m_rect)
{
	m_rect->x = 0;
	m_rect->y = 0;
	m_rect->Width = 0;
	m_rect->Height = 0;
	m_rect->Height = e_Type::e_Empty;
	m_rect->k = 0;
	m_rect->r = 0;

	for (int i = 0; i < e_Ani::e_Ani_Total; ++i) {
		m_rect->Handle[i].Handle = 0;
		m_rect->Handle[i].Width = 0;
		m_rect->Handle[i].Height = 0;
	}

	m_rect->Animation = e_Ani::e_Normal;
	m_rect->d = false;
	m_rect->JumpCount = 0;
	m_rect->Character_Check = false;
}

void Loop::Init()
{
	std::random_device rnd;     // 非決定的な乱数生成器
	std::mt19937_64 mt(rnd());
	std::uniform_int_distribution<> rand7(0, 6);
	std::uniform_int_distribution<> rand3(0, 2);


	//動的配列
	m_Stage = new s_Text * [STAGE_HEIGHT_Num];
	for (int i = 0; i < STAGE_HEIGHT_Num; ++i)
	{
		m_Stage[i] = new s_Text[STAGE_WIDTH_Num];
	}
	
	
	m_Block = new s_Rect[STAGE_TOTAL_Num];


	for (int y = 0; y < STAGE_HEIGHT_Num; ++y)
	{
		for (int x = 0; x < STAGE_WIDTH_Num; ++x)
		{
			m_Stage[y][x].k = e_Type::e_Empty;
		}
	}

	for (int x = 0; x < STAGE_WIDTH_Num; ++x)m_Stage[STAGE_HEIGHT_Num - 1][x].k = e_Type::e_Ground;

	for (int y = 0; y < STAGE_HEIGHT_Num; ++y)
	{
		for (int x = 0; x < STAGE_WIDTH_Num; ++x)
		{
			m_Stage[y][x].x = x;
			m_Stage[y][x].y = y;
		}
	}

	int x = 0;
	int y = 8;
	int n = 5;


	do {
		for (int i = 0; i < n; ++i)
		{
			m_Stage[y][x].k = e_Type::e_Block;
			x++;
		}
		y = 2 + rand7(mt);
		n = 2 + rand3(mt);
	} while (x < STAGE_WIDTH_Num - 10);


	m_Stage[STAGE_HEIGHT_Num - 3][2].k = e_Type::e_Player;

	int i = 0;
	for (int y = 0; y < STAGE_HEIGHT_Num; ++y)
	{
		for (int x = 0; x < STAGE_WIDTH_Num; ++x)
		{
			switch (m_Stage[y][x].k)
			{
			case e_Type::e_Empty:
				m_Block[i].Handle[e_Ani::e_Normal].Handle = 0;
				m_Block[i].d = false;
				m_Block[i].Character_Check = false;
				break;
			case e_Type::e_Ground:

				m_Block[i].Width = MAP_CHIP_SIZE;
				m_Block[i].Height = MAP_CHIP_SIZE;
				m_Block[i].Handle[e_Ani::e_Normal].Handle = LoadGraph("./image/chip1.png");
				m_Block[i].d = false;
				m_Block[i].Character_Check = false;

				break;
			case e_Type::e_Block:

				m_Block[i].Width = MAP_CHIP_SIZE;
				m_Block[i].Height = MAP_CHIP_SIZE;
				m_Block[i].Handle[e_Ani::e_Normal].Handle = LoadGraph("./image/chip2.png");
				m_Block[i].d = false;
				m_Block[i].Character_Check = false;

				break;
			case e_Type::e_Thorn:
				m_Block[i].Width = MAP_CHIP_SIZE;
				m_Block[i].Height = MAP_CHIP_SIZE;
				m_Block[i].Handle[e_Ani::e_Normal].Handle = LoadGraph("./image/chip3.png");
				m_Block[i].d = false;
				m_Block[i].Character_Check = false;
				break;
			case e_Type::e_Enemy1:
				m_Block[i].Width = MAP_CHIP_SIZE;
				m_Block[i].Height = MAP_CHIP_SIZE;
				m_Block[i].Handle[e_Ani::e_Normal].Handle = LoadGraph("./image/chip4.png");
				m_Block[i].d = false;
				m_Block[i].Character_Check = false;
				break;

			case e_Type::e_Coin:
				m_Block[i].Width = MAP_CHIP_SIZE;
				m_Block[i].Height = MAP_CHIP_SIZE;
				m_Block[i].Handle[e_Ani::e_Normal].Handle = LoadGraph("./image/chip5.png");
				m_Block[i].d = false;
				m_Block[i].Character_Check = true;
				break;
		
			case e_Type::e_Goal:
				m_Block[i].Width = MAP_CHIP_SIZE;
				m_Block[i].Height = MAP_CHIP_SIZE;
				m_Block[i].Handle[e_Ani::e_Normal].Handle = LoadGraph("./image/chip6.png");
				m_Block[i].d = false;
				m_Block[i].Character_Check = false;
				break;
			case e_Type::e_Player:
				m_Block[i].Width = MAP_CHIP_SIZE-1;
				m_Block[i].Height = MAP_CHIP_SIZE-1;
				m_Block[i].Handle[e_Ani::e_Normal].Handle = LoadGraph("./image/mgirl1.png");
				m_Block[i].Handle[e_Ani::e_Walk1].Handle = LoadGraph("./image/mgirl2.png");
				m_Block[i].Handle[e_Ani::e_Walk2].Handle = LoadGraph("./image/mgirl3.png");
				m_Block[i].Handle[e_Ani::e_End].Handle = LoadGraph("./image/mgirl4.png");
				m_Block[i].d = false;
				m_Block[i].Character_Check = true;
				break;
			default:
				break;
			}
			
			m_Block[i].x = m_Stage[y][x].x*MAP_CHIP_SIZE;
			m_Block[i].y = m_Stage[y][x].y*MAP_CHIP_SIZE;
			m_Block[i].k = m_Stage[y][x].k;
			m_Block[i].r = 0;
			m_Block[i].JumpCount = 0;
			m_Block[i].Animation = e_Ani::e_Normal;
			++i;
		}
	
	}

	//メモリ解放


	//m_Stage = 0;
} 

void Loop::Update()
{
	int y_add = 0;

	const int a = 25;


	Player_Copy();
	if (m_Pad_Count[e_But::But_Right] != 0)
	{
		m_Player->d = false;

		for (int i = 0; i < Move_X; ++i)
		{

			//マリオx座標計算
			m_Player->x = m_Player->x + 1;

			if (m_Player->x > g_WIN_WIDTH / 2 &&
				m_Player->x < STAGE_WIDTH_Num * MAP_CHIP_SIZE - g_WIN_WIDTH / 2)
			{
				m_Camera_x = m_Camera_x - 1;
			}

			//x方向のマリオとブロックの接触判定
			if (m_Player->x > STAGE_WIDTH_Num * MAP_CHIP_SIZE - m_Player->Width ||
				HitJudg(*m_Player, m_Plyer_i, false) )
			{
				//マリオx座標計算
				m_Player->x = m_Player->x - 1;

				if (m_Player->x > g_WIN_WIDTH / 2 &&
					m_Player->x < STAGE_WIDTH_Num * MAP_CHIP_SIZE - g_WIN_WIDTH / 2)
				{
					m_Camera_x = m_Camera_x + 1;
				}

				break;
			}
		}
	}

	if (m_Pad_Count[e_But::But_Left] != 0)
	{
		m_Player->d = true;

		for (int i = 0; i < Move_X; ++i)
		{

			//マリオx座標計算
			m_Player->x -= 1;

			if (m_Player->x > g_WIN_WIDTH / 2 &&
				m_Player->x < STAGE_WIDTH_Num * MAP_CHIP_SIZE - g_WIN_WIDTH / 2)
			{
				m_Camera_x += 1;
			}

			//x方向のマリオとブロックの接触判定
			if (m_Player->x < 1 ||
				HitJudg(*m_Player, m_Plyer_i, false) == true)
			{
				//マリオx座標計算
				m_Player->x = m_Player->x + 1;

				if (m_Player->x > g_WIN_WIDTH / 2 &&
					m_Player->x < STAGE_WIDTH_Num * MAP_CHIP_SIZE - g_WIN_WIDTH / 2)
				{
					m_Camera_x = m_Camera_x - 1;
				}

				break;
			}
		}
	}

	if (m_Pad_Count[e_But::But_A] == 1 && Jump_State == e_Jump::e_Land)
	{
		Jump_State = e_Jump::e_Jumping;

		Jump_Ymem = m_Player->y;
	}

	if (Jump_State == e_Jump::e_Jumping)
	{
		++m_Player->JumpCount;

		y_add = (m_Player->JumpCount * m_Player->JumpCount) / a;

		for (int i = 0; i < y_add; ++i)
		{
			m_Player->y -= 1;

			//y方向のマリオとブロックの接触判定
			if (m_Player->y < 0 ||
				HitJudg(*m_Player, m_Plyer_i, TRUE) == TRUE ||
				Move_Max_Y == Jump_Ymem - m_Player->y)
			{
				//ジャンプ中フラグ変更
				Jump_State = e_Jump::e_Fall;

				m_Player->y += 1;

				m_Player->JumpCount = 0;

				break;

			}
		}
	}

	//自由落下
	if (Jump_State == e_Jump::e_Fall || Jump_State == e_Jump::e_Land)
	{
		//ジャンプカウンタ
		m_Player->JumpCount += 1;

		y_add = (m_Player->JumpCount * m_Player->JumpCount) / a;

		for (int i = 0; i < y_add; ++i)
		{
			m_Player->y += 1;

			//y方向のマリオとブロックの接触判定
			if (m_Player->y > g_WIN_HEIGHT ||
				HitJudg(*m_Player, m_Plyer_i, TRUE) == TRUE)
			{
				//ジャンプ中フラグ変更
				Jump_State = e_Jump::e_Land;

				m_Player->y -= 1;

				m_Player->JumpCount = 0;

				break;

			}
		}
	}

	//マリオアニメーション
	if (Jump_State == e_Jump::e_Jumping || Jump_State == e_Jump::e_Fall)
	{
		m_Player->Animation = e_Ani::e_Jump;
	}
	else if (m_Player_x != m_Player->x)
	{
		
	}
}

void Loop::Draw()
{
	for (int i = 0; i < STAGE_TOTAL_Num; ++i)
	{
		if (!m_Block[i].d)
		{
			DrawGraph(m_Block[i].x + m_Camera_x, m_Block[i].y, m_Block[i].Handle[0].Handle, true);
		}
		else if (m_Block[i].d)
		{
			DrawTurnGraph(m_Block[i].x + m_Camera_x, m_Block[i].y, m_Block[i].Handle[0].Handle, true);
		}
	}
}
