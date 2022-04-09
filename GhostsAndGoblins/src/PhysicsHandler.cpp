#include "pch.h"

#include <iostream>
#include "PhysicsHandler.h"
#include "Transform.h"
#include "Collider.h"
#include "PhysicsBody.h"
#include "utils.h"
#include "collisions.h"
#include "Entity.h"

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
	for (PhysicsBody* currentPhysicsBody : m_PhysicsBodies)
	{
		for (Collider* currentCollider : m_Colliders)
		{
			if (currentPhysicsBody->GetCollider() == currentCollider) continue;

			// physics body and collider are colliding
			if (currentPhysicsBody->GetCollider()->IsAABBCollidingWith(currentCollider, currentPhysicsBody->GetVelocity() * deltaTime))
			{
				if (currentPhysicsBody->GetCollider()->IsTrigger() || currentCollider->IsTrigger()) continue;
				
				Vector2f distance = currentPhysicsBody->GetCollider()->CalculateAABBDistanceTo(currentCollider);
				Vector2f velocity = currentPhysicsBody->GetVelocity();
				float xAxisTimeToCollide = velocity.x != 0 ? std::abs(distance.x / velocity.x) : 0;
				float yAxisTimeToCollide = velocity.y != 0 ? std::abs(distance.y / velocity.y) : 0;

				float shortestTime = 0.f;
				if (velocity.x != 0 && velocity.y == 0)
				{
					// Collision on X-Axis only
					shortestTime = xAxisTimeToCollide;
					currentPhysicsBody->SetVelocity(Vector2f(shortestTime * velocity.x * deltaTime, 0));
				}
				else if (velocity.x == 0 && velocity.y != 0)
				{
					// Collision on Y-Axis only
					shortestTime = yAxisTimeToCollide;
					currentPhysicsBody->SetVelocity(Vector2f(0, shortestTime * velocity.y * deltaTime));
				}
				else
				{
					// Collision on X- and Y-Axis (e.g. slide up against a wall)
					shortestTime = std::min(std::abs(xAxisTimeToCollide), std::abs(yAxisTimeToCollide));
					currentPhysicsBody->SetVelocity(Vector2f(
						shortestTime * velocity.x * deltaTime,
						shortestTime * velocity.y * deltaTime
					));
				}
			}
		}
		// Apply Velocity
		currentPhysicsBody->GetTransform()->MovePosition(currentPhysicsBody->GetVelocity() * deltaTime);
	}
}

void PhysicsHandler::DebugDrawColliders() const
{
	for (Collider* coll : m_Colliders)
	{
		coll->DrawCollider();
	}

	for (PhysicsBody* currentPhysicsBody : m_PhysicsBodies)
	{
		for (Collider* currentCollider : m_Colliders)
		{
			if (currentPhysicsBody->GetCollider() == currentCollider) continue;

			Vector2f distance = currentPhysicsBody->GetCollider()->CalculateAABBDistanceTo(currentCollider);
			Vector2f physicsBodyPos = currentPhysicsBody->GetTransform()->GetPosition();
			utils::DrawLine(physicsBodyPos.ToPoint2f(), (physicsBodyPos + distance).ToPoint2f(), 2);
		}
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

std::pair<bool, Collider*> PhysicsHandler::Linecast(Vector2f p1, Vector2f p2)
{
	return Linecast(p1, p2, "");
}

std::pair<bool, Collider*> PhysicsHandler::Linecast(Vector2f p1, Vector2f p2, std::string tag)
{
	for (Collider* currentCollider : m_Colliders)
	{
		Vector2f colliderBottomLeft = currentCollider->GetBottomLeftPosition();
		Vector2f colliderSize = currentCollider->GetSize();
		Rectf colliderRect = Rectf(colliderBottomLeft.x, colliderBottomLeft.y, colliderSize.x, colliderSize.y);

		if (collisions::LineRect(p1, p2, colliderRect))
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

