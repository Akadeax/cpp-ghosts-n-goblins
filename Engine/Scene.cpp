#include "pch.h"

#include <cassert>

#include "Scene.h"
#include "Camera.h"
#include "PhysicsHandler.h"
#include "EntityKeeper.h"
#include "Game.h"
#include "utils.h"

Scene::~Scene()
{
	delete m_pCamera;
	delete m_pEntityKeeper;
	delete m_pPhysicsHandler;
}

void Scene::Initialize(Game* game)
{
	m_pGame = game;
	m_pPhysicsHandler = new PhysicsHandler();
	m_pEntityKeeper = new EntityKeeper(this);

	InitializeScene();
	assert(m_pCamera != nullptr && "Scene has no assigned camera");
}

void Scene::Update(float deltaTime)
{
	m_pPhysicsHandler->Update(deltaTime);
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

EntityKeeper* Scene::GetEntityKeeper() const
{
	return m_pEntityKeeper;
}

PhysicsHandler* Scene::GetPhysicsHandler() const
{
	return m_pPhysicsHandler;
}

Camera* Scene::GetCamera() const
{
	return m_pCamera;
}
