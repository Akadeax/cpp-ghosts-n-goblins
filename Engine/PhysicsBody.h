#pragma once
#include <list>
#include "Component.h"
#include "Vector2f.h"

class Transform;
class Collider;
class PhysicsHandler;

class PhysicsBody :
    public Component
{
public:
	explicit PhysicsBody(Entity* parent);
	PhysicsBody& operator=(const PhysicsBody & rhs) = delete;
	PhysicsBody& operator=(PhysicsBody && rhs) = delete;
	PhysicsBody(const PhysicsBody & rhs) = delete;
	PhysicsBody(PhysicsBody && rhs) = delete;
	virtual ~PhysicsBody();

	void Initialize() override;

	Transform* GetTransform() const;
	Collider* GetCollider() const;

	Vector2f GetVelocity() const;
	void SetVelocity(Vector2f velocity);
	void SetXVelocity(float x);
	void SetYVelocity(float y);
	void AddVelocity(Vector2f velocity);

private:
    Transform* m_pTransform{ nullptr };
    Collider* m_pCollider{ nullptr };

	Vector2f m_Velocity{ Vector2f() };
};

