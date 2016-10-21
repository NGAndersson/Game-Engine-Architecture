#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "ModelHandler.h"
#include <DirectXMath.h>
#include <d3d11.h>
#include "Camera.h"

class Renderer
{
	//Cam buffer for GS
	struct CamStruct {
		XMFLOAT4 camPos;
		XMMATRIX viewProjection;
	};

	//World buffer for VS
	struct WorldStruct {
		XMMATRIX worldMatrix;
		XMMATRIX worldRotation;
	};

	//World buffer for VS
	struct WorldStructInstanced {
		XMFLOAT4X4 worldMatrix[100];
		XMFLOAT4X4 worldRotation[100];
	};

//Functions
private:

public:
	~Renderer();

	void Render(ModelHandler* model, XMFLOAT3 position, XMMATRIX &rotation, XMFLOAT3 scale);
	void RenderInstanced(ModelHandler * model, vector<XMFLOAT3> position, vector<XMMATRIX> &rotation, int amountOfBullets, vector<XMFLOAT3> scale);
	Renderer(ID3D11DeviceContext* deviceContext, ID3D11Device* device);
	void CamUpdate(ID3D11DeviceContext* deviceContext, XMVECTOR direction);

//Variables
private:
	ID3D11DeviceContext* m_deviceContext = nullptr;
	ID3D11Device* m_device = nullptr;

	WorldStruct m_worldStruct;
	WorldStructInstanced m_worldStructInstanced;
	ID3D11Buffer* m_worldBuffer = nullptr, *m_worldBufferInstance = nullptr;
	Camera m_cam;

public:

};

#endif
