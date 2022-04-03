#include "pch.h"

#include <cassert>
#include "PhysicsBody.h"
#include "Entity.h"
#include "PhysicsHandler.h"
#include "Scene.h"
#include "Collider.h"

PhysicsBody::PhysicsBody(Entity* entity)
    : Component(entity)
{
}

PhysicsBody::~PhysicsBody()
{
    PhysicsHandler* ph = m_pParent->GetScene()->GetPhysicsHandler();
    ph->RemovePhysicsBody(this);
}

void PhysicsBody::Initialize()
{
    m_Collider = m_pParent->GetComponent<Collider>();
    assert(m_Collider != nullptr && "Entity has physics body but no collider");
}

Collider* PhysicsBody::GetCollider() const
{
    return m_Collider;
}
