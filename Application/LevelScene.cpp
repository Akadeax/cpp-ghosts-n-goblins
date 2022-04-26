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

	if (m_pPlayerTransform->GetPosition().y < -100)
	{
		m_pGame->LoadScene(new LevelScene());
	}
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


	// Load level collision from json
	nlohmann::json levelFile = m_pGame->LoadJsonFile("resources/level1.json");
	for (auto& collider : levelFile.at("colliders"))
	{
		std::vector<Vector2f> currentVertices;
		for (nlohmann::json& vertexJson : collider.at("vertices"))
		{
			Vector2f currentVertex = Vector2f();
			currentVertex.x = vertexJson.at("x").get<float>();
			currentVertex.y = vertexJson.at("y").get<float>();
			currentVertices.push_back(currentVertex);
		}

		for (Vector2f& vertex : currentVertices)
		{
			// Transform from centered to bottom-left
			vertex.Set(vertex.x - m_LevelSize.x / 2, vertex.y - m_LevelSize.y / 2);
		}

		m_pLevel->AddComponent(new Collider(m_pLevel, currentVertices));
	} 

	m_pLevel->Initialize();
}
