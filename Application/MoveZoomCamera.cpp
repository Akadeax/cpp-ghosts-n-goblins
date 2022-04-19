#include <pch.h>

#include <SDL.h>

#include "MoveZoomCamera.h"

MoveZoomCamera::MoveZoomCamera(float initialScale)
	: Camera(initialScale)
{
}

void MoveZoomCamera::Update(float deltaTime)
{
	const Uint8* state = SDL_GetKeyboardState(nullptr);

	float moveAmount = 200 * deltaTime;
	if (state[SDL_SCANCODE_UP])
	{
		MovePosition(Vector2f(0, moveAmount));
	}
	else if (state[SDL_SCANCODE_DOWN])
	{
		MovePosition(Vector2f(0, -moveAmount));
	}

	if (state[SDL_SCANCODE_RIGHT])
	{
		MovePosition(Vector2f(moveAmount, 0));
	}
	else if (state[SDL_SCANCODE_LEFT])
	{
		MovePosition(Vector2f(-moveAmount, 0));
	}

	float zoomAmount = 10 * deltaTime;
	if (state[SDL_SCANCODE_K] && m_Scale < 10)
	{
		m_Scale += zoomAmount;
	}
	else if (state[SDL_SCANCODE_J] && m_Scale > 0.5f)
	{
		m_Scale -= zoomAmount;
	}
}
