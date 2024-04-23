#pragma once
#include <Dxlib.h>

static const int  KEY_INDEX_MAX{ 256 };

class Keyboard
{
private:

	//���݂̃L�[�������Ă���t���[����
	int Now_Key_PressFrame[KEY_INDEX_MAX]{ 0 };
	//��O�̃L�[�������Ă���t���[����
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
		//�ꎞ�I�ɕۑ�����L�[���
		char KeyState[KEY_INDEX_MAX];

		//���ׂẴL�[������x�Ɏ擾
		GetHitKeyStateAll(&KeyState[0]);

		for (int i = 0; i < KEY_INDEX_MAX; ++i)
		{
			Old_Key_PressFrame[i] = Now_Key_PressFrame[i];

			//���݁A�L�[��������Ă��鎞
			if(KeyState[i] != 0)
			{
				//������Ă���t���[�������J�E���g�A�b�v
				Now_Key_PressFrame[i]++;
			}
			//���݁A�L�[��������Ă��鎞
			else if (KeyState[i] ==  0)
			{
				//������Ă���t���[�������J�E���g�A�b�v
				Now_Key_PressFrame[i] = 0;
			}
		}

	};

	bool KeyDown(int KEY_INPUT)
	{
		//���݂�����Ă���L�[�̃t���[������0����Ȃ�
		if (Now_Key_PressFrame[KEY_INPUT] > 0)
		{
			return TRUE;
		}

		return FALSE;
	};

	bool KeyClick(int KEY_INPUT)
	{
		//���݂�����Ă���L�[�̃t���[������0����Ȃ�
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
