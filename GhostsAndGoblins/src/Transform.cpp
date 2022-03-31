#include "pch.h"

#include "Transform.h"
#include <iostream>
#include "Component.h"


Transform::Transform(Entity* parent)
	: Component(parent)
{
}

Transform::~Transform()
{
}

Point2f Transform::GetPosition() const
{
	return m_Position;
}

void Transform::SetPosition(Point2f newPos)
{
	m_Position = newPos;
}

void Transform::MovePosition(Vector2f moveVec)
{
	m_Position += moveVec;
}

void Transform::SetScale(float newScale)
{
	m_Scale = newScale;
}

float Transform::GetScale() const
{
	return m_Scale;
}

