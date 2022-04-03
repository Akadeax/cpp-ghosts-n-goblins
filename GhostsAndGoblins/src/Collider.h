#pragma once
#include "Component.h"

class Transform;
class RectCollider;

class Collider :
    public Component
{
public:
    enum class Type
    {
        Rect
    };

    Collider(Entity* entity, Type type);
    void Initialize() override;

    bool Intersecting(Collider* other) const;

    virtual void OnCollisionUpdate(Collider* other, float deltaTime);

    Type GetType() const;

protected:
    bool m_IsTrigger = false;
    Transform* m_Transform;

    virtual bool IntersectingRect(RectCollider* other) const = 0;

private:
    Type m_Type;
};
