#include "pch.h"

#include "Entity.h"
#include "EntityKeeper.h"

EntityKeeper::EntityKeeper(Scene* scene)
    : m_pScene{scene}
{
}

EntityKeeper::~EntityKeeper()
{
    for (auto& entity : m_Entities)
    {
        delete entity;
        entity = nullptr;
    }
}

Entity* EntityKeeper::CreateEntity()
{
    return CreateEntity(0, "");
}

Entity* EntityKeeper::CreateEntity(int updatePriority)
{
    return CreateEntity(updatePriority, "");
}

Entity* EntityKeeper::CreateEntity(int updatePriority, std::string tag)
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

void EntityKeeper::DeleteEntity(Entity* entity)
{
    if (entity == nullptr) return;

    m_Entities.remove(entity);
    delete entity;
}

void EntityKeeper::UpdateEntities(float deltaTime)
{
    for (Entity* entity : m_Entities)
    {
        for (Component* comp : entity->GetComponents())
        {
            comp->Update(deltaTime);
        }
    }
}

void EntityKeeper::DrawEntities() const
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

Entity* EntityKeeper::GetEntityWithTag(std::string tag)
{
    for (Entity* e : m_Entities)
    {
        if (e->GetTag() == tag) return e;
    }
    return nullptr;
}
