#pragma once
#include <list>

class Scene;
class Entity;
class Component;

class EntityManager
{
public:
	EntityManager(Scene* scene);
	~EntityManager();

	Entity* CreateEntity();
	void DeleteEntity(Entity* entity);

	void UpdateEntities(float deltaTime);
	void DrawEntities() const;
private:
	Scene* m_pScene;

	std::list<Entity*> m_Entities;
};

