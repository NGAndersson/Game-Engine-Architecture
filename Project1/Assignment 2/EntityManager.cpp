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

	//Set all asset pointers
	//Not how we are supposed to do it right now: m_loader.Get() shall return an obj object so that the model gets saved in the memory, and not the file.
	m_tempAsset = m_loader.Get("asset1.obj.zip");
	m_objAsset = static_cast<char*> (m_tempAsset);
	m_tempAsset = m_loader.Get("asset1.mtl.zip");
	m_mtlAsset = static_cast<char*> (m_tempAsset);
	m_tempAsset = m_loader.Get("vertexasset.hlsl.zip");
	m_vAsset = static_cast<char*> (m_tempAsset);
	m_tempAsset = m_loader.Get("geometryasset.hlsl.zip");
	m_gAsset = static_cast<char*> (m_tempAsset);
	m_tempAsset = m_loader.Get("pixelasset.hlsl.zip");
	m_pAsset = static_cast<char*> (m_tempAsset);

	//Set the renderer
	m_renderer = new Renderer(m_deviceContext, m_device);
	m_modelHandler = new ModelHandler();
	m_modelHandler->LoadOBJData("playerShip.obj", "playerShip.mtl", m_device, m_deviceContext);
	//m_modelHandler->LoadOBJData(m_objAsset, m_mtlAsset, m_device, m_deviceContext); <--- Detta är vad det ska bli efter att LoadOBJData är omskriven
	//kan göra om char* till string via std::string(const char*), göra innan eller efter datan har skickats igenom LoadOBJData? Eller ska jag typecasta till string* istället för char?
	m_modelHandler->CreateBuffers(m_device);
	m_shaderLoad = new ShaderHandler();
	m_shaderLoad->CreateShaders(m_device, "PlayerVS.hlsl", "PlayerGS.hlsl", "PlayerPS.hlsl");
	//shaderLoad->CreateShaders(m_device, m_vAsset, m_gAsset, m_pAsset); <--- Detta är vad det ska bli efter att CreateShaders är omskriven
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
	XMStoreFloat3(&m_camPos, m_cam.GetCameraPos());
	m_entityPos = m_entity->GetPosition();
	float distance = sqrt((m_camPos.x - m_entityPos.x)*(m_camPos.x - m_entityPos.x) + (m_camPos.y - m_entityPos.y)*(m_camPos.y - m_entityPos.y) + (m_camPos.z - m_entityPos.y)*(m_camPos.z - m_entityPos.y));
	for (int i = 1; i < 11; i++)
	{
		if (distance <= i * 10)
			LoD++;
		else
			break;
	}
	m_entity->Update(time);
	LoD = 0;
}
