#include "pch.h"

#include "Collider.h"
#include "Entity.h"
#include <cassert>
#include "RectCollider.h"
#include "PhysicsHandler.h"
#include "Transform.h"
#include "Scene.h"

Collider::Collider(Entity* entity, Type type)
	: Component(entity)
{
	m_Type = type;
}

Collider::~Collider()
{
	PhysicsHandler* ph = m_pParent->GetScene()->GetPhysicsHandler();
	ph->RemoveCollider(this);
}

void Collider::Initialize()
{
	m_pTransform = m_pParent->GetComponent<Transform>();
	assert(m_pTransform != nullptr && "Entity has collider but no transform");
}

bool Collider::Intersecting(Collider* other) const
{
	switch (other->GetType())
	{
	case Type::Rect:
		return IntersectingRect(static_cast<RectCollider*>(other));
	default:
		return false;
	}
}

void Collider::OnCollisionUpdate(Collider* other, float deltaTime)
{
	std::cout << "Coll" << std::endl;
}

Collider::Type Collider::GetType() const
{
	return m_Type;
}
