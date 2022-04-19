#include <pch.h>

#include <unordered_map>
#include <iostream>

#include <InputHandler.h>

#include "GhostsAndGoblins.h"
#include "LevelScene.h"

GhostsAndGoblins::GhostsAndGoblins(const Window& window)
	: Game(window, new LevelScene(this))
{
	m_pInputHandler->AddKey("test", SDL_SCANCODE_SPACE);
}

GhostsAndGoblins::~GhostsAndGoblins()
{
}

void GhostsAndGoblins::UpdateGame(float deltaTime)
{
}
