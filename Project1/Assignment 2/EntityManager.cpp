#include "EntityManager.h"
#include <iostream>


EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{	
	delete m_modelHandler;
	delete m_shaderLoad;
	delete m_renderer;
	delete m_entity;
}

void EntityManager::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{

	//Set device and context
	m_device = device;
	m_deviceContext = deviceContext;

	//Set the renderer
	m_renderer = new Renderer(m_deviceContext, m_device);
	m_modelHandler = new ModelHandler();
	m_modelHandler->LoadOBJData("Player_ship.obj", "Player_Ship.mtl", m_device, m_deviceContext);
	m_modelHandler->CreateBuffers(m_device);
	m_shaderLoad = new ShaderHandler();
	m_shaderLoad->CreateShaders(m_device, "PlayerVS.hlsl", "PlayerGS.hlsl", "PlayerPS.hlsl");
	m_entity = new Entity(XMFLOAT3(0, 0, 40), XMFLOAT3(1, 1, 1));

	XMVECTOR _rotatAxis{ 0, 1, 0, 0 };
	m_xmrot = XMMatrixRotationAxis(_rotatAxis, XM_PI);
}

void EntityManager::Render()
{
	m_shaderLoad->SetShaders(m_deviceContext);
	m_modelHandler->SetBuffers(m_deviceContext);
	m_renderer->Render(m_modelHandler, m_entity->GetPosition(), m_entity->GetRotation(), m_entity->GetScale());
}

void EntityManager::Update(double time)
{
	m_entity->Update(time);
}
