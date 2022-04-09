#include "pch.h"

#include "Component.h"
#include "Entity.h"
#include "Scene.h"

Component::Component(Entity* parent)
{
	m_pParent = parent;
}

PhysicsHandler* Component::GetPhysicsHandler() const
{
	return m_pParent->GetScene()->GetPhysicsHandler();
}

Component::~Component()
{
}

Entity* Component::GetParent() const
{
	return m_pParent;
}

void Component::Initialize() {}

void Component::Update(float deltaTime) {}

void Component::Draw() const {}
