#pragma once
#include "Component.h"
#include "Vector2f.h"

class Transform;
class RectCollider;

class Collider :
    public Component
{
public:
    Collider(Entity* entity, Vector2f offset, Vector2f size);
    ~Collider();
    void Initialize() override;

    virtual void CollidingUpdate(Collider* other, float deltaTime);
    virtual void NotCollidingUpdate(float deltaTime);

    void DrawCollider() const;

    Vector2f GetOffset() const;
    Vector2f GetSize() const;
    Transform* GetTransform();
    bool CompareTag(std::string tag) const;

    void SetTrigger(bool newVal);
    bool IsTrigger() const;

    bool IsAABBCollidingWith(const Collider* other, Vector2f vel) const;
    Vector2f CalculateAABBDistanceTo(const Collider* other) const;

    Vector2f GetBottomLeftPosition() const;

protected:
    bool m_IsTrigger = false;
    Transform* m_pTransform = nullptr;

    Vector2f m_Offset;
    Vector2f m_Size;
};
