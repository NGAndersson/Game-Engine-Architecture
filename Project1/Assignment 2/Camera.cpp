#include "Camera.h"


Camera::Camera()
{
	m_cameraPos = XMVectorSet(0, 0, 0, 0);
	m_lookAtVec = XMVectorSet(0, 1, 0, 0);

	SetViewMatrix();
	SetProjectionMatrix();
	SetViewProjectionMatrix();

}

Camera::Camera(XMVECTOR NewCameraPosition, XMVECTOR PositionLookingAt)
{
	m_cameraPos = NewCameraPosition;
	m_lookAtVec = PositionLookingAt;

	SetViewMatrix();
	SetProjectionMatrix();
	SetViewProjectionMatrix();
}

Camera::~Camera()
{
	if (m_constCameraBuffer != nullptr)
		m_constCameraBuffer->Release();
}

XMVECTOR Camera::GetCameraPos()
{
	return m_cameraPos;
}

XMVECTOR Camera::GetLookAtVec()
{
	return m_lookAtVec;
}

XMMATRIX Camera::GetViewMatrix()
{
	return m_view;
}

XMMATRIX Camera::GetProjectionMatrix()
{
	return m_projection;
}

XMMATRIX Camera::GetViewProjectionMatrix()
{
	return m_viewProjection;
}

void Camera::SetViewMatrix()
{
	m_view = XMMatrixLookAtLH(m_cameraPos, m_lookAtVec, XMVectorSet(0, 1, 0, 0));
}

void Camera::SetProjectionMatrix()
{
	m_projection = XMMatrixPerspectiveFovLH(XM_PI * 0.45f, 720.0f / 980.0f, 0.1f, 1500);
}

void Camera::SetViewProjectionMatrix()
{
	 m_viewProjection = m_view * m_projection;
}

void Camera::SetCameraPos(XMVECTOR NewCameraPosition)
{
	m_cameraPos = NewCameraPosition;
}

void Camera::SetLookAtVec(XMVECTOR PositionLookingAt)
{
	m_lookAtVec = m_cameraPos + XMVector3Normalize(PositionLookingAt);
}

HRESULT Camera::CreateBuffer(ID3D11Device* device)
{
	HRESULT _hr;

	D3D11_BUFFER_DESC _cameraBufferDesc;
	ZeroMemory(&_cameraBufferDesc, sizeof(D3D11_BUFFER_DESC));

	_cameraBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	_cameraBufferDesc.ByteWidth = sizeof(CameraType);
	_cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_cameraBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_cameraBufferDesc.MiscFlags = 0;

	//skapar constant buffer
	_hr = device->CreateBuffer(&_cameraBufferDesc, NULL, &m_constCameraBuffer);

	return _hr;
}

void Camera::SetConstantBuffer(ID3D11DeviceContext* gDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE _mappedResource;

	HRESULT hr = gDeviceContext->Map(m_constCameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_mappedResource);
	m_constCamera = (CameraType*)_mappedResource.pData;
	m_constCamera->CameraPos = XMFLOAT4(XMVectorGetByIndex(m_cameraPos, 0), XMVectorGetByIndex(m_cameraPos, 1), XMVectorGetByIndex(m_cameraPos, 2), 0);
	XMStoreFloat4x4(&m_constCamera->ViewProjection, XMMatrixTranspose(m_viewProjection));

	gDeviceContext->Unmap(m_constCameraBuffer, 0);

	gDeviceContext->GSSetConstantBuffers(0, 1, &m_constCameraBuffer);
	gDeviceContext->PSSetConstantBuffers(2, 1, &m_constCameraBuffer);
}