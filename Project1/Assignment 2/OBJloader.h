#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <iostream>
#include <vector>
#include <d3dcompiler.h>
#include <WICTextureLoader.h>
#include <sstream>

#include "Loader.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "DirectXTK.lib")

using namespace std;
using namespace DirectX;


typedef struct
{
	int vIndex1, vIndex2, vIndex3;
	int tIndex1, tIndex2, tIndex3;
	int nIndex1, nIndex2, nIndex3;
}FaceType;

typedef struct
{
	XMFLOAT3 position;
	XMFLOAT2 uv;
	XMFLOAT3 normal;
}VertexInputType;

class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();
	ID3D11ShaderResourceView* LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext,void* texFile);
	VertexInputType* LoadObj(int& vertexCount, int& textureCount, int& normalCount, int& faceCount,void* file);//file is the obj loader remade to a char array.
	bool ReadColourCounts(int& vertexCount, int& textureCount, int& normalCount, int& faceCount, string fileName);
	ID3D11ShaderResourceView* LoadColour(ID3D11Device* device, ID3D11DeviceContext* deviceContext, void* file, XMFLOAT3 *RGBDeffuse, XMFLOAT3 *RGBAL, XMFLOAT3 *Tf, XMFLOAT3 *Ni, ID3D11ShaderResourceView** m_ObjTex);
};

#endif