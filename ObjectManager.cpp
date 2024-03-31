#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	m_ref = 0;
	m_object_container.reserve(10);
}

void ObjectManager::AddObject(King& king)
{
	m_ref++;
	m_object_container.emplace_back(king);
}

void ObjectManager::Render(HDC hdc)
{
	for (auto& a : m_object_container)
	{
		a.Render(hdc);
	}
}

void ObjectManager::ReleaseObject(int id)
{
	m_ref--;
	m_object_container.erase(m_object_container.begin() + id);
}

ObjectManager::~ObjectManager()
{
	for (auto it = m_object_container.begin(); it != m_object_container.end(); ++it)
	{
		m_object_container.erase(it);
	}
}
