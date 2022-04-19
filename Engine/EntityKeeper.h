#pragma once
#include <list>
#include <string>

class Scene;
class Entity;
class Component;

class EntityKeeper final
{
public:
	explicit EntityKeeper(Scene* scene);
	EntityKeeper& operator=(const EntityKeeper& rhs) = delete;
	EntityKeeper& operator=(EntityKeeper&& rhs) = delete;
	EntityKeeper(const EntityKeeper& rhs) = delete;
	EntityKeeper(EntityKeeper&& rhs) = delete;
	~EntityKeeper();

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

