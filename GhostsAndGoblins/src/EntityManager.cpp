#include "pch.h"

#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
    for (Entity* entity : m_Entities)
    {
        delete entity;
    }
}

Entity* EntityManager::CreateEntity()
{
    Entity* newEntity = new Entity();
    m_Entities.insert(newEntity);
    return newEntity;
}

bool EntityManager::DeleteEntity(Entity* entity)
{
    for (Entity* entPointer : m_Entities)
    {
        if (entPointer == entity)
        {
            m_Entities.erase(entity);
            delete entity;
            return true;
        }
    }

    return false;
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
        for (Component* comp : entity->GetComponents())
        {
            comp->Draw();
        }
    }
}
