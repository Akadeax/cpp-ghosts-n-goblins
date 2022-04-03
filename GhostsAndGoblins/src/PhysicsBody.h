#pragma once
#include "Component.h"

class Collider;

class PhysicsBody final
    : public Component
{
public:
    PhysicsBody(Entity* entity);
    ~PhysicsBody();
    void Initialize() override;

    Collider* GetCollider() const;

private:
    Collider* m_Collider;
};