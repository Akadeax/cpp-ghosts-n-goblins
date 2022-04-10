#pragma once
#include "Vector2f.h"
#include "Transform.h"

class Camera
{
public:
	Camera(Vector2f initialPos, float initialScale);
	Camera(const Camera& other) = delete;
	Camera& operator=(const Camera& other) = delete;
	Camera(Camera&& other) = delete;
	Camera& operator=(Camera&& other) = delete;

	void Update(float deltaTime);
	void Draw() const;

	Vector2f GetPosition() const;
	void SetPosition(Vector2f newPosition);
	void MovePosition(Vector2f moveVec);
	
	void SetFollowTarget(Transform* transform);

private:
	Transform* m_pFollowTransform = nullptr;
	float m_FollowOffset = -450;

	Vector2f m_Position = Vector2f(0, 0);
	float m_Scale = 1.f;

	float m_LeftBound = 0;
	float m_RightBound = 10000.f;
};

