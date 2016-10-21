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
	ModelHandler* m_modelHandlers [4][3];
	ModelHandler* m_modelHandlers1[3];
	ModelHandler* m_modelHandlers2[3];
	ModelHandler* m_modelHandlers3[3];
	ModelHandler* m_modelHandlers4[3];

	vector<Entity*> m_entityList;
	Loader Loader::instance();
	void* m_objAsset; //should be a pointer of type ModelHandler or OBJ or whatever depending on what format we choose to do it in
	void* m_mtlAsset;
	void* m_vAsset;
	void* m_gAsset;
	void* m_pAsset;
	int LoD = 5;
	float distance;
	XMFLOAT3 m_camPos;
	XMFLOAT3 m_entityPos;
	Camera m_cam;
	Renderer* m_renderer;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	XMMATRIX m_xmrot;
public:
	Entity* m_entity1;
	Entity* m_entity2;
	Entity* m_entity3;
	Entity* m_entity4;
};

#endif // !_ENTITYMANAGER_H
