#ifndef _SHADERHANDLER_H_
#define _SHADERHANDLER_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <iostream>
#include <vector>
#include <d3dcompiler.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

using namespace std;
using namespace DirectX;

class ShaderHandler
{
public:
	ShaderHandler();
	~ShaderHandler();
	bool CreateShaders(ID3D11Device* device, string vertexFile, string geometryFile, string pixelFile);
	bool CreateShadersPosOnly(ID3D11Device* device, string vertexFile, string geometryFile, string pixelFile);
	bool CreatePlayerFireShaders(ID3D11Device* device, string vertexFile, string geometryFile, string pixelFile);
	bool CreateShadersCompute(ID3D11Device* device,string computeFile);
	bool SetShaders(ID3D11DeviceContext* deviceContext);
	void SetComputeShader(ID3D11DeviceContext* deviceContext,int Pass);

private:
	ID3D11InputLayout* m_vertexLayout = nullptr;
	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11GeometryShader* m_geometryShader = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11ComputeShader* m_computeShaderPass1 = nullptr;
	ID3D11ComputeShader* m_computeShaderPass2 = nullptr;

};

#endif