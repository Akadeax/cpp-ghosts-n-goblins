#include "pch.h"

#include "RectCollider.h"

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

bool RectCollider::IntersectingRect(RectCollider* other) const
{
	// TODO: implement collision logic for 2 rects
	return false;
}

