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

    const float GROUNDED_CHECK_Y_OFFSET = -14.f;
    const float GROUNDED_CHECK_X_SIZE = 22.f;
    float m_GravityFactor = 1.f;

    bool m_IsGrounded = false;
    // TODO: Refactor into input manager
    bool m_SpaceLastFrame = false;
};