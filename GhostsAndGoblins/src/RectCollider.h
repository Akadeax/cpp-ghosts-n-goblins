#pragma once
#include "Collider.h"
#include "Vector2f.h"

class RectCollider :
    public Collider
{
public:
    RectCollider(Entity* entity, Vector2f offset, Vector2f size);

    Vector2f GetOffset() const;
    Vector2f GetSize() const;

protected:
    Vector2f m_Offset;
    Vector2f m_Size;

    bool IntersectingRect(RectCollider* other) const override;
};
