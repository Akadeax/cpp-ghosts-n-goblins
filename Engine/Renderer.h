#pragma once
#include "Entity.h"
#include "Component.h"

class Texture;
class Transform;

class Renderer
	: public Component
{
public:
	explicit Renderer(Entity* parent, Texture* texture);
	Renderer& operator=(const Renderer& rhs) = delete;
	Renderer& operator=(Renderer&& rhs) = delete;
	Renderer(const Renderer& rhs) = delete;
	Renderer(Renderer&& rhs) = delete;
	virtual ~Renderer() = default;

	void Initialize() override;
	// general draw call that applies to all renderer subclasses
	void Draw() const override final;
	// function that can be overriden for specific renderer subclass
	virtual void DrawSprite() const;

	bool GetFlipX() const;
	void SetFlipX(bool newState);
	bool GetFlipY() const;
	void SetFlipY(bool newState);

protected:
	Texture* m_pTexture;
	Transform* m_pParentTransform = nullptr;

	bool m_FlipX = false;
	bool m_FlipY = false;
};

