#include "pch.h"

#include "Entity.h"
#include "Scene.h"

void Entity::AddComponent(Component* comp)
{
	m_Components.push_back(comp);
}

std::list<Component*> Entity::GetComponents() const
{
	return m_Components;
}

void Entity::Initialize()
{
	for (auto&& component : m_Components)
	{
		component->Initialize();
	}
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

Scene* Entity::GetScene() const
{
	return m_pScene;
}

int Entity::GetUpdatePriority() const
{
	return m_UpdatePriority;
}

Entity::Entity(Scene* scene, int updatePriority)
	: m_pScene{scene}, m_UpdatePriority{updatePriority}
{
}

Entity::~Entity()
{
	for (auto&& comp : m_Components)
	{
		delete comp;
		comp = nullptr;
	}
}
