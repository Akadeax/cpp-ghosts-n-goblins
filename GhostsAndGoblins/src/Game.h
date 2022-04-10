#pragma once
#include <SDL.h>
#include "InputHandler.h"

class Entity;
class Scene;
class TextureCache;

class Game final
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update(float elapsedSec);
	void Draw() const;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

	TextureCache* GetTextureCache();
	InputHandler* GetInputHandler();

private:
	// DATA MEMBERS
	const Window m_Window;
	TextureCache* m_pTextureCache;
	InputHandler* m_pInputHandler;
	Scene* m_pScene;

	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;
};
