#include "pch.h"

#include <cassert>
#include <SDL.h>
#include "Player.h"
#include "Entity.h"
#include "Transform.h"
#include "PhysicsBody.h"
#include "AnimatorRenderer.h"

Player::Player(Entity* entity)
	: Component(entity)
{
}

void Player::Initialize()
{
	m_Animator = m_pParent->GetComponent<AnimatorRenderer>();
	assert(m_Animator != nullptr && "Player has no Animator");
	m_Transform = m_pParent->GetComponent<Transform>();
	assert(m_Transform != nullptr && "Player has no Transform");
	m_PhysicsBody = m_pParent->GetComponent<PhysicsBody>();
	assert(m_PhysicsBody != nullptr && "Player has no physics body");
}

void Player::Update(float deltaTime)
{
	const int MOVE_SPEED = 100;
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_A])
	{
		m_PhysicsBody->SetXVelocity(-MOVE_SPEED);
		m_Animator->SetParameter("isWalking", true);
		m_Animator->SetFlipX(true);
	}
	else if (state[SDL_SCANCODE_D])
	{
		m_PhysicsBody->SetXVelocity(MOVE_SPEED);
		m_Animator->SetParameter("isWalking", true);
		m_Animator->SetFlipX(false);
	}
	else
	{
		m_PhysicsBody->SetXVelocity(0);
		m_Animator->SetParameter("isWalking", false);
	}

	if (state[SDL_SCANCODE_W])
	{
		m_PhysicsBody->SetYVelocity(MOVE_SPEED);
		m_Animator->SetParameter("isWalking", true);
		m_Animator->SetFlipY(false);
	}
	else if (state[SDL_SCANCODE_S])
	{
		m_PhysicsBody->SetYVelocity(-MOVE_SPEED);
		m_Animator->SetParameter("isWalking", true);
		m_Animator->SetFlipY(true);
	}
	else
	{
		m_PhysicsBody->SetYVelocity(0);
		m_Animator->SetParameter("isWalking", false);
	}

	if (state[SDL_SCANCODE_SPACE])
	{
		m_PhysicsBody->AddVelocity(Vector2f(0, 100));
	}
}
