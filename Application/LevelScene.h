#pragma once
#include <Scene.h>

class Entity;

class LevelScene final
	: public Scene
{
public:
	explicit LevelScene() = default;
	LevelScene& operator=(const LevelScene& rhs) = delete;
	LevelScene& operator=(LevelScene&& rhs) = delete;
	LevelScene(const LevelScene& rhs) = delete;
	LevelScene(LevelScene&& rhs) = delete;
	virtual ~LevelScene() = default;

	void InitializeScene() override;

	void UpdateScene(float deltaTime) override;

	void DrawUI() const override;
	void DrawScene() const override;

private:
	Entity* m_pPlayer{ nullptr };
	Entity* m_pBox{ nullptr };
};
