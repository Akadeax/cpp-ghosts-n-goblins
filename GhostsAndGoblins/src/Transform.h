#pragma once
#include "structs.h"
#include "Vector2f.h"
#include "Component.h"

class Entity;

class Transform final
	: public Component
{
public:
	Transform(Entity* parent);
	Transform& operator=(const Transform& other) = delete;
	Transform(const Transform& other) = delete;
	Transform(Transform&&) = delete;
	Transform& operator=(Transform&&) = delete;

	~Transform();

	Point2f GetPosition() const;

	void SetPosition(Point2f newPos);
	void MovePosition(Vector2f moveVec);

	void SetScale(float newScale);
	float GetScale() const;

private:
	Point2f m_Position = Point2f(0, 0);
	float m_Scale = 1;
};

