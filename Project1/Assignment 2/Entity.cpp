#include "Entity.h"

Entity::Entity(XMFLOAT3 Position, XMFLOAT3 Scale)
{
	XMVECTOR _rotzAxis{ 0,1,0,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, m_rot);

	m_position = Position;
	m_scale = Scale;

	m_speed = 0;
}

void Entity::Update(double time)
{
	XMVECTOR _rotzAxis{ 0,1,0,0 };
	if (m_rot >= 360)
	{
		m_rot = 0;
	}
	else
	{
		m_rot = m_rot + time;
	}
	m_rotation = XMMatrixRotationAxis(_rotzAxis, m_rot);
}