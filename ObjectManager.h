#pragma once
#include "stdafx.h"
#include "King.h"

class ObjectManager
{
private:
	int m_ref;
	std::vector<King> m_object_container;

public:

	ObjectManager();
	void AddObject(King&);
	void Render(HDC);
	void ReleaseObject(int);
	~ObjectManager();
};

