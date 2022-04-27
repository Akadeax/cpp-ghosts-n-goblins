#include <pch.h>

#include <unordered_map>
#include <iostream>

#include <InputHandler.h>

#include "GhostsAndGoblins.h"
#include "LevelScene.h"

GhostsAndGoblins::GhostsAndGoblins()
	: Game(new LevelScene())
{
	m_pInputHandler->AddKey("move_left", SDL_SCANCODE_LEFT);
	m_pInputHandler->AddKey("move_right", SDL_SCANCODE_RIGHT);
	m_pInputHandler->AddKey("crouch", SDL_SCANCODE_DOWN);
	m_pInputHandler->AddKey("climb_up", SDL_SCANCODE_UP);
	m_pInputHandler->AddKey("jump", SDL_SCANCODE_J);
	m_pInputHandler->AddKey("fire", SDL_SCANCODE_K);
}

void GhostsAndGoblins::UpdateGame(float deltaTime)
{
}
