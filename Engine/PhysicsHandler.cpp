#include "pch.h"

#include <iostream>

#include "PhysicsHandler.h"
#include "Transform.h"
#include "Collider.h"
#include "PhysicsBody.h"
#include "collisions.h"

void PhysicsHandler::Update(float deltaTime)
{
	ResolveCollisions(deltaTime);

	// Apply Velocity
	for (PhysicsBody* currentPhysicsBody : m_PhysicsBodies)
	{
		currentPhysicsBody->GetTransform()->MovePosition(currentPhysicsBody->GetVelocity() * deltaTime);
	}

	NotifyColliders(deltaTime);
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

std::pair<bool, Collider*> PhysicsHandler::Linecast(Vector2f p1, Vector2f p2)
{
	return Linecast(p1, p2, "");
}

std::pair<bool, Collider*> PhysicsHandler::Linecast(Vector2f p1, Vector2f p2, std::string tag)
{
	for (Collider* currentCollider : m_Colliders)
	{
		if (collisions::IntersectLinePolygon(p1, p2, currentCollider->GetTransformedVertices()))
		{
			// Check if tag of hit object is correct
			// or we're not checking for tag
			if (tag == "" || currentCollider->CompareTag(tag))
			{
				return std::make_pair(true, currentCollider);
			}
		}
	}
	return std::make_pair(false, nullptr);
}

void PhysicsHandler::ResolveCollisions(float deltaTime)
{
	for (PhysicsBody* physicsBody : m_PhysicsBodies)
	{
		for (Collider* collider : m_Colliders)
		{
			if (physicsBody->GetCollider()->GetParent() == collider->GetParent()) continue;

			collisions::CollisionHitInfo currentCollision = collisions::IntersectPolygons(
				physicsBody->GetCollider()->GetTransformedVertices(),
				collider->GetTransformedVertices()
			);

			if (currentCollision.hit)
			{
				if (physicsBody->GetCollider()->IsTrigger() || collider->IsTrigger()) continue;

				// resolve collision by just pushing position back with normal
				physicsBody->GetTransform()->MovePosition(-currentCollision.normal * currentCollision.depth);
			}
		}
	}
}

void PhysicsHandler::NotifyColliders(float deltaTime)
{
	for (PhysicsBody* physicsBody : m_PhysicsBodies)
	{
		for (Collider* collider : m_Colliders)
		{
			if (physicsBody->GetCollider()->GetParent() == collider->GetParent()) continue;

			std::pair currentCollisionPair = std::make_pair(physicsBody, collider);

			// Find current collision state
			collisions::CollisionHitInfo currentCollision = collisions::IntersectPolygons(
				physicsBody->GetCollider()->GetTransformedVertices(),
				collider->GetTransformedVertices()
			);

			bool currentlyColliding = currentCollision.hit;
			bool collidedLastFrame = m_LastFrameCollisions[currentCollisionPair];

			// Check collision state (against set data from last frame)
			if (!collidedLastFrame && currentlyColliding)
			{
				physicsBody->GetCollider()->OnCollisionEnter(collider, deltaTime);
				collider->OnCollisionEnter(physicsBody->GetCollider(), deltaTime);
			}
			else if (collidedLastFrame && currentlyColliding)
			{
				physicsBody->GetCollider()->OnCollisionUpdate(collider, deltaTime);
				collider->OnCollisionUpdate(physicsBody->GetCollider(), deltaTime);
			}
			else if (collidedLastFrame && !currentlyColliding)
			{
				physicsBody->GetCollider()->OnCollisionExit(collider, deltaTime);
				collider->OnCollisionExit(physicsBody->GetCollider(), deltaTime);
			}

			// Set collision state data for next frame
			m_LastFrameCollisions[currentCollisionPair] = currentlyColliding;

		}
	}
}
