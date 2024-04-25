#pragma once
class Keyboard;
class Title
{
private:
	void m_Logo_Render(void);
	void m_Logo_Update(void);
	void m_Title_Render(void);
	void m_Title_Update(Keyboard* Key);
public:
	void init(void);
	~Title();
	void Update(Keyboard* Key);
	void Render(void);
	bool m_Title_Renderflag{TRUE};
	float  m_Title_Frame = 0.0f;
};

