#pragma once

#include "GameObject.h"
#include "Common.h"

class Triangle : public GameObject
{
	ID3D11Buffer* pVBuffer;                            // the vertex buffer

	// Vertext
	Vector3 _v1, _v2, _v3;

	Color _color;

	D3DXMATRIX matFinal;

public:
	Triangle(Vector3 position, Vector3 rotation, Vector3 v1, Vector3 v2, Vector3 v3, Color color);

	// Inherited via GameObject
	virtual void RenderTick() override;
};
