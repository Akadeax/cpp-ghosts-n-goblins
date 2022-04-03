#include "pch.h"

#include "Scene.h"
#include "EntityManager.h"
#include "Camera.h"
#include "Player.h"
#include "TextureCache.h"
#include "TextureCache.h"
#include "Entity.h"
#include "Game.h"
#include "ConditionalTransition.h"

#include "Transform.h"
#include "AnimatorRenderer.h"
#include "RectCollider.h"

#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerJumpState.h"


Scene::Scene(Game* game)
{
	m_pGame = game;

}

Scene::~Scene()
{
	delete m_pEntityManager;
	delete m_pCamera;
}

void Scene::Initialize()
{

	m_pEntityManager = new EntityManager();
	m_pCamera = new Camera(Point2f(-60, -60), 5);

	CreatePlayer();
}

void Scene::Update(float deltaTime)
{
	m_pEntityManager->UpdateEntities(deltaTime);
}

void Scene::Draw() const
{
	m_pCamera->Draw();
	m_pEntityManager->DrawEntities();
}

EntityManager* Scene::GetEntityManager() const
{
	return m_pEntityManager;
}

Camera* Scene::GetCamera() const
{
	return m_pCamera;
}

void Scene::CreatePlayer()
{
	m_pPlayer = m_pEntityManager->CreateEntity();
	m_pPlayer->AddComponent(new Transform(m_pPlayer));

	Texture* playerTexture = m_pGame->GetTextureCache()->GetTexture(TextureCache::Spritesheet::Player);
	std::unordered_map<std::string, AnimatorState*> states = std::unordered_map<std::string, AnimatorState*>
	{
		{ "idle", new PlayerIdleState() },
		{ "walk", new PlayerWalkState() },
		{ "jump", new PlayerJumpState() },
	};


	std::list<AnimatorTransition*> transitions = std::list<AnimatorTransition*>
	{
		new ConditionalTransition("idle", "walk", std::unordered_map<std::string, int>{ {"isWalking", 1}, }),
		new ConditionalTransition("walk", "idle", std::unordered_map<std::string, int>{ {"isWalking", 0}, }),

		new ConditionalTransition("idle", "jump", std::unordered_map<std::string, int>{ {"isGrounded", 0}, }),
		new ConditionalTransition("walk", "jump", std::unordered_map<std::string, int>{ {"isGrounded", 0}, }),
		new ConditionalTransition("jump", "idle", std::unordered_map<std::string, int>{ {"isGrounded", 1}, }),
	};

	m_pPlayer->AddComponent(new AnimatorRenderer(m_pPlayer, playerTexture, states, transitions, "idle"));
	m_pPlayer->AddComponent(new Player(m_pPlayer));

	//m_pPlayer->AddComponent(new RectCollider(m_pPlayer, Vector2f(0, 0), Vector2f(10, 10)));

	m_pPlayer->Initialize();
}
