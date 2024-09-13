#pragma once
#include "Common.h"

class Camera
{
	static Camera* Instance;

	Vector3 _position, _forward, _up;

	Camera(Vector3 position, Vector3 forward, Vector3 up);

public:
	static void Init(Vector3 position, Vector3 forward, Vector3 up);

	D3DXMATRIX GetView() const;
	D3DXMATRIX GetProjection() const;

	static const Camera& Get() { return *Instance; }
};

