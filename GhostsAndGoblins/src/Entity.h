#pragma once
#include <string>
#include <iostream>
#include <list>
#include "Component.h"

class EntityManager;

class Entity
{
public:
	Entity& operator=(const Entity& other) = delete;
	Entity(const Entity& other) = delete;
	Entity(Entity&&) = delete;
	Entity& operator=(Entity&&) = delete;

	template<typename TComponent>
	TComponent* GetComponent() const;
	void AddComponent(Component* comp);
	std::list<Component*> GetComponents() const;

	void SetTag(std::string newTag);
	std::string GetTag() const;

	void SetActive(bool newState);
	bool IsActive() const;

private:
	bool m_IsActive = true;
	std::list<Component*> m_Components;
	std::string m_Tag;

	Entity();
	virtual ~Entity();

	// Allow EntityManager to manage lifecycle of Entities
	friend class EntityManager;
};

// Definition in header because templates are... interesting
template<typename TComponent>
TComponent* Entity::GetComponent() const
{
	static_assert(std::is_base_of<Component, TComponent>::value, "Provided template argument is not a component");

	for (Component* comp : m_Components)
	{
		if (typeid(*comp) == typeid(TComponent))
		{
			return reinterpret_cast<TComponent*>(comp);
		}
	}

	return nullptr;
}
