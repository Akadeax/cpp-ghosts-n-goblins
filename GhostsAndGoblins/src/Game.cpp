#include "pch.h"
#include "Game.h"

#include <iostream>

#include "Camera.h"
#include "Texture.h"

#include "Entity.h"
#include "EntityManager.h"

#include "TransformComponent.h"
#include "RendererComponent.h"
#include "TextureCache.h"

Game::Game(const Window& window) 
	:m_Window{window}
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_EntityManager = new EntityManager();
	m_Camera = new Camera();
	m_TextureCache = new TextureCache();

	m_Ent = m_EntityManager->CreateEntity();
	m_Ent->AddComponent(new TransformComponent(m_Ent, Point2f(0, 0)));
	m_Ent->AddComponent(new RendererComponent(m_Ent, m_TextureCache->GetTexture(TextureCache::Spritesheet::Player)));
}

void Game::Cleanup()
{
	delete m_EntityManager;
	delete m_Camera;
	delete m_TextureCache;
}

void Game::Update(float deltaTime)
{
	m_EntityManager->UpdateEntities(deltaTime);
	m_Camera->Update(deltaTime);
}

void Game::Draw() const
{
	ClearBackground();

	glPushMatrix();
	m_Camera->Draw();
	m_EntityManager->DrawEntities();
	glPopMatrix();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent & e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
