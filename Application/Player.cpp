#include "pch.h"

#include "Player.h"
#include <InputHandler.h>
#include <Entity.h>
#include <Scene.h>
#include <Game.h>
#include <Transform.h>

Player::Player(Entity* parent)
	: Component(parent)
{
}

void Player::Update(float deltaTime)
{
	InputHandler* input = m_pParent->GetScene()->GetGame()->GetInputHandler();

	if (input->GetKeyPressed("move_left"))
	{
		m_pTransform->MovePosition(Vector2f(-m_MoveSpeed * deltaTime, 0));
	}
	else if (input->GetKeyPressed("move_right"))
	{
		m_pTransform->MovePosition(Vector2f(m_MoveSpeed * deltaTime, 0));
	}

	if (input->GetKeyPressed("move_down"))
	{
		m_pTransform->MovePosition(Vector2f(0, -m_MoveSpeed * deltaTime));
	}
	else if (input->GetKeyPressed("move_up"))
	{
		m_pTransform->MovePosition(Vector2f(0, m_MoveSpeed * deltaTime));
	}
}

void Player::Initialize()
{
	m_pTransform = m_pParent->GetComponent<Transform>();
}
