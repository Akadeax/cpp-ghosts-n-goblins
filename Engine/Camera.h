#pragma once
#include "Vector2f.h"
class Camera
{
public:
	explicit Camera(float initialScale);
	Camera& operator=(const Camera& rhs) = delete;
	Camera& operator=(Camera&& rhs) = delete;
	Camera(const Camera& rhs) = delete;
	Camera(Camera&& rhs) = delete;
	virtual ~Camera() = default;

	Vector2f GetPosition() const;
	void SetPosition(Vector2f newPos);
	void MovePosition(Vector2f moveBy);

	virtual void Update(float deltaTime);
	virtual void Draw() const;

protected:
	Vector2f m_Position;
	float m_Scale;
};

