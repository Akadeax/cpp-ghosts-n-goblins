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

LevelScene::LevelScene(Game* game)
	: Scene(m_pGame, new MoveZoomCamera(1.f))
{
	// Center camera at start
	m_pCamera->MovePosition(Vector2f(-450, -300));

	m_pTest = m_pEntityKeeper->CreateEntity();
	m_pTest->AddComponent(new Transform(m_pTest, Vector2f()));
	Texture* testTex = new Texture("resources/test.png");
	m_pTest->AddComponent(new Renderer(m_pTest, testTex));

	m_pTest->AddComponent(new Collider(m_pTest, std::vector<Vector2f>{
		Vector2f(-16, -16),
		Vector2f(-16, 16),
		Vector2f(16, 16),
		Vector2f(16, -16)
	}));

	m_pTest->Initialize();



	m_pBox = m_pEntityKeeper->CreateEntity();
	m_pBox->AddComponent(new Transform(m_pBox, Vector2f(-50, -50)));
	Texture* boxTex = new Texture("resources/box.png");
	m_pTest->AddComponent(new Renderer(m_pTest, testTex));
}

LevelScene::~LevelScene()
{
}

void LevelScene::UpdateScene(float deltaTime)
{
	m_pTest->GetComponent<Transform>()->Rotate(25 * deltaTime);
}

void LevelScene::DrawUI() const
{
}

void LevelScene::DrawScene() const
{
}
