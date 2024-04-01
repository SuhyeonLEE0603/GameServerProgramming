#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	m_ref = 0;
	m_object_container.reserve(10);
}

void ObjectManager::Init()
{
	for (int i = 0; i < 10; ++i)
	{
		if (m_object_container[i] != nullptr)
		{
			m_object_container[i]->Init();
		}
	}
}

//void ObjectManager::AddKing(King* object)
//{
//	//object = new King;
//	m_ref++;
//	m_object_container.emplace_back(object);
//}

void ObjectManager::Render(HDC hdc)
{
	for (auto& a : m_object_container)
	{
		a->Render(hdc);
	}
}

void ObjectManager::ReleaseObject(int id)
{
	delete m_object_container[id];
	m_object_container.erase(m_object_container.begin() + id);
	m_ref--;

}

ObjectManager::~ObjectManager()
{
	for (auto it = m_object_container.begin(); it != m_object_container.end(); ++it)
	{
		delete *it;
		m_object_container.erase(it);
		m_ref--;
	}
}
