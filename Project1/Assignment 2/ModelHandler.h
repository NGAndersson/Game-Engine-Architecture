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
	bool LoadOBJData(string OBJFileName, string colourFileName, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	bool CreateBuffers(ID3D11Device* device);
	bool SetBuffers(ID3D11DeviceContext* deviceContext);
	void beatBoost(bool beat, float time, float timeSinceLast, float BPM);
	int GetVertexCount();
	XMFLOAT3 GetDeffuse();

private:
	XMFLOAT3* m_vertices,* m_normals, *m_RGBDeffuse, *m_RGBAL, *m_Tf, *m_Ni;
	XMFLOAT2* m_texcoords;
	int m_vertexCount, m_textureCount, m_normalCount, m_faceCount, m_kdCount, m_kaCount, m_tfCount, m_niCount;
	FaceType* m_faces;
	OBJLoader m_OBJLoad;
	ID3D11Buffer* m_vertexBuffer = nullptr, *m_OBJColourBuffer = nullptr;
	ID3D11ShaderResourceView* m_ObjTex = nullptr;
	VertexInputType* m_vertexInput;
	float m_beatBoost = 1;
	float m_beatTime = 0;
	OBJColourType _OBJColour;
};

#endif
