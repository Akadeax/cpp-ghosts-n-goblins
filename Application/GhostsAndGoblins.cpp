#include <pch.h>

#include <unordered_map>
#include <iostream>

#include <InputHandler.h>

#include "GhostsAndGoblins.h"
#include "LevelScene.h"

GhostsAndGoblins::GhostsAndGoblins()
	: Game(new LevelScene())
{
	m_pInputHandler->AddKey("move_left", SDL_SCANCODE_A);
	m_pInputHandler->AddKey("move_right", SDL_SCANCODE_D);
	m_pInputHandler->AddKey("jump", SDL_SCANCODE_SPACE);
}

void GhostsAndGoblins::UpdateGame(float deltaTime)
{
}
