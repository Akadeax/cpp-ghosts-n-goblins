#pragma once
#include <Scene.h>

class Entity;
class Transform;

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
	Transform* m_pPlayerTransform{ nullptr };

	Vector2f m_LevelSize{ Vector2f() };
	Entity* m_pLevel{ nullptr };
	Entity* m_pLevelBackground{ nullptr };
	Transform* m_pBackgroundTransform{ nullptr };

	void CreatePlayer();
	void CreateLevel();
};
