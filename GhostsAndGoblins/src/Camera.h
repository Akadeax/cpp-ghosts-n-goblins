#pragma once
#include "Vector2f.h"

class Camera
{
public:
	void Update(float deltaTime);
	void Draw() const;

	Point2f GetPosition() const;
	void SetPosition(Point2f newPosition);
	void MovePosition(Vector2f moveVec);
private:
	Point2f m_Position;
};

