#include "pch.h"

#include "Scene.h"
#include "Camera.h"
#include "EntityKeeper.h"
#include "Game.h"
#include "utils.h"

Scene::~Scene()
{
	delete m_pCamera;
	delete m_pEntityKeeper;
}

void Scene::Initialize(Game* game, Camera* camera)
{
	m_pGame = game;
	m_pCamera = camera;
	m_pEntityKeeper = new EntityKeeper(this);

	InitializeScene();
}

void Scene::Update(float deltaTime)
{
	m_pEntityKeeper->UpdateEntities(deltaTime);
	m_pCamera->Update(deltaTime);
	UpdateScene(deltaTime);
}

void Scene::Draw() const
{
	glPushMatrix();
	m_pCamera->Draw();
	m_pEntityKeeper->DrawEntities();
	DrawScene();
	glPopMatrix();

	// Draw UI last and without camera transformation
	glPushMatrix();
	DrawUI();
	glPopMatrix();
}

Game* Scene::GetGame() const
{
	return m_pGame;
}

Camera* Scene::GetCamera() const
{
	return m_pCamera;
}
