#ifndef _MODELHANDLER_H_
#define _MODELHANDLER_H_

#include "OBJloader.h"

class ModelHandler
{
private:
	struct OBJColourType
	{
		XMFLOAT3 Deffuse;
		XMFLOAT3 Albi;
		XMFLOAT3 Tf;
		XMFLOAT3 Ni;
	};
public:
	ModelHandler();
	~ModelHandler();
	bool LoadOBJData(void* file, string colourFileName, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	bool CreateBuffers(ID3D11Device* device);
	bool SetBuffers(ID3D11DeviceContext* deviceContext);
	int GetVertexCount();
	XMFLOAT3 GetDeffuse();

private:
	XMFLOAT3* m_vertices,* m_normals, *m_RGBDeffuse, *m_RGBAL, *m_Tf, *m_Ni;
	XMFLOAT2* m_texcoords;
	int m_vertexCount = 0, m_textureCount = 0, m_normalCount = 0, m_faceCount = 0, m_kdCount = 0, m_kaCount = 0, m_tfCount = 0, m_niCount = 0;
	FaceType* m_faces;
	OBJLoader m_OBJLoad;
	ID3D11Buffer* m_vertexBuffer = nullptr, *m_OBJColourBuffer = nullptr;
	ID3D11ShaderResourceView* m_ObjTex = nullptr;
	VertexInputType* m_vertexInput;
	OBJColourType _OBJColour;
};

#endif
