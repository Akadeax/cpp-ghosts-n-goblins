#pragma once
#include <Game.h>

class GhostsAndGoblins final :
    public Game
{
public:
    explicit GhostsAndGoblins();
	GhostsAndGoblins& operator=(const GhostsAndGoblins& rhs) = delete;
	GhostsAndGoblins& operator=(GhostsAndGoblins&& rhs) = delete;
	GhostsAndGoblins(const GhostsAndGoblins& rhs) = delete;
	GhostsAndGoblins(GhostsAndGoblins&& rhs) = delete;
	virtual ~GhostsAndGoblins() = default;

    void UpdateGame(float deltaTime) override;
};

