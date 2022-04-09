#pragma once
#include "Vector2f.h"
#include "Component.h"

class Entity;

class Transform final
	: public Component
{
public:
	Transform(Entity* parent, Vector2f startingPos);
	Transform& operator=(const Transform& other) = delete;
	Transform(const Transform& other) = delete;
	Transform(Transform&&) = delete;
	Transform& operator=(Transform&&) = delete;

	~Transform();

	Vector2f GetPosition() const;

	void SetPosition(Vector2f newPos);
	void MovePosition(Vector2f moveVec);

	void SetScale(float newScale);
	float GetScale() const;

private:
	Vector2f m_Position = Vector2f(0, 0);
	float m_Scale = 1;
};
