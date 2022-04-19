#include <pch.h>

#include <Camera.h>
#include <utils.h>
#include <Entity.h>
#include <EntityKeeper.h>
#include <Transform.h>
#include <Renderer.h>
#include <Collider.h>
#include <Texture.h>

#include "LevelScene.h"
#include "MoveZoomCamera.h"
#include "Player.h"

void LevelScene::InitializeScene()
{
	m_pCamera = new MoveZoomCamera(2.f);
	// Center camera at start
	m_pCamera->MovePosition(Vector2f(-450, -300));

	m_pPlayer = m_pEntityKeeper->CreateEntity(100);
	m_pPlayer->AddComponent(new Transform(m_pPlayer, Vector2f(20, 20)));
	Texture* testTex = new Texture("resources/test.png");
	m_pPlayer->AddComponent(new Renderer(m_pPlayer, testTex));


	m_pPlayer->AddComponent(new Player(m_pPlayer));
	m_pPlayer->AddComponent(new Collider(m_pPlayer, std::vector<Vector2f>{
		Vector2f(-16, -16),
			Vector2f(-16, 16),
			Vector2f(16, 16),
			Vector2f(16, -16)
	}));

	m_pPlayer->Initialize();


	m_pBox = m_pEntityKeeper->CreateEntity(0);
	m_pBox->AddComponent(new Transform(m_pBox, Vector2f(-50, -50)));
	Texture* boxTex = new Texture("resources/box.png");
	m_pBox->AddComponent(new Renderer(m_pBox, boxTex));

	m_pBox->AddComponent(new Collider(m_pBox, std::vector<Vector2f>{
		Vector2f(-16, -16),
			Vector2f(-16, 16),
			Vector2f(16, 16),
			Vector2f(16, -16)
	}));

	m_pBox->Initialize();
}

void LevelScene::UpdateScene(float deltaTime)
{
	m_pPlayer->GetComponent<Transform>()->Rotate(75 * deltaTime);
}

void LevelScene::DrawUI() const
{
}

void LevelScene::DrawScene() const
{
}
