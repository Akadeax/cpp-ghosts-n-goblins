#include "pch.h"

#include "InputHandler.h"
#include <iostream>

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::AddKey(std::string inputName, SDL_Scancode scancode)
{
	m_Keys[inputName] = scancode;
}

// Over-aggressive compiler warning that discourages
// the C-Style enums used by SDL
#pragma warning( disable: 26812 )
bool InputHandler::GetKeyDown(std::string key)
{
	return m_KeyDown[m_Keys[key]];
}

bool InputHandler::GetKeyPressed(std::string key)
{
	return m_KeyPressed[m_Keys[key]];
}

bool InputHandler::GetKeyUp(std::string key)
{
	return m_KeyUp[m_Keys[key]];
}

void InputHandler::Update()
{
	// Keyboard
	const Uint8* state = SDL_GetKeyboardState(nullptr);

	for (auto& inputPair : m_Keys)
	{
		bool currentlyPressed = state[inputPair.second];
		bool pressedLastFrame = m_PressedLastFrame[inputPair.second];

		// reset all values so we can set them for this frame
		m_KeyDown[inputPair.second] = false;
		m_KeyPressed[inputPair.second] = false;
		m_KeyUp[inputPair.second] = false;

		if (currentlyPressed && !pressedLastFrame)
		{
			m_KeyDown[inputPair.second] = true;
		}
		else if (currentlyPressed && pressedLastFrame)
		{
			m_KeyPressed[inputPair.second] = true;
		}
		else if (!currentlyPressed && pressedLastFrame)
		{
			m_KeyUp[inputPair.second] = true;
		}

		m_PressedLastFrame[inputPair.second] = currentlyPressed;
	}
}

