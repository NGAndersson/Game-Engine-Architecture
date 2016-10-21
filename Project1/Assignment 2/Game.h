#ifndef _GAME_H_
#define _GAME_H_

#include "Display.h"
#include "Camera.h"
#include "Timer.h"
#include <dxgidebug.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <iostream>
#include <vector>
#include <d3dcompiler.h>
#include "EntityManager.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

using namespace std;
using namespace DirectX;

class Game
{
private:
	void Update(double time, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	void Render();
	void SetViewport();
	HRESULT CreateDirect3DContext(HWND wndHandle);
	HRESULT DepthStencilInitialicer();

public:
	Game();
	~Game();
	void InitGame(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	WPARAM MainLoop(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

private:
	int m_width = 1920, m_height = 1280;
	Display* m_display;
	EntityManager* m_entitymanager;
	MSG m_winMSG;
	ID3D11DeviceContext* m_deviceContext = nullptr;
	ID3D11Device* m_device = nullptr;
	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11RenderTargetView* m_backbufferRTV = nullptr;
	ID3D11DepthStencilView* m_depthStencilView = nullptr;
	ID3D11Texture2D* m_depthStencil = nullptr;
	ID3D11SamplerState* m_sampleState = nullptr;
public:
};

#endif 

