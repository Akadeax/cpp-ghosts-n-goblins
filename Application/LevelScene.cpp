#include <pch.h>

#include <Camera.h>
#include <utils.h>
#include <Entity.h>
#include <EntityKeeper.h>
#include <Transform.h>
#include <Renderer.h>
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
	m_pTest->Initialize();
}

LevelScene::~LevelScene()
{
}

void LevelScene::UpdateScene(float deltaTime)
{
}

void LevelScene::DrawUI() const
{
	utils::DrawRect(25, 25, 100, 100, 5.f);
	utils::DrawEllipse(Ellipsef(75, 75, 30, 30), 5.f);
}

void LevelScene::DrawScene() const
{
	utils::SetColor(Color4f(1, 1, 1, 1));
	utils::DrawLine(Vector2f(20, 20), 1.f);
}
