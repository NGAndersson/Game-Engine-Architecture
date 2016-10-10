#ifndef ENTITY_H
#define ENTITY_H
//Temporary include
#include <DirectXCollision.h>
#include <DirectXMath.h>
using namespace DirectX;


class Entity
{
	//----------------------------Functions----------------------------------------
public:
	Entity() 
	{
		m_speed = 0;
	}
	~Entity() {}
	Entity(XMFLOAT3 Position, XMFLOAT3 Scale);

	void Update(double time);

	 //Get set 
	 XMFLOAT3 GetPosition(){return m_position;}

	 void SetPosition(XMFLOAT3 newPos) { m_position = newPos; }

	 XMMATRIX GetRotation(){ return m_rotation; }

	 XMFLOAT3 GetScale() { return m_scale; }

	 void SetScale(XMFLOAT3 newScale) { m_scale = newScale; }

	 virtual float GetSpeed() { return m_speed; }

	//----------------------------Attributes----------------------------------------
protected:
	 //Position // Rotation
	 XMFLOAT3 m_position;
	 XMMATRIX m_rotation;
	 XMFLOAT3 m_scale;
	 float m_rot = XM_PI;
	 float m_speed;
};
#endif // ! ENTITY