#pragma once
#include <list>
#include <map>
#include "Vector2f.h"

class Collider;
class PhysicsBody;

class PhysicsHandler
{
public:
	explicit PhysicsHandler() = default;
	PhysicsHandler& operator=(const PhysicsHandler & rhs) = delete;
	PhysicsHandler& operator=(PhysicsHandler && rhs) = delete;
	PhysicsHandler(const PhysicsHandler & rhs) = delete;
	PhysicsHandler(PhysicsHandler && rhs) = delete;
	virtual ~PhysicsHandler() = default;

	void Update(float deltaTime);

	void AddCollider(Collider* collider);
	void AddPhysicsBody(PhysicsBody* physicsBody);

	void RemoveCollider(Collider* collider);
	void RemovePhysicsBody(PhysicsBody* physicsBody);

	std::pair<bool, Collider*> Linecast(Vector2f p1, Vector2f p2);
	std::pair<bool, Collider*> Linecast(Vector2f p1, Vector2f p2, std::string tag);

private:
	std::list<Collider*> m_Colliders;
	std::list<PhysicsBody*> m_PhysicsBodies;

	std::map<std::pair<PhysicsBody*, Collider*>, bool> m_LastFrameCollisions;

	void ResolveCollisions(float deltaTime);
	void NotifyColliders(float deltaTime);
};

