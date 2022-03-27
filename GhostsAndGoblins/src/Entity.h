#pragma once
#include <set>
#include <string>
#include <iostream>
#include "Component.h"

class Entity
{
public:
	Entity& operator=(const Entity& other) = delete;
	Entity(const Entity& other) = delete;
	Entity(Entity&&) = delete;
	Entity& operator=(Entity&&) = delete;
	virtual ~Entity();

	template<typename TComponent>
	TComponent* GetComponent(Component::Type type) const;
	void AddComponent(Component* comp);
	std::set<Component*> GetComponents() const;

	void SetTag(std::string newTag);
	std::string GetTag() const;

	void SetActive(bool newState);
	bool IsActive() const;

private:
	bool m_IsActive;
	std::set<Component*> m_Components;
	std::string m_Tag;

	Entity();
	// only allow EntityManager to make instances of Entity
	friend class EntityManager;
};

// Definition in header because templates are... interesting
template<typename TComponent>
TComponent* Entity::GetComponent(Component::Type type) const
{
	for (Component* comp : m_Components)
	{
		if (comp->GetType() == type)
		{
			return reinterpret_cast<TComponent*>(comp);
		}
	}

	return nullptr;
}
