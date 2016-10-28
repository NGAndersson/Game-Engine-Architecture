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
#include "MemoryManager.h"
#include "StackAllocator.h"

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
	void CamUpd(ID3D11DeviceContext* m_deviceContext, XMVECTOR move);

	//Variables
private:
	//Vectors with all the different types of entities
	ShaderHandler* m_shaderLoad;
	ModelHandler* m_modelHandlers [4][3];

	vector<Entity*> m_entityList;
	void* m_objAsset; //should be a pointer of type ModelHandler or OBJ or whatever depending on what format we choose to do it in
	void* m_mtlAsset;
	char* m_vAsset;
	char* m_gAsset;
	char* m_pAsset;
	int LoD = 5;
	float distance;
	XMFLOAT3 m_camPos;
	XMFLOAT3 m_entityPos;
	//Camera m_cam;
	Renderer* m_renderer;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	XMMATRIX m_xmrot;
	StackAllocator m_stackAllocator;
public:
	Entity* m_entity1;
	Entity* m_entity2;
	Entity* m_entity3;
	Entity* m_entity4;
};

#endif // !_ENTITYMANAGER_H
