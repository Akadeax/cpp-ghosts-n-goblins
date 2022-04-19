#pragma once
#include <Game.h>

class GhostsAndGoblins final :
    public Game
{
public:
    GhostsAndGoblins(const Window& window);
    ~GhostsAndGoblins();

    void UpdateGame(float deltaTime) override;
};

