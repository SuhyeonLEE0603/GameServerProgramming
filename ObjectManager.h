#pragma once
#include "stdafx.h"
#include "King.h"

class ObjectManager : Object
{
private:
	int m_ref;
	std::vector<Object*> m_object_container;
public:

	ObjectManager();
	void Init();
	//void AddKing(King*);
	void Render(HDC) override;
	void ReleaseObject(int);
	~ObjectManager();
};

