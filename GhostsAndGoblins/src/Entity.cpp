#include "pch.h"

#include "Entity.h"
#include "Component.h"
#include <iostream>

Entity::Entity()
	: m_IsActive{true}
{
}

Entity::~Entity()
{
	for (Component* component : m_Components)
	{
		delete component;
	}
}

void Entity::AddComponent(Component* comp)
{
	m_Components.insert(comp);
}

std::set<Component*> Entity::GetComponents() const
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
