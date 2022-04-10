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
#include "Collider.h"
#include "PhysicsBody.h"
#include "DetectionCollider.h"

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
	m_pCamera = new Camera(Vector2f(0, 0), 2.7f);

	CreateStage();
	CreatePlayer();
}

void Scene::Update(float deltaTime)
{
	m_pEntityManager->UpdateEntities(deltaTime);
	m_pPhysicsHandler->Update(deltaTime);
	m_pCamera->Update(deltaTime);
}

void Scene::Draw() const
{
	glPushMatrix();
	m_pCamera->Draw();
	m_pEntityManager->DrawEntities();
	m_pPhysicsHandler->DebugDrawColliders();
	glPopMatrix();
}

Game* Scene::GetGame() const
{
	return m_pGame;
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
	m_pPlayer = m_pEntityManager->CreateEntity(100, "player");
	Transform* playerTransform = new Transform(m_pPlayer, Vector2f(50, 300));
	m_pPlayer->AddComponent(playerTransform);

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

	m_pPlayer->AddComponent(new Collider(m_pPlayer, Vector2f(0, 0), Vector2f(25, 25)));
	m_pPlayer->AddComponent(new PhysicsBody(m_pPlayer));

	m_pPlayer->Initialize();
	m_pCamera->SetFollowTarget(playerTransform);
}

void Scene::CreateStage()
{
	Texture* stageTexture = m_pGame->GetTextureCache()->GetTexture(TextureCache::Spritesheet::Stage);

	m_pStage = m_pEntityManager->CreateEntity(-100, "level");
	m_pStage->AddComponent(new Transform(m_pStage, Vector2f(stageTexture->GetWidth() / 2, stageTexture->GetHeight() / 2)));
	
	m_pStage->AddComponent(new Renderer(m_pStage, stageTexture));

	// Colliders are normally centered on the Entity, so we have to
	// convert to bottom-left-based for easier collider assignment
	std::vector<std::pair<Vector2f, Vector2f>> stageColliders
	{
		// level collision
		std::pair { Vector2f(0, 0), Vector2f(1663, 39) },
		std::pair { Vector2f(596, 105), Vector2f(536, 15) },
		// gravestones
		std::pair { Vector2f(47, 40), Vector2f(16, 16) },
		std::pair { Vector2f(239, 40), Vector2f(16, 16)},
		std::pair { Vector2f(415, 40), Vector2f(16, 16) },
		std::pair { Vector2f(527, 40), Vector2f(16, 16) },
		std::pair { Vector2f(751, 40), Vector2f(16, 16) },
		std::pair { Vector2f(959, 40), Vector2f(16, 16) },
		std::pair { Vector2f(1103, 40), Vector2f(16, 16) },
		std::pair { Vector2f(1263, 40), Vector2f(16, 16) },
		std::pair { Vector2f(1519, 40), Vector2f(16, 16) },
		std::pair { Vector2f(1519, 40), Vector2f(16, 16) }
	};
	
	Vector2f bottomLeft = Vector2f(-stageTexture->GetWidth() / 2, -stageTexture->GetHeight() / 2);
	for (auto& pair : stageColliders)
	{
		Vector2f offset = Vector2f(bottomLeft.x + pair.first.x + pair.second.x / 2, bottomLeft.y + pair.first.y + pair.second.y / 2);
		m_pStage->AddComponent(new DetectionCollider(m_pStage, offset, pair.second));
	}


	m_pStage->Initialize();
}
