#pragma once
class Keyboard;
class Title
{
private:
	void m_Logo_Render(void);
public:
	void init(void);
	~Title();
	void Update(Keyboard* Key);
	void Render(void);
};

