#pragma once
#include <string>
#include <iostream>
#include <list>
#include "Component.h"
#include "InputHandler.h"

class EntityManager;
class Scene;

class Entity
{
public:
	Entity(Scene* scene, int updatePriority);

	Entity& operator=(const Entity& other) = delete;
	Entity(const Entity& other) = delete;
	Entity(Entity&&) = delete;
	Entity& operator=(Entity&&) = delete;

	template<typename TComponent>
	TComponent* GetComponent() const;
	void AddComponent(Component* comp);
	std::list<Component*> GetComponents() const;

	void Initialize();

	void SetTag(std::string newTag);
	std::string GetTag() const;

	void SetActive(bool newState);
	bool IsActive() const;

	Scene* GetScene() const;
	InputHandler* GetInputHandler() const;

	int GetUpdatePriority() const;

private:
	Scene* m_pScene;

	const int m_UpdatePriority;

	bool m_IsActive = true;
	std::list<Component*> m_Components;
	std::string m_Tag;

	// Allow EntityManager to manage lifecycle of Entities
	Entity();
	virtual ~Entity();
	friend class EntityManager;
};

// Definition in header because templates are... interesting
template<typename TComponent>
TComponent* Entity::GetComponent() const
{
	static_assert(std::is_base_of<Component, TComponent>::value, "Provided template argument is not a component");

	for (Component* comp : m_Components)
	{
		TComponent* castComponent = dynamic_cast<TComponent*>(comp);
		if (castComponent) return castComponent;
		else continue;
	}

	return nullptr;
}
