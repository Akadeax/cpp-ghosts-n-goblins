#pragma once
#include <SDL.h>
#include <unordered_map>

class InputHandler
{
public:
	InputHandler();

	enum class Input
	{
		WalkLeft, WalkRight, Jump, Shoot
	};

	bool GetKeyDown(Input key);
	bool GetKeyPressed(Input key);
	bool GetKeyUp(Input key);

	void Update();

private:
	std::unordered_map<Input, SDL_Scancode> m_Keys;

	std::unordered_map<Input, bool> m_KeyDown;
	std::unordered_map<Input, bool> m_KeyPressed;
	std::unordered_map<Input, bool> m_KeyUp;

	std::unordered_map<Input, bool> m_PressedLastFrame;
};

