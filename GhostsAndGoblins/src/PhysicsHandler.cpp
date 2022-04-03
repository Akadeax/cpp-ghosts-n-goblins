#include "pch.h"

#include "PhysicsHandler.h"
#include "Collider.h"
#include "PhysicsBody.h"

PhysicsHandler::PhysicsHandler(Scene* scene)
{
	m_pScene = scene;
}

PhysicsHandler::~PhysicsHandler()
{
	for (auto& coll : m_Colliders)
	{
		delete coll;
	}
	for (auto& physicsBody : m_PhysicsBodies)
	{
		delete physicsBody;
	}
}

void PhysicsHandler::UpdateCollision()
{
}

void PhysicsHandler::AddCollider(Collider* collider)
{
	m_Colliders.push_back(collider);
}

void PhysicsHandler::AddPhysicsBody(PhysicsBody* physicsBody)
{
	m_PhysicsBodies.push_back(physicsBody);
}

void PhysicsHandler::RemoveCollider(Collider* collider)
{
	m_Colliders.remove(collider);
}

void PhysicsHandler::RemovePhysicsBody(PhysicsBody* physicsBody)
{
	m_PhysicsBodies.remove(physicsBody);
}
