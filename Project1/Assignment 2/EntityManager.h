#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H
#include "Entity.h"
#include <vector>
#include "Renderer.h"
#include "ShaderHandler.h"
#include "ModelHandler.h"
#include <d3d11.h>
#include <random>
#include <memory>

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
	Entity* m_entity;

	Renderer* m_renderer;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	XMMATRIX m_xmrot;
public:

};

#endif // !_ENTITYMANAGER_H
