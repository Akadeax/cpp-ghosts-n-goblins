#pragma once
#include "Vector2f.h"

class Game;
class EntityKeeper;
class Camera;

class Scene
{
public:
	explicit Scene() = default;
	Scene& operator=(const Scene& rhs) = delete;
	Scene& operator=(Scene&& rhs) = delete;
	Scene(const Scene& rhs) = delete;
	Scene(Scene&& rhs) = delete;
	virtual ~Scene();

	void Initialize(Game* game, Camera* camera);
	virtual void InitializeScene() = 0;

	void Update(float deltaTime);
	virtual void UpdateScene(float deltaTime) = 0;

	void Draw() const;
	virtual void DrawUI() const = 0;
	virtual void DrawScene() const = 0;

	Game* GetGame() const;
	Camera* GetCamera() const;

protected:
	Game* m_pGame{ nullptr };

	EntityKeeper* m_pEntityKeeper{ nullptr };
	Camera* m_pCamera{ nullptr };
};
