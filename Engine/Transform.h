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

	float GetScale() const;
	void SetScale(float newScale);

	float GetRotation() const;
	void SetRotation(float newRotation);
	void Rotate(float rotateBy);

private:
	Vector2f m_Position = Vector2f(0, 0);
	float m_Scale = 1.f;
	float m_RotationAngleDegrees = 0.f;
};
