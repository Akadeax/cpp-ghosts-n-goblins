#pragma once

class Game;
class EntityManager;
class Camera;

class Entity;

class Scene final
{
public:
	Scene(Game* game);
	~Scene();

	void Initialize();
	void Update(float deltaTime);
	void Draw() const;

	EntityManager* GetEntityManager() const;
	Camera* GetCamera() const;

private:
	// Handlers
	Game* m_pGame;

	EntityManager* m_pEntityManager = nullptr;
	Camera* m_pCamera = nullptr;

	// Persistent Entities
	Entity* m_pPlayer = nullptr;
	void CreatePlayer();
};
