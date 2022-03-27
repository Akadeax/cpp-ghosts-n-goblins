#pragma once
#include <set>

class Entity;
class Component;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	Entity* CreateEntity();
	bool DeleteEntity(Entity* entity);

	void UpdateEntities(float deltaTime);
	void DrawEntities() const;
private:
	std::set<Entity*> m_Entities;
};

