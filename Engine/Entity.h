#pragma once
#include <string>
#include <iostream>
#include <list>
#include "Component.h"
#include "InputHandler.h"

class EntityKeeper;
class Scene;

class Entity
{
public:
	Entity& operator=(const Entity& rhs) = delete;
	Entity& operator=(Entity&& rhs) = delete;
	Entity(const Entity& rhs) = delete;
	Entity(Entity&& rhs) = delete;

	template<typename TComponent>
	TComponent* GetComponent() const;
	void AddComponent(Component* comp);
	std::list<Component*> GetComponents() const;

	void Initialize();

	// Non-Unique Identifiers that can be used to filter Entities
	std::string GetTag() const;
	void SetTag(std::string newTag);

	// Inactive Entities are neither updated nor drawn
	void SetActive(bool newState);
	bool IsActive() const;

	Scene* GetScene() const;

	// Entities and all components within them are updated
	// from highest update priority to lowest, so this value
	// determines for example like render priority (!)
	int GetUpdatePriority() const;

private:
	Scene* m_pScene;

	const int m_UpdatePriority;

	bool m_IsActive = true;
	std::list<Component*> m_Components;
	std::string m_Tag;

	// Allow EntityKeeper to manage lifecycle of Entities
	explicit Entity(Scene* scene, int updatePriority);
	virtual ~Entity();
	friend class EntityKeeper;
};

// Definition in header because templates are... interesting
// Fetches Component of type TComponent if this Entity has it
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
