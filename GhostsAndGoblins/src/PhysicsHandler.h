#pragma once
#include <list>

class Scene;
class Collider;
class PhysicsBody;

class PhysicsHandler final
{
public:
	PhysicsHandler(Scene* scene);
	~PhysicsHandler();

	void UpdatePhysics(float deltaTime);
	
	void DrawColliders() const;

	void AddCollider(Collider* collider);
	void AddPhysicsBody(PhysicsBody* physicsBody);

	void RemoveCollider(Collider* collider);
	void RemovePhysicsBody(PhysicsBody* physicsBody);

private:
	std::list<Collider*> m_Colliders;
	std::list<PhysicsBody*> m_PhysicsBodies;

	Scene* m_pScene;

	void HandleCollisions();
	void ApplyVelocity(float deltaTime);
};

