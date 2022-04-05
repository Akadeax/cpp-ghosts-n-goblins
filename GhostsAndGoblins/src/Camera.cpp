#include "pch.h"

#include "Camera.h"

Camera::Camera(Point2f initialPos, float initialScale)
{
	m_Position = initialPos;
	m_Scale = initialScale;
}

void Camera::Update(float deltaTime)
{
	const Uint8* state = SDL_GetKeyboardState(nullptr);

	float moveVal = 200 * deltaTime;
	if (state[SDL_SCANCODE_UP])
	{
		MovePosition(Vector2f(0, moveVal));
	}
	else if (state[SDL_SCANCODE_DOWN])
	{
		MovePosition(Vector2f(0, -moveVal));
	}

	if (state[SDL_SCANCODE_RIGHT])
	{
		MovePosition(Vector2f(moveVal, 0));
	}
	else if (state[SDL_SCANCODE_LEFT])
	{
		MovePosition(Vector2f(-moveVal, 0));
	}
}

void Camera::Draw() const
{
	glTranslatef(-m_Position.x, -m_Position.y, 0);
	glScalef(m_Scale, m_Scale, 0);
}

Point2f Camera::GetPosition() const
{
	return m_Position;
}

void Camera::SetPosition(Point2f newPosition)
{
	m_Position = newPosition;
}

void Camera::MovePosition(Vector2f moveVec)
{
	m_Position += moveVec;
}
