#pragma once
#include "Vector2f.h"

class Camera
{
public:
	Camera(Point2f initialPos, float initialScale);
	Camera(const Camera& other) = delete;
	Camera& operator=(const Camera& other) = delete;
	Camera(Camera&& other) = delete;
	Camera& operator=(Camera&& other) = delete;

	void Update(float deltaTime);
	void Draw() const;

	Point2f GetPosition() const;
	void SetPosition(Point2f newPosition);
	void MovePosition(Vector2f moveVec);
private:
	Point2f m_Position;
	float m_Scale;
};

