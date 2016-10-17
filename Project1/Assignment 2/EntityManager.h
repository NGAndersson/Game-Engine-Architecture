#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H
#include "Entity.h"
#include <vector>
#include "Renderer.h"
#include "ShaderHandler.h"
#include "ModelHandler.h"
#include "Loader.h"
#include <d3d11.h>
#include <random>
#include <memory>
#include "Camera.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")


class EntityManager
{
	//Functions
private:

public:
	EntityManager();
	~EntityManager();
	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Render();
	void Update(double time);

	//Variables
private:
	//Vectors with all the different types of entities
	ShaderHandler* m_shaderLoad;
	ModelHandler* m_modelHandler;

	Loader m_loader;
	void* m_tempAsset;
	char* m_objAsset; //should be a pointer of type ModelHandler or OBJ or whatever depending on what format we choose to do it in
	char* m_mtlAsset;
	char* m_vAsset;
	char* m_gAsset;
	char* m_pAsset;
	int LoD = 0;
	XMFLOAT3 m_camPos;
	XMFLOAT3 m_entityPos;
	Camera m_cam;
	Renderer* m_renderer;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	XMMATRIX m_xmrot;
public:
	Entity* m_entity;
};

#endif // !_ENTITYMANAGER_H
