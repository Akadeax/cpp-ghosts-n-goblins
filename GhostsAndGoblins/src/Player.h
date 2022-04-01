#pragma once
#include "Component.h"

class AnimatorRenderer;
class Transform;
class Entity;

class Player :
    public Component
{
public:
    Player(Entity* parent);
    void Update(float deltaTime) override;

private:
    AnimatorRenderer* m_Animator;
    Transform* m_Transform;
};

