#pragma once
#include "Component.h"
#include "Vector2f.h"

class Collider;
class Transform;

class PhysicsBody final
    : public Component
{
public:
    PhysicsBody(Entity* entity);
    ~PhysicsBody();
    void Initialize() override;

    Transform* GetTransform();
    Collider* GetCollider() const;

    Vector2f GetVelocity() const;
    void SetVelocity(Vector2f velocity);
    void SetXVelocity(float x);
    void SetYVelocity(float y);
    void AddVelocity(Vector2f velocity);

private:
    Transform* m_Transform = nullptr;
    Collider* m_Collider = nullptr;
    
    Vector2f m_Velocity = Vector2f(0, 0);
};