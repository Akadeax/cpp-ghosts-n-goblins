#include "pch.h"

#include "Transform.h"
#include <iostream>
#include "Component.h"


Transform::Transform(Entity* parent, Point2f startingPos)
	: Component(parent),
	m_Position{ startingPos } 
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

