#pragma once
#include <Camera.h>

class MoveZoomCamera :
    public Camera
{
public:
    MoveZoomCamera(float initialScale);
    void Update(float deltaTime) override;
};

