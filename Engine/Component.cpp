#include "pch.h"
#include "Component.h"

Component::Component(Entity* parent)
	: m_pParent{parent}
{
}

Entity* Component::GetParent() const
{
	return m_pParent;
}

void Component::Initialize()
{
}

void Component::Update(float deltaTime)
{
}

void Component::Draw() const
{
}
