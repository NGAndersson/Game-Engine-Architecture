#include "Renderer.h"

struct Vertex    //Overloaded Vertex Structure
{
	XMFLOAT3 pos;
	XMFLOAT2 tex;
	XMFLOAT3 normal;

	Vertex() {}
	Vertex(float x, float y, float z) {
		pos = XMFLOAT3(x, y, z);
		tex = XMFLOAT2(0.5f, 0.5f);
		normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
};

Renderer::~Renderer()
{
	if (m_camBuffer != nullptr)
		m_camBuffer->Release();

	if (m_worldBuffer != nullptr)
		m_worldBuffer->Release();

	if (m_worldBufferInstance != nullptr)
		m_worldBufferInstance->Release();
}

void Renderer::Render(ModelHandler* model, XMFLOAT3 position, XMMATRIX &rotation, XMFLOAT3 scale)
{
	//Set vertexbuffer, pixel material constant buffer and set the correct shaders
	model->SetBuffers(m_deviceContext);

	//Set Worldmatrix and Position(float3) as a Vertexshader constant buffer
	XMMATRIX Scale = XMMatrixScaling(scale.x, scale.y, scale.z);
	XMMATRIX Translation = XMMatrixTranslation(position.x, position.y, position.z);
	m_worldStruct.worldMatrix = XMMatrixTranspose(Scale * rotation * Translation);
	m_worldStruct.worldRotation= XMMatrixTranspose(rotation);

	m_deviceContext->UpdateSubresource(m_worldBuffer, 0, NULL, &m_worldStruct, 0, 0);
	m_deviceContext->VSSetConstantBuffers(0, 1, &m_worldBuffer);

	XMFLOAT3 camPos = XMFLOAT3(m_camStruct.camPos.x, m_camStruct.camPos.y, m_camStruct.camPos.z);
	float distance = sqrt((camPos.x - position.x)*(camPos.x - position.x) + (camPos.y - position.y)*(camPos.y - position.y) + (camPos.z - position.z)*(camPos.z - position.z));
	int LoD = 0;
	//Checks for distance for level of detail
	for (int i = 1; i < 11; i++)
	{
		if (distance <= i * 10)
			LoD++;
		else
			break;
	}

	//Draw call
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->Draw(model->GetVertexCount(), 0);
}

void Renderer::RenderInstanced(ModelHandler * model, vector<XMFLOAT3> position, vector<XMMATRIX> &rotation, int amountOfBullets, vector<XMFLOAT3> scale)
{
	//Set vertexbuffer, pixel material constant buffer and set the correct shaders
	model->SetBuffers(m_deviceContext);
	XMMATRIX Translation;
	XMMATRIX Scale;
	//Set Worldmatrix and Position(float3) as a Vertexshader constant buffer

	XMFLOAT4X4 _worldInstance;
	XMFLOAT4X4 _worldRotation;

	D3D11_MAPPED_SUBRESOURCE _mappedResource;

	HRESULT hr = m_deviceContext->Map(m_worldBufferInstance, 0, D3D11_MAP_WRITE_DISCARD, 0, &_mappedResource);

	for (int i = 0; i < amountOfBullets; i++)
	{
		Translation = XMMatrixTranslation(position[i].x, position[i].y, position[i].z);
		Scale = XMMatrixScaling(scale[i].x, scale[i].y, scale[i].z);
		XMStoreFloat4x4(&_worldInstance, XMMatrixTranspose(rotation[i] * Scale * Translation));
		XMStoreFloat4x4(&_worldRotation, XMMatrixTranspose(rotation[i]));
		m_worldStructInstanced.worldMatrix[i] = _worldInstance;
		m_worldStructInstanced.worldRotation[i] = _worldRotation;
		if (amountOfBullets >= 100)
		{
			int fail = 1;
		}
	}

	memcpy(_mappedResource.pData, &m_worldStructInstanced, sizeof(WorldStructInstanced));

	m_deviceContext->Unmap(m_worldBufferInstance, 0);

	m_deviceContext->VSSetConstantBuffers(0, 1, &m_worldBufferInstance);

	//Draw call
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->DrawInstanced(model->GetVertexCount(), amountOfBullets, 0, 0);
}

Renderer::Renderer(ID3D11DeviceContext * deviceContext, ID3D11Device * device)
{
	m_device = device;
	m_deviceContext = deviceContext;

	m_cam.SetCameraPos(XMVectorSet(0, 0, 0, 0));
	m_cam.SetLookAtVec(XMVectorSet(0, 0, 1, 0));
	m_cam.SetProjectionMatrix();
	m_cam.SetViewMatrix();
	m_cam.SetViewProjectionMatrix();
	m_cam.CreateBuffer(device);
	m_cam.SetConstantBuffer(deviceContext);

	D3D11_BUFFER_DESC _worldBufferDesc, _worldBufferInstanceDesc;
	
	//Create world constant buffer desc
	ZeroMemory(&_worldBufferDesc, sizeof(D3D11_BUFFER_DESC));

	_worldBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	_worldBufferDesc.ByteWidth = sizeof(WorldStruct);
	_worldBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_worldBufferDesc.CPUAccessFlags = 0;
	_worldBufferDesc.MiscFlags = 0;

	//Create the world constant buffer
	device->CreateBuffer(&_worldBufferDesc, NULL, &m_worldBuffer);
		
	//Create world constant buffer desc
	ZeroMemory(&_worldBufferInstanceDesc, sizeof(D3D11_BUFFER_DESC));

	_worldBufferInstanceDesc.Usage = D3D11_USAGE_DYNAMIC;
	_worldBufferInstanceDesc.ByteWidth = sizeof(WorldStructInstanced);
	_worldBufferInstanceDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_worldBufferInstanceDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_worldBufferInstanceDesc.MiscFlags = 0;

	//Create the world constant buffer
	device->CreateBuffer(&_worldBufferInstanceDesc, NULL, &m_worldBufferInstance);
}
