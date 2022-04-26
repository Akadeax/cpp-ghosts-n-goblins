#include "pch.h"

#include <iostream>
#include <fstream>

#include "Game.h"
#include "Texture.h"
#include "Scene.h"
#include "InputHandler.h"
#include "TextureCache.h"

Game::Game(Scene* scene)
	: m_pInputHandler{ new InputHandler() },
	m_pScene{scene},
	m_pTextureCache{ new TextureCache() }
{
	m_pScene->Initialize(this);
}

Game::~Game()
{
	delete m_pInputHandler;
	delete m_pScene;
	delete m_pTextureCache;
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

InputHandler* Game::GetInputHandler() const
{
	return m_pInputHandler;
}

Scene* Game::GetScene() const
{
	return m_pScene;
}

TextureCache* Game::GetTextureCache() const
{
	return m_pTextureCache;
}

nlohmann::json Game::LoadJsonFile(std::string file)
{
	std::string levelJsonString;

	std::ifstream levelFile;
	levelFile.open(file);
	if (levelFile)
	{
		std::ostringstream os;
		os << levelFile.rdbuf();
		levelJsonString = os.str();
	}

	return nlohmann::json::parse(levelJsonString);
}

void Game::LoadScene(Scene* newScene)
{
	delete m_pScene;
	m_pScene = newScene;
	m_pScene->Initialize(this);
}
