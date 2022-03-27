#include "pch.h"

#include "TransformComponent.h"
#include <iostream>
#include "Component.h"

TransformComponent::TransformComponent(Entity* parent, Point2f startingPos)
	: Component(Component::Type::Transform, parent),
	m_Position{ startingPos } 
{
}

TransformComponent::~TransformComponent()
{
}

Point2f TransformComponent::GetPosition() const
{
	return m_Position;
}

void TransformComponent::SetPosition(Point2f newPos)
{
	m_Position = newPos;
}

void TransformComponent::MovePosition(Vector2f moveVec)
{
	m_Position += moveVec;
}

