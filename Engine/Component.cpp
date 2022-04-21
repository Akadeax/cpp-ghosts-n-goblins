#include "pch.h"

#include "Component.h"
#include "Entity.h"
#include "Scene.h"

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

PhysicsHandler* Component::GetPhysicsHandler()
{
	return m_pParent->GetScene()->GetPhysicsHandler();
}
