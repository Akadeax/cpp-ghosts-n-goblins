#include "pch.h"

#include "Transform.h"
#include "Component.h"


Transform::Transform(Entity* parent, Vector2f startingPos)
	: Component(parent)
{
	m_Position = startingPos;
}

Transform::~Transform()
{
}

Vector2f Transform::GetPosition() const
{
	return m_Position;
}

void Transform::SetPosition(Vector2f newPos)
{
	m_Position = newPos;
}

void Transform::MovePosition(Vector2f moveVec)
{
	m_Position += moveVec;
}
