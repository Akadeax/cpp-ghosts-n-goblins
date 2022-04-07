#include "pch.h"

#include "Collider.h"
#include "Entity.h"
#include <cassert>
#include "PhysicsHandler.h"
#include "Transform.h"
#include "Scene.h"
#include "utils.h"

Collider::Collider(Entity* entity, Vector2f offset, Vector2f size)
	: Component(entity)
{
	m_Offset = offset;
	m_Size = size;
}

Collider::~Collider()
{
	GetPhysicsHandler()->RemoveCollider(this);
}

void Collider::Initialize()
{
	m_pTransform = m_pParent->GetComponent<Transform>();
	assert(m_pTransform != nullptr && "Entity has collider but no transform");
	GetPhysicsHandler()->AddCollider(this);
}

bool Collider::IsAABBCollidingWith(const Collider* other, Vector2f vel) const
{
	Rectf thisRect = Rectf(
		GetBottomLeftPosition().x + vel.x,
		GetBottomLeftPosition().y + vel.y,
		m_Size.x,
		m_Size.y
	);
	Rectf otherRect = Rectf(
		other->GetBottomLeftPosition().x,
		other->GetBottomLeftPosition().y,
		other->m_Size.x,
		other->m_Size.y
	);

	return
		thisRect.left + thisRect.width > otherRect.left &&
		thisRect.left < otherRect.left + otherRect.width &&
		thisRect.bottom + thisRect.height > otherRect.bottom &&
		thisRect.bottom < otherRect.bottom + otherRect.height;
}

// Assuming we have two AABBs, what's the actual distance between them?
// eg. if `e1` is on the left of `e2`, we want `dx` to be `e2.left - e1.right`.
Vector2f Collider::CalculateAABBDistanceTo(const Collider* other) const
{
	float dx = 0;
	float dy = 0;

	Vector2f thisBottomLeft = GetBottomLeftPosition();

	Vector2f otherBottomLeft = other->GetBottomLeftPosition();

	if (thisBottomLeft.x + m_Size.x < otherBottomLeft.x)
	{
		dx = otherBottomLeft.x - (thisBottomLeft.x + m_Size.x);
	}
	else if (thisBottomLeft.x > otherBottomLeft.x + other->m_Size.x)
	{
		dx = (otherBottomLeft.x + other->m_Size.x) - thisBottomLeft.x;
	}

	if (thisBottomLeft.y + m_Size.y < otherBottomLeft.y)
	{
		dy = otherBottomLeft.y - (thisBottomLeft.y + m_Size.y);
	}
	else if (thisBottomLeft.y > otherBottomLeft.y + other->m_Size.y)
	{
		dy = (otherBottomLeft.y + other->m_Size.y) - thisBottomLeft.y;
	}

	return Vector2f(dx, dy);
}

Vector2f Collider::GetBottomLeftPosition() const
{
	return Vector2f(
		m_pTransform->GetPosition().x + m_Offset.x - (m_Size.x / 2),
		m_pTransform->GetPosition().y + m_Offset.y - (m_Size.y / 2)
	);
}

void Collider::CollidingUpdate(Collider* other, float deltaTime)
{
}

void Collider::NotCollidingUpdate(float deltaTime)
{
}

void Collider::DrawCollider() const
{
	// Change color if it's trigger
	utils::SetColor(Color4f(m_IsTrigger ? 0.f : 1.f, m_IsTrigger ? 1.f : 0.f, 0.f, 1.f));

	Rectf thisRect = Rectf(
		GetBottomLeftPosition().x,
		GetBottomLeftPosition().y,
		m_Size.x,
		m_Size.y
	);
	utils::DrawRect(thisRect, 2);
}

Vector2f Collider::GetOffset() const
{
	return m_Offset;
}

Vector2f Collider::GetSize() const
{
	return m_Size;
}

void Collider::SetTrigger(bool newVal)
{
	m_IsTrigger = newVal;
}

bool Collider::IsTrigger() const
{
	return m_IsTrigger;
}

Transform* Collider::GetTransform()
{
	return m_pTransform;
}

bool Collider::CompareTag(std::string tag) const
{
	return m_pParent->GetTag() == tag;
}
