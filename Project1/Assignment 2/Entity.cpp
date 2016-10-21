#include "Entity.h"

Entity::Entity(XMFLOAT3 Position, XMFLOAT3 Scale, int levelOfDetail)
{
	XMVECTOR _rotzAxis{ 0,1,0,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, m_rot);

	m_position = Position;
	m_scale = Scale;
	m_LoD = levelOfDetail;
	m_speed = 0;
	m_LoD = 10;
}

void Entity::Update(double time)
{
	XMVECTOR _rotzAxis{ 0,1,0,0 };
	if (m_rot >= 2 * XM_PI)
	{
		m_rot = m_rot - (2 * XM_PI);
	}
	else
	{
		m_rot = m_rot + time;
	}
	m_rotation = XMMatrixRotationAxis(_rotzAxis, m_rot);
}
