#pragma once
#include "Vector2f.h"

class Game;
class EntityKeeper;
class Camera;

class Scene
{
public:
	explicit Scene(Game* game, Camera* camera);
	Scene(const Scene& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(Scene&& other) = delete;
	virtual ~Scene();

	void Update(float deltaTime);
	virtual void UpdateScene(float deltaTime) = 0;

	void Draw() const;
	virtual void DrawUI() const = 0;
	virtual void DrawScene() const = 0;

protected:
	Game* m_pGame;

	EntityKeeper* m_pEntityKeeper;
	Camera* m_pCamera;
};
