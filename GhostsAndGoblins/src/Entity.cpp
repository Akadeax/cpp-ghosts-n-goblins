#include "pch.h"

#include "EntityManager.h"
#include "Entity.h"
#include "Component.h"
#include <iostream>

Entity::Entity()
{
}

Entity::~Entity()
{
	for (Component* comp : m_Components)
	{
		delete comp;
		comp = nullptr;
	}
}

void Entity::AddComponent(Component* comp)
{
	m_Components.push_back(comp);
}

std::list<Component*> Entity::GetComponents() const
{
	return m_Components;
}

void Entity::SetTag(std::string newTag)
{
	m_Tag = newTag;
}

std::string Entity::GetTag() const
{
	return m_Tag;
}

void Entity::SetActive(bool newState)
{
	m_IsActive = newState;
}

bool Entity::IsActive() const
{
	return m_IsActive;
}
