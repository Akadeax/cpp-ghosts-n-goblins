#pragma once
#include <SDL.h>
#include "structs.h"

class InputHandler;
class Scene;

class Game
{
public:
	explicit Game(const Window& window, Scene* scene);
	Game& operator=(const Game& rhs) = delete;
	Game& operator=(Game&& rhs) = delete;
	Game(const Game& rhs) = delete;
	Game(Game&& rhs) = delete;
	~Game();

	void Update(float deltaTime);
	virtual void UpdateGame(float deltaTime) = 0;

	void Draw() const;

	Window GetWindow();
	InputHandler* GetInputHandler();
	Scene* GetScene();

protected:
	const Window m_Window;

	InputHandler* m_pInputHandler{ nullptr };
	Scene* m_pScene{ nullptr };
};

