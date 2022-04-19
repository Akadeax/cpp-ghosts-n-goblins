#include "pch.h"

#include "Game.h"
#include "Texture.h"
#include <cmath>
#include "Scene.h"
#include "InputHandler.h"
#include <iostream>

Game::Game(const Window& window, Scene* scene)
	: m_Window(window), m_pInputHandler{ new InputHandler() }, m_pScene{scene}
{
	m_pScene->Initialize(this, nullptr);
}

Game::~Game()
{
	delete m_pInputHandler;
	delete m_pScene;
}

void Game::Update(float deltaTime)
{
	m_pInputHandler->Update();
	m_pScene->Update(deltaTime);
	UpdateGame(deltaTime);
}

void Game::Draw() const
{
	m_pScene->Draw();
}

Window Game::GetWindow()
{
	return m_Window;
}

InputHandler* Game::GetInputHandler()
{
	return m_pInputHandler;
}

Scene* Game::GetScene()
{
	return m_pScene;
}
