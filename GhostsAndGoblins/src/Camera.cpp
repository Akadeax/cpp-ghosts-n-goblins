#include "pch.h"

#include "Camera.h"
#include <algorithm>
#include <iostream>
Camera::Camera(Vector2f initialPos, float initialScale)
{
	m_Position = initialPos;
	m_Scale = initialScale;
}

void Camera::Update(float deltaTime)
{
	if (m_pFollowTransform == nullptr) return;

	Vector2f followPos = m_pFollowTransform->GetPosition();
	m_Position = Vector2f(std::clamp((followPos.x * m_Scale) + m_FollowOffset, m_LeftBound / 2, m_RightBound), 0);
	std::cout << followPos.x << ", " << m_Position.x << ", " << std::clamp(followPos.x, m_LeftBound / 2, m_RightBound) << std::endl;
	//const Uint8* state = SDL_GetKeyboardState(nullptr);

	//float moveVal = 200 * deltaTime;
	//if (state[SDL_SCANCODE_UP])
	//{
	//	MovePosition(Vector2f(0, moveVal));
	//}
	//else if (state[SDL_SCANCODE_DOWN])
	//{
	//	MovePosition(Vector2f(0, -moveVal));
	//}

	//if (state[SDL_SCANCODE_RIGHT])
	//{
	//	MovePosition(Vector2f(moveVal, 0));
	//}
	//else if (state[SDL_SCANCODE_LEFT])
	//{
	//	MovePosition(Vector2f(-moveVal, 0));
	//}
}

void Camera::Draw() const
{
	glTranslatef(-m_Position.x, -m_Position.y, 0);
	glScalef(m_Scale, m_Scale, 0);
}

Vector2f Camera::GetPosition() const
{
	return m_Position;
}

void Camera::SetPosition(Vector2f newPosition)
{
	m_Position = newPosition;
}

void Camera::MovePosition(Vector2f moveVec)
{
	m_Position += moveVec;
}

void Camera::SetFollowTarget(Transform* transform)
{
	m_pFollowTransform = transform;
}
