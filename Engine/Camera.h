#pragma once
#include "Vector2f.h"
class Camera
{
public:
	Camera(float initialScale);
	Camera(const Camera& other) = delete;
	Camera& operator=(const Camera& other) = delete;
	Camera(Camera&& other) = delete;
	Camera& operator=(Camera&& other) = delete;
	virtual ~Camera();

	Vector2f GetPosition() const;
	void SetPosition(Vector2f newPos);
	void MovePosition(Vector2f moveBy);

	virtual void Update(float deltaTime);
	virtual void Draw() const;

protected:
	Vector2f m_Position;
	float m_Scale;
};

