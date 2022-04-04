#include "pch.h"

#include <iostream>
#include "RectCollider.h"
#include "Transform.h"
#include "Camera.h"
#include "Scene.h"
#include "Entity.h"
#include "utils.h"

RectCollider::RectCollider(Entity* entity, Vector2f offset, Vector2f size)
	: Collider(entity, Collider::Type::Rect)
{
	m_Offset = offset;
	m_Size = size;
}

Vector2f RectCollider::GetOffset() const
{
	return m_Offset;
}

Vector2f RectCollider::GetSize() const
{
	return m_Size;
}

void RectCollider::DrawCollider() const
{
	utils::SetColor(Color4f(1, 0, 0, 1));
	Rectf thisRect = Rectf(
		m_pTransform->GetPosition().x + m_Offset.x - (m_Size.x / 2),
		m_pTransform->GetPosition().y + m_Offset.y - (m_Size.y / 2),
		m_Size.x,
		m_Size.y
	);
	utils::DrawRect(thisRect, 2);
}

bool RectCollider::IntersectingRect(const RectCollider* other) const
{
	Rectf thisRect = Rectf(
		m_pTransform->GetPosition().x + m_Offset.x - (m_Size.x / 2),
		m_pTransform->GetPosition().y + m_Offset.y - (m_Size.y / 2),
		m_Size.x,
		m_Size.y
	);
	Rectf otherRect = Rectf(
		other->m_pTransform->GetPosition().x + other->m_Offset.x - (other->m_Size.x / 2),
		other->m_pTransform->GetPosition().y + other->m_Offset.y - (other->m_Size.y / 2),
		other->m_Size.x,
		other->m_Size.y
	);

	return
		thisRect.left + thisRect.width > otherRect.left &&
		thisRect.left < otherRect.left + otherRect.width &&
		thisRect.bottom + thisRect.height > otherRect.bottom &&
		thisRect.bottom < otherRect.bottom + otherRect.height;
}
