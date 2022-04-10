#pragma once
#include "Component.h"

class AnimatorRenderer;
class Transform;
class PhysicsBody;
class Entity;

class Player :
    public Component
{
public:
    Player(Entity* entity);
    void Initialize() override;
    void Update(float deltaTime) override;
    void Draw() const override;

private:
    AnimatorRenderer* m_Animator = nullptr;
    Transform* m_Transform = nullptr;
    PhysicsBody* m_PhysicsBody = nullptr;

    const float GROUNDED_CHECK_Y_OFFSET = -13.f;
    const float GROUNDED_CHECK_X_SIZE = 25.f;

    float m_GravityFactor = 2.f;
    float m_MoveSpeed = 80.f;
    float m_JumpStrength = 210.f;

    bool m_IsGrounded = false;
};
