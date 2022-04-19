#include <pch.h>

#include <unordered_map>
#include <iostream>

#include <InputHandler.h>

#include "GhostsAndGoblins.h"
#include "LevelScene.h"

GhostsAndGoblins::GhostsAndGoblins(const Window& window)
	: Game(window, new LevelScene())
{
	m_pInputHandler->AddKey("move_left", SDL_SCANCODE_A);
	m_pInputHandler->AddKey("move_right", SDL_SCANCODE_D);
	m_pInputHandler->AddKey("move_up", SDL_SCANCODE_W);
	m_pInputHandler->AddKey("move_down", SDL_SCANCODE_S);
}

void GhostsAndGoblins::UpdateGame(float deltaTime)
{
}
