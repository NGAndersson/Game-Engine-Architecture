#include "EntityManager.h"
#include <iostream>



EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{

	delete m_shaderLoad;
	delete m_renderer;
	m_stackAllocator.ClearStack(true);
	m_stackAllocator.ClearStack(false);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_entityList[j]->GetLoD() == 9 && i == 2)
			{
				
			}
			else if (m_entityList[j]->GetLoD() == 0 && i == 0)
			{

			}
			else
			{
				delete m_modelHandlers[j][i];
			}
		}		
	}
}

void EntityManager::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	m_stackAllocator.Setup(MemoryManager::instance().GetMemory(sizeof(Entity) * 4), sizeof(Entity) * 4);

	//Set device and context
	m_device = device;
	m_deviceContext = deviceContext;

	//Set all asset pointers
	m_vAsset = reinterpret_cast<char*>(Loader::instance().Get("zip.vertexshader.hlsl"));
	m_gAsset = reinterpret_cast<char*>(Loader::instance().Get("zip.geometryshader.hlsl"));
	m_pAsset = reinterpret_cast<char*>(Loader::instance().Get("zip.pixelshader.hlsl"));

	//Create entities with position and the like
	m_entity1 = new(m_stackAllocator.Alloc(sizeof(Entity), true)) Entity(XMFLOAT3(0, 0, 10), XMFLOAT3(1, 1, 1), LoD);
	m_entityList.push_back(m_entity1);
	m_entity2 = new(m_stackAllocator.Alloc(sizeof(Entity), true)) Entity(XMFLOAT3(10, 0, 0), XMFLOAT3(1, 1, 1), LoD);
	m_entityList.push_back(m_entity2);
	m_entity3 = new(m_stackAllocator.Alloc(sizeof(Entity), true)) Entity(XMFLOAT3(0, 0, -10), XMFLOAT3(1, 1, 1), LoD);
	m_entityList.push_back(m_entity3);
	m_entity4 = new(m_stackAllocator.Alloc(sizeof(Entity), true)) Entity(XMFLOAT3(-10, 0, 0), XMFLOAT3(1, 1, 1), LoD);
	m_entityList.push_back(m_entity4);

	//Set the renderer
	m_renderer = new Renderer(m_deviceContext, m_device);
	//j are the differend models, i are the 3 modelhandlers belonging to each j. i = 1 is the current LoD distance, i = 0 is the LoD level for going forward and i = 2 is the LoD level for going backward
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			XMStoreFloat3(&m_camPos, m_renderer->GetCamera()->GetCameraPos());
			//Calculates distance in order to calculat the LoD, Level of Depth, which depends on the distance
			distance = sqrt((m_camPos.x - m_entityList[j]->GetPosition().x) * (m_camPos.x - m_entityList[j]->GetPosition().x) +
				(m_camPos.y - m_entityList[j]->GetPosition().y) * (m_camPos.y - m_entityList[j]->GetPosition().y) +
				(m_camPos.z - m_entityList[j]->GetPosition().z) * (m_camPos.z - m_entityList[j]->GetPosition().z));

			LoD = max(min(int(distance / 1), 9), 0);
			m_objAsset = Loader::instance().Get("zip.asset" + to_string(j) + ".obj");
			Loader::instance().Pin("zip.asset" + to_string(j) + ".obj");
			m_mtlAsset = Loader::instance().Get("zip.asset" + to_string(j) + ".lod" + to_string(min(max(LoD + (i % 3) - 1, 0), 9)) + ".mtl");
			m_modelHandlers[j][i] = new ModelHandler();
			m_modelHandlers[j][i]->LoadOBJData(m_objAsset, m_mtlAsset, m_device, m_deviceContext);
			Loader::instance().Free("zip.asset" + to_string(j) + ".obj");
			Loader::instance().Free("zip.asset" + to_string(j) + ".lod" + to_string(min(max(LoD + (i % 3) - 1, 0), 9)) + ".mtl");
			m_modelHandlers[j][i]->CreateBuffers(m_device);
			m_entityList[j]->SetLoD(LoD);
		}
	}

	//Create a dummy model handler, for edge LoDs and not-yet-loaded models
	m_modelHandlerDummy = new ModelHandler;
	m_modelHandlerDummy->LoadOBJData(Loader::instance().Get("zip.asset0.obj"), Loader::instance().Get("zip.dummy.mtl"), m_device, m_deviceContext);
	Loader::instance().Free("zip.asset0.obj"); Loader::instance().Free("zip.dummy.mtl");
	m_modelHandlerDummy->CreateBuffers(m_device);

	//Create Shaders
	m_shaderLoad = new ShaderHandler();
	m_shaderLoad->CreateShaders(m_device, m_vAsset, m_gAsset, m_pAsset); //<--- Detta är vad det ska bli efter att CreateShaders är omskriven
	

	XMVECTOR _rotatAxis{ 0, 1, 0, 0 };
	m_xmrot = XMMatrixRotationAxis(_rotatAxis, XM_PI);
}

void EntityManager::Render()
{
	m_shaderLoad->SetShaders(m_deviceContext);
	//m_modelHandlers1[1]->SetBuffers(m_deviceContext);
	for (int i = 0; i < 4; i++)
	{
		m_modelHandlers[i][1]->SetBuffers(m_deviceContext);
		//Always render [i][1] as the [1] refers to the middle LoD level for each model i, which is the one we're always actively seeing
		m_renderer->Render(m_modelHandlers[i][1], m_entityList[i]->GetPosition(), m_entityList[i]->GetRotation(), m_entityList[i]->GetScale());
	}
}

void EntityManager::Update(double time)
{
	XMStoreFloat3(&m_camPos, m_renderer->GetCamera()->GetCameraPos());
	for (int j = 0; j < m_entityList.size(); j++)
	{
		
		//Calculates distance in order to calculat the LoD, Level of Depth, which depends on the distance
		distance = sqrt((m_camPos.x - m_entityList[j]->GetPosition().x) * (m_camPos.x - m_entityList[j]->GetPosition().x) +
						(m_camPos.y - m_entityList[j]->GetPosition().y) * (m_camPos.y - m_entityList[j]->GetPosition().y) + 
						(m_camPos.z - m_entityList[j]->GetPosition().z) * (m_camPos.z - m_entityList[j]->GetPosition().z));

		int LoD = max(min(int(distance/ 1), 9), 0);

		if (m_entityList[j]->GetLoD() != LoD)
		{
			std::clock_t c_start, c_end, c_time, c_TotTime;
			c_start = std::clock();
			auto t_start = std::chrono::high_resolution_clock::now();
			if (m_entityList[j]->GetLoD() > LoD) //Move forward to the next LoD
			{
				
				if(m_modelHandlers[j][2] != m_modelHandlerDummy) delete m_modelHandlers[j][2];
				m_modelHandlers[j][2] = m_modelHandlers[j][1];
				m_modelHandlers[j][1] = m_modelHandlers[j][0];
				if (LoD != 0)
				{
					m_modelHandlers[j][0] = new ModelHandler;
					m_objAsset = Loader::instance().Get("zip.asset" + to_string(j) + ".obj");
					m_mtlAsset = Loader::instance().Get("zip.asset" + to_string(j) + ".lod" + to_string(LoD - 1) + ".mtl");
					//unsure if need to call on ~ModelHandler() and then new Modelhandler for [j][0] or if below is fine
					m_modelHandlers[j][0]->LoadOBJData(m_objAsset, m_mtlAsset, m_device, m_deviceContext);
					Loader::instance().Free("zip.asset" + to_string(j) + ".obj");
					Loader::instance().Free("zip.asset" + to_string(j) + ".lod" + to_string(LoD - 1) + ".mtl");
					m_modelHandlers[j][0]->CreateBuffers(m_device);
				}
				else m_modelHandlers[j][0] = m_modelHandlerDummy;
			}
			else if (m_entityList[j]->GetLoD() < LoD) //Move backward to the previous LoD
			{
				if (m_modelHandlers[j][0] != m_modelHandlerDummy) delete m_modelHandlers[j][0];
				m_modelHandlers[j][0] = m_modelHandlers[j][1];
				m_modelHandlers[j][1] = m_modelHandlers[j][2];
				if (LoD != 9)
				{
					m_modelHandlers[j][2] = new ModelHandler;
					m_objAsset = Loader::instance().Get("zip.asset" + to_string(j) + ".obj");
					m_mtlAsset = Loader::instance().Get("zip.asset" + to_string(j) + ".lod" + to_string(LoD + 1) + ".mtl");
					//unsure if need to call on ~ModelHandler() and then new Modelhandler for [j][2] or if below is fine
					m_modelHandlers[j][2]->LoadOBJData(m_objAsset, m_mtlAsset, m_device, m_deviceContext);
					Loader::instance().Free("zip.asset" + to_string(j) + ".obj");
					Loader::instance().Free("zip.asset" + to_string(j) + ".lod" + to_string(LoD + 1) + ".mtl");
					m_modelHandlers[j][2]->CreateBuffers(m_device);
				}
				else m_modelHandlers[j][2] = m_modelHandlerDummy;
			}
			m_entityList[j]->SetLoD(LoD); //Sets the current LoD to the entity so that it's updated for the next calculation
			
			c_end = std::clock();
			auto t_end = std::chrono::high_resolution_clock::now();

			std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
				<< 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
				<< "Wall clock time passed: "
				<< std::chrono::duration<double, std::milli>(t_end - t_start).count()
				<< " ms\n";
		}
		m_entityList[j]->Update(time);
	}
}

void EntityManager::CamUpd(ID3D11DeviceContext* m_deviceContext, XMVECTOR move)
{
	m_renderer->CamUpdate(m_deviceContext, move);
}