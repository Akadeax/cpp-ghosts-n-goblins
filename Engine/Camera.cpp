#include "pch.h"

#include "Camera.h"
#include <SDL.h>
#include "Vector2f.h"

Camera::Camera(float initialScale)
	: m_Scale{initialScale}
{
}

Vector2f Camera::GetPosition() const
{
	return m_Position;
}

void Camera::SetPosition(Vector2f newPos)
{
	m_Position = newPos;
}

void Camera::MovePosition(Vector2f moveBy)
{
	m_Position += moveBy;
}

void Camera::Update(float deltaTime)
{
}

void Camera::Draw() const
{
	glScalef(m_Scale, m_Scale, 0);

	glTranslatef(-m_Position.x, -m_Position.y, 0);
}
