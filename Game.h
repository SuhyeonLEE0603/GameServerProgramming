#pragma once
#include "ObjectManager.h"
#include "stdafx.h"

class Game
{
private:
	HDC m_hdcBuffer; // �� ���ۿ� HDC
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;

	ObjectManager* m_objectmanager;

public:
	Game() {};
	~Game() {};
	void Init();
	void Update();
	void Render(HDC);
};

extern HDC g_hdc;
