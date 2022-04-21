#include <pch.h>

#include <Camera.h>
#include <utils.h>
#include <Entity.h>
#include <EntityKeeper.h>
#include <Transform.h>
#include <Renderer.h>
#include <Collider.h>
#include <Texture.h>
#include <PhysicsBody.h>
#include <PhysicsHandler.h>
#include <collisions.h>
#include <Game.h>
#include <TextureCache.h>
#include <AnimatorState.h>
#include <ConditionalTransition.h>
#include <AnimatorRenderer.h>
#include <Camera.h>

#include "LevelScene.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerJumpState.h"
#include "PlayerCamera.h"

void LevelScene::InitializeScene()
{
	m_pCamera = new PlayerCamera(m_pPlayerTransform);

	m_pGame->GetTextureCache()->LoadTexture("player", "resources/player.png");

	m_pGame->GetTextureCache()->LoadTexture("level1Foreground", "resources/level1Foreground.png");
	m_pGame->GetTextureCache()->LoadTexture("level1Background", "resources/level1Background.png");

	// Center camera at start
	m_pCamera->MovePosition(Vector2f(-450, -300));

	CreatePlayer();
	dynamic_cast<PlayerCamera*>(m_pCamera)->SetFollowTarget(m_pPlayerTransform);
	CreateLevel();
}

void LevelScene::UpdateScene(float deltaTime)
{
	// Parallax the background
	float newXPos = (m_pCamera->GetPosition().x * 0.2f) + (m_LevelSize.x / 2.f);
	m_pBackgroundTransform->SetPosition(Vector2f(newXPos, 0));
}

void LevelScene::DrawUI() const
{
}

void LevelScene::DrawScene() const
{

}

void LevelScene::CreatePlayer()
{
	m_pPlayer = m_pEntityKeeper->CreateEntity(100, "player");
	m_pPlayerTransform = new Transform(m_pPlayer, Vector2f(90, -40));
	m_pPlayer->AddComponent(m_pPlayerTransform);
	Texture* playerTex = m_pGame->GetTextureCache()->GetTexture("player");
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

	m_pPlayer->AddComponent(new AnimatorRenderer(m_pPlayer, playerTex, states, transitions, "idle"));


	m_pPlayer->AddComponent(new Player(m_pPlayer));
	m_pPlayer->AddComponent(new Collider(m_pPlayer, std::vector<Vector2f>{
		Vector2f(-12, -12),
		Vector2f(-12, 12),
		Vector2f(12, 12),
		Vector2f(12, -12)
	}));

	m_pPlayer->AddComponent(new PhysicsBody(m_pPlayer));

	m_pPlayer->Initialize();
}

void LevelScene::CreateLevel()
{
	Texture* foreground = m_pGame->GetTextureCache()->GetTexture("level1Foreground");
	Texture* background = m_pGame->GetTextureCache()->GetTexture("level1Background");

	m_LevelSize = Vector2f(foreground->GetWidth(), foreground->GetHeight());

	m_pLevelBackground = m_pEntityKeeper->CreateEntity(-10);
	m_pBackgroundTransform = new Transform(m_pLevelBackground, Vector2f(m_LevelSize.x / 2, 0));
	m_pLevelBackground->AddComponent(m_pBackgroundTransform);
	m_pLevelBackground->AddComponent(new Renderer(m_pLevelBackground, background));
	m_pLevelBackground->Initialize();


	m_pLevel = m_pEntityKeeper->CreateEntity(0, "ground");
	m_pLevel->AddComponent(new Transform(m_pLevel, Vector2f(m_LevelSize.x / 2, 0)));
	m_pLevel->AddComponent(new Renderer(m_pLevel, foreground));

	nlohmann::json file = m_pGame->LoadJsonFile("resources/level1.json");
	std::vector<Vector2f> curr = file["colliders"];

	std::vector<std::vector<Vector2f>> colliders
	{
		// 1st ground
		{ Vector2f(0, 0), Vector2f(0, 38), Vector2f(1662, 38), Vector2f(1662, 0), },
		// Left bound
		{ Vector2f(-32, 0), Vector2f(-32, 200), Vector2f(0, 200), Vector2f(0, 0), },
		// Gravestones
		{ Vector2f(47, 38), Vector2f(47, 38 + 16), Vector2f(47 + 16, 38 + 16), Vector2f(47 + 16, 38), },
	};

	for (std::vector<Vector2f>& coll : colliders)
	{
		for (Vector2f& vec : coll)
		{
			// Transform from centered to bottom-left
			vec = Vector2f(vec.x - m_LevelSize.x / 2, vec.y - m_LevelSize.y / 2);
		}
		m_pLevel->AddComponent(new Collider(m_pLevel, coll));
	}

	m_pLevel->Initialize();
}
