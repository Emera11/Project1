#pragma once
class Keyboard;

class a_Title
{
private:
	int m_Title{ 0 };
	int m_Illust{ 0 };
public:
	void Init();
	void Update(Keyboard* Key, int& idx);
	void Draw();
};

