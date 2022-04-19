#pragma once
#include <SDL.h>
#include <unordered_map>
#include <map>
#include "Vector2f.h"

class InputHandler
{
public:
	explicit InputHandler() = default;
	InputHandler& operator=(const InputHandler& rhs) = delete;
	InputHandler& operator=(InputHandler&& rhs) = delete;
	InputHandler(const InputHandler& rhs) = delete;
	InputHandler(InputHandler&& rhs) = delete;
	virtual ~InputHandler() = default;

	void AddKey(std::string inputName, SDL_Scancode scancode);

	bool GetKeyDown(std::string key);
	bool GetKeyPressed(std::string key);
	bool GetKeyUp(std::string key);

	void Update();

private:
	// Keyboard
	std::map<std::string, SDL_Scancode> m_Keys;

	std::unordered_map<SDL_Scancode, bool> m_KeyDown;
	std::unordered_map<SDL_Scancode, bool> m_KeyPressed;
	std::unordered_map<SDL_Scancode, bool> m_KeyUp;

	std::unordered_map<SDL_Scancode, bool> m_PressedLastFrame;
};

