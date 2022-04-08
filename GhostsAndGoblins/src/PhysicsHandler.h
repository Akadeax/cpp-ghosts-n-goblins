#pragma once
#include <list>
#include "Vector2f.h"

class Scene;
class Collider;
class PhysicsBody;

class PhysicsHandler final
{
public:
	PhysicsHandler(Scene* scene);
	~PhysicsHandler();

	void UpdatePhysics(float deltaTime);
	
	void DebugDrawColliders() const;

	void AddCollider(Collider* collider);
	void AddPhysicsBody(PhysicsBody* physicsBody);

	void RemoveCollider(Collider* collider);
	void RemovePhysicsBody(PhysicsBody* physicsBody);

	std::pair<bool, Collider*> Linecast(Vector2f p1, Vector2f p2);
	std::pair<bool, Collider*> Linecast(Vector2f p1, Vector2f p2, std::string tag);

private:
	std::list<Collider*> m_Colliders;
	std::list<PhysicsBody*> m_PhysicsBodies;

	Scene* m_pScene;
};

