#include "pch.h"

#include <iostream>
#include "PhysicsHandler.h"
#include "Transform.h"
#include "Collider.h"
#include "PhysicsBody.h"
#include "utils.h"

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

void PhysicsHandler::UpdatePhysics(float deltaTime)
{
	HandleCollisions();
	ApplyVelocity(deltaTime);
}

void PhysicsHandler::DrawColliders() const
{
	for (Collider* coll : m_Colliders)
	{
		coll->DrawCollider();
	}
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

void PhysicsHandler::HandleCollisions()
{
	for (PhysicsBody* currentPhysicsBody : m_PhysicsBodies)
	{
		for (Collider* currentCollider : m_Colliders)
		{
			if (currentPhysicsBody->GetCollider() == currentCollider) continue;

			if (currentPhysicsBody->GetCollider()->Intersecting(currentCollider))
			{
				std::cout << "Colliding!" << std::endl;
			}
		}
	}
}

void PhysicsHandler::ApplyVelocity(float deltaTime)
{
	for (PhysicsBody* currentPhysicsBody : m_PhysicsBodies)
	{
		Vector2f moveBy = currentPhysicsBody->GetVelocity() * deltaTime;
		currentPhysicsBody->GetTransform()->MovePosition(moveBy);
		// Apply gravity
		currentPhysicsBody->AddVelocity(Vector2f(0, -10 * deltaTime));
	}
}
