#include "pch.h"

#include "Transform.h"
#include "Component.h"


Transform::Transform(Entity* parent, Vector2f startingPos)
	: Component(parent), m_Position{startingPos}
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

float Transform::GetScale() const
{
	return m_Scale;
}

void Transform::SetScale(float newScale)
{
	m_Scale = newScale;
}

float Transform::GetRotation() const
{
	return m_RotationAngleDegrees;
}

void Transform::SetRotation(float newRotation)
{
	m_RotationAngleDegrees = newRotation;
}

void Transform::Rotate(float rotateBy)
{
	m_RotationAngleDegrees += rotateBy;
}
