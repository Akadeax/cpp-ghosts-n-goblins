#pragma once
#include <list>

class Entity;
class Component;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	Entity* CreateEntity();
	void DeleteEntity(Entity* entity);

	void UpdateEntities(float deltaTime);
	void DrawEntities() const;
private:
	std::list<Entity*> m_Entities;
};

