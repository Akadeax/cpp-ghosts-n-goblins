#include "pch.h"

#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager()
{
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
    Entity* newEnt = new Entity();
    m_Entities.push_back(newEnt);
    return newEnt;
}

void EntityManager::DeleteEntity(Entity* entity)
{
    m_Entities.remove(entity);
    delete entity;
}

void EntityManager::InitializeEntities()
{
    for (Entity* entity : m_Entities)
    {
        for (Component* comp : entity->GetComponents())
        {
            comp->Initialize();
        }
    }
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
