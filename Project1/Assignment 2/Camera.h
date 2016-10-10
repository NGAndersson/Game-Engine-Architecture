#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <DirectXMath.h>
#include <d3d11.h>
using namespace DirectX;

class Camera
{
private:
	struct CameraType
	{
		XMFLOAT4 CameraPos;
		XMFLOAT4X4 ViewProjection;
	};
public:
	Camera();
	Camera(XMVECTOR NewCameraPosition, XMVECTOR PositionLookingAt);
	~Camera();
	XMVECTOR GetCameraPos();
	XMVECTOR GetLookAtVec();
	XMMATRIX GetViewMatrix();
	XMMATRIX GetProjectionMatrix();
	XMMATRIX GetViewProjectionMatrix();
	void SetViewMatrix();
	void SetProjectionMatrix();
	void SetViewProjectionMatrix();
	void SetCameraPos(XMVECTOR NewCameraPosition);
	void SetLookAtVec(XMVECTOR PositionLookingAt);
	HRESULT CreateBuffer(ID3D11Device* device);
	void SetConstantBuffer(ID3D11DeviceContext* gDeviceContext);

	

private:
	XMVECTOR m_cameraPos, m_lookAtVec;
	XMMATRIX m_view, m_projection, m_viewProjection;
	ID3D11Buffer* m_constCameraBuffer = nullptr;
	CameraType* m_constCamera;
	
};

#endif