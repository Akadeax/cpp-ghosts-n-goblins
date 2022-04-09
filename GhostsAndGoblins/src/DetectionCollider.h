#pragma once
#include "Collider.h"

class DetectionCollider :
    public Collider
{
public:
    DetectionCollider(Entity* entity, Vector2f offset, Vector2f size);

    void OnCollisionEnter(Collider* other, float deltaTime) override;
    void OnCollisionUpdate(Collider* other, float deltaTime) override;
    void OnCollisionExit(Collider* other, float deltaTime) override;
};