#include "pch.h"

#include "InputHandler.h"
#include <iostream>

// Harmless warning caused by SDL tomfoolery
#pragma warning( disable: 26812 )
InputHandler::InputHandler()
{
	m_Keys[Input::WalkLeft] = (SDL_Scancode)SDL_SCANCODE_A;
	m_Keys[Input::WalkRight] = SDL_SCANCODE_D;
	m_Keys[Input::Jump] = SDL_SCANCODE_SPACE;
	m_Keys[Input::Shoot] = SDL_SCANCODE_F;
}

bool InputHandler::GetKeyDown(Input key)
{
	return m_KeyDown[key];
}

bool InputHandler::GetKeyPressed(Input key)
{
	return m_KeyPressed[key];
}

bool InputHandler::GetKeyUp(Input key)
{
	return m_KeyUp[key];
}

void InputHandler::Update()
{
	const Uint8* state = SDL_GetKeyboardState(nullptr);

	for (auto& inputPair : m_Keys)
	{
		bool currentlyPressed = state[inputPair.second];
		bool pressedLastFrame = m_PressedLastFrame[inputPair.first];

		// reset all values so we can set them accordingly
		m_KeyDown[inputPair.first] = false;
		m_KeyPressed[inputPair.first] = false;
		m_KeyUp[inputPair.first] = false;

		if (currentlyPressed && !pressedLastFrame)
		{
			m_KeyDown[inputPair.first] = true;
		}
		else if (currentlyPressed && pressedLastFrame)
		{
			m_KeyPressed[inputPair.first] = true;
		}
		else if (!currentlyPressed && pressedLastFrame)
		{
			m_KeyUp[inputPair.first] = true;
		}

		m_PressedLastFrame[inputPair.first] = currentlyPressed;
	}
}
