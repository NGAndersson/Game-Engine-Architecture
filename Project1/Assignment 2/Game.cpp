#include "Game.h"

Game::Game()
{

}

Game::~Game()
{
	if (m_swapChain != nullptr)
	{
		m_swapChain->Release();
	}
	if (m_backbufferRTV != nullptr)
	{
		m_backbufferRTV->Release();
	}
	if (m_depthStencilView != nullptr)
	{
		m_depthStencilView->Release();
	}
	if (m_depthStencil != nullptr)
	{
		m_depthStencil->Release();
	}
	if (m_sampleState != nullptr)
	{
		m_sampleState->Release();
	}
	if (m_deviceContext != nullptr)
	{
		m_deviceContext->Release();
	}
	if (m_device != nullptr)
	{
		m_device->Release();
	}

	delete m_display;
	m_display = 0;
	delete m_entitymanager;
}

void Game::InitGame(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Create inputclass
	m_display = new Display(hInstance, hPrevInstance, lpCmdLine, nCmdShow, m_width, m_height);


	HWND _hwnd = m_display->GethWnd();

	//Create and initialize device/devicecontext/swapchain/depthstenciel
	CreateDirect3DContext(_hwnd);
	

	//Sets the viewport
	SetViewport();
	m_entitymanager = new EntityManager();
	m_entitymanager->Initialize(m_device, m_deviceContext);
}

WPARAM Game::MainLoop(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Timer _time;
	static float _frameTime = 0.f;
	_time.StartTime();
	_time.TimeCheck();

	InitGame(hInstance,hPrevInstance,lpCmdLine,nCmdShow);//initialize the things that does not need ScreenWidh/m_height

	while (TRUE) {
		// Check to see if any messages are waiting in the queue
		while (PeekMessage(&m_winMSG, NULL, 0, 0, PM_REMOVE))
		{
			// translate keystroke messages into the right format
			TranslateMessage(&m_winMSG);

			

			// send the message to the WindowProc function
			DispatchMessage(&m_winMSG);
		}

		XMVECTOR move = XMVectorSet(0, 0, 0, 0);

		if (GetAsyncKeyState(0x57))
		{
			move += XMVectorSet(0, 0, 0.0001, 0);
		}
		if (GetAsyncKeyState(0x53))
		{
			move += XMVectorSet(0, 0, -0.0001, 0);
		}
		if (GetAsyncKeyState(0x41))
		{
			move += XMVectorSet(-0.0001, 0, 0, 0);
		}
		if (GetAsyncKeyState(0x44))
		{
			move += XMVectorSet(0.0001, 0, 0, 0);
		}
		//Finns inte ??
		m_entitymanager->CamUpd(m_deviceContext, move);

		// If the message is WM_QUIT, exit the while loop
		if (m_winMSG.message == WM_QUIT)
			return m_winMSG.wParam;

		float time = _time.TimeCheck();
		_frameTime += time;

		//Call update functions
		Update(time, hInstance, hPrevInstance, lpCmdLine, nCmdShow);



		//Call Render Functions
		if (_frameTime*1000.f >= 16.6f) {
			Render();
			m_swapChain->Present(0, 0);
			_frameTime = 0.f;
		}
	}

}

void Game::Update(double time, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	m_entitymanager->Update(time);
}

void Game::Render()
{

	// clear the back buffer to a deep blue
	float _clearColor[] = { 0, 0, 0, 1 };
	m_deviceContext->ClearRenderTargetView(m_backbufferRTV, _clearColor);
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);


	m_entitymanager->Render();

}

void Game::SetViewport()
{
	D3D11_VIEWPORT _viewport;
	_viewport.Width = (float)m_width;
	_viewport.Height = (float)m_height;
	_viewport.MinDepth = 0.0f;
	_viewport.MaxDepth = 1.0f;
	_viewport.TopLeftX = 0;
	_viewport.TopLeftY = 0;
	m_deviceContext->RSSetViewports(1, &_viewport);
}

HRESULT Game::CreateDirect3DContext(HWND wndHandle)
{
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC _swapChainDesc;

	// clear out the struct for use
	ZeroMemory(&_swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	_swapChainDesc.BufferCount = 1;                                    // one back buffer
	_swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	_swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	_swapChainDesc.OutputWindow = wndHandle;                           // the window to be used
	_swapChainDesc.SampleDesc.Count = 1;                               // how many multisamples
	_swapChainDesc.Windowed = TRUE;                                    // windowed/full-screen mode
	_swapChainDesc.BufferDesc.Width = m_width;
	_swapChainDesc.BufferDesc.Height = m_height;

	//														// create a device, device context and swap chain using the information in the scd struct
	HRESULT _hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&_swapChainDesc,
		&m_swapChain,
		&m_device,
		NULL,
		&m_deviceContext);

	//

	if (SUCCEEDED(_hr))
	{
		_hr = DepthStencilInitialicer(); //skapar depthstencil/desc 

		// get the address of the back buffer
		ID3D11Texture2D* _backBuffer = nullptr;
		m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&_backBuffer);

		// use the back buffer address to create the render target
		_hr = m_device->CreateRenderTargetView(_backBuffer,NULL, &m_backbufferRTV);
		_backBuffer->Release();

		// set the render target as the back buffer
		m_deviceContext->OMSetRenderTargets(1, &m_backbufferRTV, m_depthStencilView);

		// description for sampler
		D3D11_SAMPLER_DESC samplDesc;
		ZeroMemory(&samplDesc, sizeof(D3D11_SAMPLER_DESC));

		samplDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplDesc.MinLOD = 0;
		samplDesc.MaxLOD = D3D11_FLOAT32_MAX;

		// create the sampler
		_hr = m_device->CreateSamplerState(&samplDesc, &m_sampleState);
		//Set the sampler state
		m_deviceContext->PSSetSamplers(0, 1, &m_sampleState);
	}

	
	return _hr;
}

HRESULT Game::DepthStencilInitialicer()
{
	HRESULT _hr;

	//create the depth stencil
	D3D11_TEXTURE2D_DESC _descDepth;
	_descDepth.Width = m_width;
	_descDepth.Height = m_height;
	_descDepth.MipLevels = 1;
	_descDepth.ArraySize = 1;
	_descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	_descDepth.SampleDesc.Count = 1;
	_descDepth.SampleDesc.Quality = 0;
	_descDepth.Usage = D3D11_USAGE_DEFAULT;
	_descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	_descDepth.CPUAccessFlags = 0;
	_descDepth.MiscFlags = 0;
	_hr = m_device->CreateTexture2D(&_descDepth, NULL, &m_depthStencil);

	D3D11_DEPTH_STENCIL_VIEW_DESC ddesc;

	ddesc.Flags = 0;
	ddesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	ddesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	ddesc.Texture2D.MipSlice = 0;

	if (SUCCEEDED(_hr))
	{
		_hr = m_device->CreateDepthStencilView(m_depthStencil, NULL, &m_depthStencilView);
	}
	return _hr;
}
