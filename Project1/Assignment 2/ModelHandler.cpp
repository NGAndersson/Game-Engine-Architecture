#include "ModelHandler.h"

ModelHandler::ModelHandler()
{
	
}

ModelHandler::~ModelHandler()
{
	delete[] m_vertices;
	delete[] m_normals;
	delete[] m_texcoords;
	delete[] m_RGBDeffuse;
	delete[] m_RGBAL;
	delete[] m_Tf;
	delete[] m_Ni;
	delete[] m_faces;
	delete[] m_vertexInput;
	if (m_vertexBuffer != nullptr)
	{
		m_vertexBuffer->Release();
	}
	if (m_OBJColourBuffer != nullptr)
	{
		m_OBJColourBuffer->Release();
	}
	if (m_ObjTex != nullptr)
	{
		m_ObjTex->Release();
	}
}

bool ModelHandler::LoadOBJData(void* file, void* colourFileName, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	bool _ifOK;

	m_vertexInput = m_OBJLoad.LoadObj(m_vertexCount, m_textureCount, m_normalCount, m_faceCount, file);

	//Sets amount of kd, ka, tf and ni counts for the file
	_ifOK = m_OBJLoad.ReadColourCounts(m_kdCount, m_kaCount, m_tfCount, m_niCount, colourFileName);
	if (_ifOK == false)
	{
		return false;
	}

	// Initialize the four data structures.
	m_RGBDeffuse = new XMFLOAT3[m_kdCount];
	if (!m_RGBDeffuse)
	{
		return false;
	}

	m_RGBAL = new XMFLOAT3[m_kaCount];
	if (!m_RGBAL)
	{
		return false;
	}

	m_Tf = new XMFLOAT3[m_tfCount];
	if (!m_Tf)
	{
		return false;
	}

	m_Ni = new XMFLOAT3[m_niCount];
	if (!m_Ni)
	{
		return false;
	}

	//Loads the colour data from file
	m_OBJLoad.LoadColour(device, deviceContext, colourFileName, m_RGBDeffuse, m_RGBAL, m_Tf, m_Ni, &m_ObjTex);
	return true;
}

bool ModelHandler::CreateBuffers(ID3D11Device* device)
{
	D3D11_BUFFER_DESC _OBJvertexBufferDesc, _OBJColDesc;
	D3D11_SUBRESOURCE_DATA _OBJvertexData;

	// description for vertexbuffer
	_OBJvertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	_OBJvertexBufferDesc.ByteWidth = sizeof(float) * 8 * (m_faceCount * 3);
	_OBJvertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	_OBJvertexBufferDesc.CPUAccessFlags = 0;
	_OBJvertexBufferDesc.MiscFlags = 0;
	_OBJvertexBufferDesc.StructureByteStride = 0;


	_OBJvertexData.pSysMem = m_vertexInput;
	_OBJvertexData.SysMemPitch = 0;
	_OBJvertexData.SysMemSlicePitch = 0;

	// Creates vertex buffern
	device->CreateBuffer(&_OBJvertexBufferDesc, &_OBJvertexData, &m_vertexBuffer);

	

	ZeroMemory(&_OBJColDesc, sizeof(D3D11_BUFFER_DESC));

	_OBJColDesc.Usage = D3D11_USAGE_DYNAMIC;
	_OBJColDesc.ByteWidth = sizeof(OBJColourType);
	_OBJColDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_OBJColDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_OBJColDesc.MiscFlags = 0;

	//skapar constant buffer
	device->CreateBuffer(&_OBJColDesc, NULL, &m_OBJColourBuffer);

	return true;
}

bool ModelHandler::SetBuffers(ID3D11DeviceContext* deviceContext)
{
	D3D11_MAPPED_SUBRESOURCE _mappedResource;

 	HRESULT hr = deviceContext->Map(m_OBJColourBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_mappedResource);

	_OBJColour.Deffuse = XMFLOAT3(m_RGBDeffuse[0].x, m_RGBDeffuse[0].y, m_RGBDeffuse[0].z);
	_OBJColour.Albi = m_RGBAL[0];
	_OBJColour.Ni = m_Tf[0];
	_OBJColour.Tf = m_Ni[0];

	memcpy(_mappedResource.pData, &_OBJColour, sizeof(OBJColourType));

	deviceContext->Unmap(m_OBJColourBuffer, 0);


	UINT32 _vertexSize = sizeof(float) * 8;
	UINT32 _offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &_vertexSize, &_offset);

	deviceContext->PSSetConstantBuffers(0, 1, &m_OBJColourBuffer);
	deviceContext->PSSetShaderResources(0, 1, &m_ObjTex);

	return true;
}

int ModelHandler::GetVertexCount()
{
	return m_faceCount;
}

XMFLOAT3 ModelHandler::GetDeffuse()
{
	XMFLOAT3 _colour = m_RGBDeffuse[0];
	return _colour;
}