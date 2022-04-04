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
    virtual ~Collider();
    void Initialize() override;

    bool Intersecting(const Collider* other) const;

    virtual void OnCollisionUpdate(Collider* other, float deltaTime);
    virtual void DrawCollider() const = 0;

    Type GetType() const;

protected:
    bool m_IsTrigger = false;
    Transform* m_pTransform = nullptr;

    virtual bool IntersectingRect(const RectCollider* other) const = 0;

private:
    Type m_Type;
};
