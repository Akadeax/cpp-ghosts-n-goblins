#include "pch.h"

#include "DetectionCollider.h"
#include <iostream>

DetectionCollider::DetectionCollider(Entity* entity, Vector2f offset, Vector2f size)
	: Collider(entity, offset, size)
{
}

void DetectionCollider::OnCollisionEnter(Collider* other, float deltaTime)
{
	std::cout << "enter" << std::endl;
}

void DetectionCollider::OnCollisionUpdate(Collider* other, float deltaTime)
{
}

void DetectionCollider::OnCollisionExit(Collider* other, float deltaTime)
{
	std::cout << "exit" << std::endl;
}