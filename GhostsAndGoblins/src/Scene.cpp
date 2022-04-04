#include "pch.h"

#include "Scene.h"
#include "EntityManager.h"
#include "PhysicsHandler.h"
#include "Camera.h"
#include "Player.h"
#include "TextureCache.h"
#include "Texture.h"
#include "TextureCache.h"
#include "Entity.h"
#include "Game.h"
#include "ConditionalTransition.h"

#include "Transform.h"
#include "AnimatorRenderer.h"
#include "RectCollider.h"
#include "PhysicsBody.h"

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
	delete m_pPhysicsHandler;
	delete m_pCamera;
}

void Scene::Initialize()
{
	m_pEntityManager = new EntityManager(this);
	m_pPhysicsHandler = new PhysicsHandler(this);
	m_pCamera = new Camera(Point2f(-60, -60), 3);

	CreatePlayer();
	CreatePlatform();
}

void Scene::Update(float deltaTime)
{
	m_pEntityManager->UpdateEntities(deltaTime);
	m_pPhysicsHandler->UpdatePhysics(deltaTime);
	m_pCamera->Update(deltaTime);
}

void Scene::Draw() const
{
	glPushMatrix();
	m_pCamera->Draw();
	m_pEntityManager->DrawEntities();
	m_pPhysicsHandler->DrawColliders();
	glPopMatrix();
}

EntityManager* Scene::GetEntityManager() const
{
	return m_pEntityManager;
}

PhysicsHandler* Scene::GetPhysicsHandler() const
{
	return m_pPhysicsHandler;
}

Camera* Scene::GetCamera() const
{
	return m_pCamera;
}

void Scene::CreatePlayer()
{
	m_pPlayer = m_pEntityManager->CreateEntity();
	m_pPlayer->AddComponent(new Transform(m_pPlayer, Vector2f(50, 100)));

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

	m_pPlayer->AddComponent(new RectCollider(m_pPlayer, Vector2f(0, 0), Vector2f(25, 25)));
	m_pPlayer->AddComponent(new PhysicsBody(m_pPlayer));

	m_pPlayer->Initialize();
}

void Scene::CreatePlatform()
{
	m_pPlatform = m_pEntityManager->CreateEntity();
	Transform* platformTransform = new Transform(m_pPlatform, Vector2f(50, 0));
	m_pPlatform->AddComponent(platformTransform);
	platformTransform->SetScale(0.5f);
	
	Texture* platformTexture = m_pGame->GetTextureCache()->GetTexture(TextureCache::Spritesheet::Platform);
	m_pPlatform->AddComponent(new Renderer(m_pPlatform, platformTexture));

	m_pPlatform->AddComponent(new RectCollider(m_pPlatform, Vector2f(0, 0), Vector2f(125, 25)));

	m_pPlatform->Initialize();
}
