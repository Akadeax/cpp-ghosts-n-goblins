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

private:
    AnimatorRenderer* m_Animator = nullptr;
    Transform* m_Transform = nullptr;
    PhysicsBody* m_PhysicsBody = nullptr;
};

