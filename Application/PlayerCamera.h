#pragma once
#include <Camera.h>

class Transform;

class PlayerCamera :
    public Camera
{
public:
    PlayerCamera(Transform* followTarget);

    void Update(float deltaTime) override;

    void SetFollowTarget(Transform* target);

private:
    Transform* m_pFollowTarget;

    const float m_LeftBoundary{ 0.f };
    const float m_RightBoundary{ 3580.f };
};

