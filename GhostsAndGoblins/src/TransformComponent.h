#pragma once
#include "structs.h"
#include "Vector2f.h"
#include "Component.h"

class Entity;

class TransformComponent final
	: public Component
{
public:
	TransformComponent(Entity* parent, Point2f startingPos);
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&&) = delete;
	TransformComponent& operator=(TransformComponent&&) = delete;

	~TransformComponent();

	Point2f GetPosition() const;

	void SetPosition(Point2f newPos);
	void MovePosition(Vector2f moveVec);

private:
	Point2f m_Position;
};

