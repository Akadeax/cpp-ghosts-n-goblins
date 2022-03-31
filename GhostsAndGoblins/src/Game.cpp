#include "pch.h"
#include "Game.h"

#include <iostream>

#include "Camera.h"
#include "Texture.h"

#include "Entity.h"
#include "EntityManager.h"
#include "TextureCache.h"

#include "Transform.h"
#include "Renderer.h"
#include "AnimatorRenderer.h"

#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerJumpState.h"

#include "ConditionalTransition.h"

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
	m_Camera = new Camera(Point2f(0, 0), 5);
	m_TextureCache = new TextureCache();

	m_Player = m_EntityManager->CreateEntity();
	m_Player->AddComponent(new Transform(m_Player));

	Texture* playerTexture = m_TextureCache->GetTexture(TextureCache::Spritesheet::Player);
	std::unordered_map<std::string, AnimatorState*> states = std::unordered_map<std::string, AnimatorState*>
	{
		{ "idle", new PlayerIdleState() },
		{ "walk", new PlayerWalkState() },
		{ "jump", new PlayerJumpState() },
	};


	std::set<AnimatorTransition*> transitions = std::set<AnimatorTransition*>
	{
		new ConditionalTransition("idle", "walk", std::unordered_map<std::string, int>{ {"isWalking", 1}, }),
		new ConditionalTransition("walk", "idle", std::unordered_map<std::string, int>{ {"isWalking", 0}, }),

		new ConditionalTransition("idle", "jump", std::unordered_map<std::string, int>{ {"isGrounded", 0}, }),
		new ConditionalTransition("walk", "jump", std::unordered_map<std::string, int>{ {"isGrounded", 0}, }),
		new ConditionalTransition("jump", "idle", std::unordered_map<std::string, int>{ {"isGrounded", 1}, }),
	};

	m_Player->AddComponent(new AnimatorRenderer(m_Player, playerTexture, states, transitions, "idle"));
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

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_SPACE])
	{
		m_Player->GetComponent<Transform>()->MovePosition(Vector2f(100, 100) * deltaTime);
	}

	if (state[SDL_SCANCODE_J])
	{
		m_Player->GetComponent<AnimatorRenderer>()->SetParameter("isGrounded", 0);
	}
	else
	{
		m_Player->GetComponent<AnimatorRenderer>()->SetParameter("isGrounded", 1);
	}

	if (state[SDL_SCANCODE_H])
	{
		m_Player->GetComponent<AnimatorRenderer>()->SetParameter("isWalking", 1);
	}
	else
	{
		m_Player->GetComponent<AnimatorRenderer>()->SetParameter("isWalking", 0);
	}
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
