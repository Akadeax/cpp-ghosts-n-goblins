#include "pch.h"

#include "Component.h"

Component::Component(Type type, Entity* parent)
{
	m_Type = type;
	m_pParent = parent;
}

Component::~Component()
{
}

Entity* Component::GetParent() const
{
	return m_pParent;
}

Component::Type Component::GetType() const
{
	return m_Type;
}

void Component::Update(float deltaTime) {}

void Component::Draw() const {}
