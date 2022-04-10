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
	Entity* CreateEntity(int updatePriority);
	Entity* CreateEntity(int updatePriority, std::string tag);
	void DeleteEntity(Entity* entity);

	void UpdateEntities(float deltaTime);
	void DrawEntities() const;

	Entity* GetEntityWithTag(std::string tag);
private:
	Scene* m_pScene;

	std::list<Entity*> m_Entities;
};

