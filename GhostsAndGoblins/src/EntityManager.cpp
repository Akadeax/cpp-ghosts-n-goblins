#include "pch.h"

#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager(Scene* scene)
{
    m_pScene = scene;
}

EntityManager::~EntityManager()
{
    for (auto& entity : m_Entities)
    {
        delete entity;
        entity = nullptr;
    }
}

Entity* EntityManager::CreateEntity()
{
    return CreateEntity(0, "");
}

Entity* EntityManager::CreateEntity(int updatePriority)
{
    return CreateEntity(updatePriority, "");
}

Entity* EntityManager::CreateEntity(int updatePriority, std::string tag)
{
    Entity* newEnt = new Entity(m_pScene, updatePriority);

    std::list<Entity*>::iterator it = m_Entities.begin();
    while (it != m_Entities.end() && (*it)->GetUpdatePriority() < updatePriority)
    {
        it++;
    }
    m_Entities.insert(it, newEnt);

    return newEnt;
}


void EntityManager::DeleteEntity(Entity* entity)
{
    if (entity == nullptr) return;

    m_Entities.remove(entity);
    delete entity;
}

void EntityManager::UpdateEntities(float deltaTime)
{
    for (Entity* entity : m_Entities)
    {
        for (Component* comp : entity->GetComponents())
        {
            comp->Update(deltaTime);
        }
    }
}

void EntityManager::DrawEntities() const
{
    for (Entity* entity : m_Entities)
    {
        glPushMatrix();
        for (Component* comp : entity->GetComponents())
        {
            comp->Draw();
        }
        glPopMatrix();
    }
}

Entity* EntityManager::GetEntityWithTag(std::string tag)
{
    for (Entity* e : m_Entities)
    {
        if (e->GetTag() == tag) return e;
    }
    return nullptr;
}
