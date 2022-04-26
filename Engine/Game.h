#pragma once
#include <SDL.h>

#include "structs.h"
#include "json.hpp"

class InputHandler;
class Scene;
class TextureCache;

class Game
{
public:
	explicit Game(Scene* scene);
	Game& operator=(const Game& rhs) = delete;
	Game& operator=(Game&& rhs) = delete;
	Game(const Game& rhs) = delete;
	Game(Game&& rhs) = delete;
	~Game();

	void Update(float deltaTime);
	virtual void UpdateGame(float deltaTime) = 0;

	void Draw() const;

	InputHandler* GetInputHandler() const;
	Scene* GetScene() const;
	TextureCache* GetTextureCache() const;

	nlohmann::json LoadJsonFile(std::string file);

	void LoadScene(Scene* newScene);

protected:
	InputHandler* m_pInputHandler{ nullptr };
	Scene* m_pScene{ nullptr };
	TextureCache* m_pTextureCache{ nullptr };
};

