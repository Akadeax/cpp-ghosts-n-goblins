#include "pch.h"

#include <cassert>
#include "PhysicsBody.h"
#include "Entity.h"
#include "PhysicsHandler.h"
#include "Scene.h"
#include "Collider.h"
#include "Transform.h"

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
    m_Transform = m_pParent->GetComponent<Transform>();
    assert(m_Transform != nullptr && "Entity has physics body but no transform");
    m_pParent->GetScene()->GetPhysicsHandler()->AddPhysicsBody(this);
}

Transform* PhysicsBody::GetTransform()
{
    return m_Transform;
}

Collider* PhysicsBody::GetCollider() const
{
    return m_Collider;
}

Vector2f PhysicsBody::GetVelocity() const
{
    return m_Velocity;
}

void PhysicsBody::SetVelocity(Vector2f velocity)
{
    m_Velocity = velocity;
}

void PhysicsBody::SetXVelocity(float x)
{
    m_Velocity.x = x;
}

void PhysicsBody::SetYVelocity(float y)
{
    m_Velocity.y = y;
}

void PhysicsBody::AddVelocity(Vector2f velocity)
{
    m_Velocity += velocity;
}
