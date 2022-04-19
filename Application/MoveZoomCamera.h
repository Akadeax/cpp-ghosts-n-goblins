#pragma once
#include <Camera.h>

class MoveZoomCamera final :
    public Camera
{
public:
	explicit MoveZoomCamera(float initialScale);
	MoveZoomCamera& operator=(const MoveZoomCamera& rhs) = delete;
	MoveZoomCamera& operator=(MoveZoomCamera&& rhs) = delete;
	MoveZoomCamera(const MoveZoomCamera& rhs) = delete;
	MoveZoomCamera(MoveZoomCamera&& rhs) = delete;
	virtual ~MoveZoomCamera() = default;

    void Update(float deltaTime) override;
};

