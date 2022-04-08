#include "pch.h"

#include <cassert>
#include <SDL.h>
#include "Player.h"
#include "Entity.h"
#include "Transform.h"
#include "PhysicsBody.h"
#include "AnimatorRenderer.h"
#include "Collider.h"
#include "PhysicsHandler.h"
#include "utils.h"
#include "collisions.h"

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
	const int MOVE_SPEED = 50;
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_A] && m_IsGrounded)
	{
		m_PhysicsBody->SetXVelocity(-MOVE_SPEED);
		m_Animator->SetParameter("isWalking", true);
		m_Animator->SetFlipX(true);
	}
	else if (state[SDL_SCANCODE_D] && m_IsGrounded)
	{
		m_PhysicsBody->SetXVelocity(MOVE_SPEED);
		m_Animator->SetParameter("isWalking", true);
		m_Animator->SetFlipX(false);
	}
	else if(m_IsGrounded)
	{
		m_PhysicsBody->SetXVelocity(0);
		m_Animator->SetParameter("isWalking", false);
	}

	// Jump
	if (!m_SpaceLastFrame && state[SDL_SCANCODE_SPACE] && m_IsGrounded)
	{
		m_PhysicsBody->AddVelocity(Vector2f(0, 150));
	}
	// TODO: Rework
	m_SpaceLastFrame = state[SDL_SCANCODE_SPACE];


	// Apply gravity
	if (!m_IsGrounded)
	{
		m_PhysicsBody->AddVelocity(Vector2f(0, -6 * m_GravityFactor));
	}


	// Grounded
	Vector2f playerPos = m_PhysicsBody->GetTransform()->GetPosition();
	// Offset both ground check points down and to the left/right according to consts
	// If Anything is between these two points, player is grounded
	Vector2f castBottomLeft = playerPos + Vector2f(-(m_GroundedCheckXSize / 2), m_GroundedCheckYOffset);
	Vector2f castBottomRight = playerPos + Vector2f(m_GroundedCheckXSize / 2, m_GroundedCheckYOffset);

	std::pair<bool, Collider*> groundedResult = GetPhysicsHandler()->Linecast(castBottomLeft, castBottomRight);
	m_IsGrounded = groundedResult.first;
	m_Animator->SetParameter("isGrounded", m_IsGrounded);
}

void Player::Draw() const
{
	Transform* trans = m_PhysicsBody->GetTransform();
	collisions::LineLine(Vector2f(-10, m_GroundedCheckYOffset), Vector2f(10, m_GroundedCheckYOffset), Vector2f(), Vector2f());
}
