#pragma once
#include <Scene.h>

class Entity;

class LevelScene final
	: public Scene
{
public:
	LevelScene(Game* game);
	~LevelScene();

	void UpdateScene(float deltaTime) override;

	void DrawUI() const override;
	void DrawScene() const override;

private:
	Entity* m_pTest;
};
