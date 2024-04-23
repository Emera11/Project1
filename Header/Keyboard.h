#pragma once
#include <Dxlib.h>

static const int  KEY_INDEX_MAX{ 256 };

class Keyboard
{
private:

	//現在のキーを押しているフレーム数
	int Now_Key_PressFrame[KEY_INDEX_MAX]{ 0 };
	//一つ前のキーを押しているフレーム数
	int Old_Key_PressFrame[KEY_INDEX_MAX]{ 0 };

public:
	~Keyboard()
	{
		Now_Key_PressFrame[KEY_INDEX_MAX]={ 0 };
		Old_Key_PressFrame[KEY_INDEX_MAX]={ 0 };
	}

public:

	void KeyUpdate(void)
	{
		//一時的に保存するキー情報
		char KeyState[KEY_INDEX_MAX];

		//すべてのキー情報を一度に取得
		GetHitKeyStateAll(&KeyState[0]);

		for (int i = 0; i < KEY_INDEX_MAX; ++i)
		{
			Old_Key_PressFrame[i] = Now_Key_PressFrame[i];

			//現在、キーがおされている時
			if(KeyState[i] != 0)
			{
				//おされているフレーム数をカウントアップ
				Now_Key_PressFrame[i]++;
			}
			//現在、キーがおされている時
			else if (KeyState[i] ==  0)
			{
				//おされているフレーム数をカウントアップ
				Now_Key_PressFrame[i] = 0;
			}
		}

	};

	bool KeyDown(int KEY_INPUT)
	{
		//現在おされているキーのフレーム数が0より上なら
		if (Now_Key_PressFrame[KEY_INPUT] > 0)
		{
			return TRUE;
		}

		return FALSE;
	};

	bool KeyClick(int KEY_INPUT)
	{
		//現在おされているキーのフレーム数が0より上なら
		if (Now_Key_PressFrame[KEY_INPUT] == 0 && Old_Key_PressFrame[KEY_INPUT] > 0)
		{
			return TRUE;
		}

		return FALSE;
	};

	int KeyPressFrame(int KEY_INPUT)
	{
		return Now_Key_PressFrame[KEY_INPUT];
	};


};
