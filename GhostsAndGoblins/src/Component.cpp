#include "pch.h"

#include "Component.h"

Component::Component(std::string type, Entity* parent)
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

std::string Component::GetType() const
{
	return m_Type;
}

void Component::Update(float deltaTime) {}

void Component::Draw() const {}
