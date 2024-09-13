#include "Camera.h"
#include "CommonInclude.h"
#include "DXInclude.h"

Camera* Camera::Instance = nullptr;

Camera::Camera(Vector3 position, Vector3 forward, Vector3 up)
	: _position(position), _forward(forward), _up(up)
{
}

void Camera::Init(Vector3 position, Vector3 forward, Vector3 up)
{
	Camera c(position, forward, up);
	Instance = &c;
}

D3DXMATRIX Camera::GetView() const
{
	D3DXMATRIX matView;

	// 뷰 행렬 생성 
	D3DXVECTOR3 cameraPos(_position.x, _position.y, _position.z); // 카메라 위치 
	D3DXVECTOR3 cameraAt(_position.x + _forward.x, _position.y + _forward.y, _position.z + _forward.z); // 시선 위치 
	D3DXVECTOR3 cameraUp(_up.x, _up.y, _up.z); // 위쪽 방향 

	D3DXMatrixLookAtLH(&matView,
		&cameraPos, // 카메라 위치 
		&cameraAt, // 시선 위치 
		&cameraUp); // 위쪽 방향 


	return matView;
}

D3DXMATRIX Camera::GetProjection() const
{
	D3DXMATRIX matProjection;
	// create a projection matrix
	D3DXMatrixPerspectiveFovLH(&matProjection,
		(FLOAT)D3DXToRadian(45),                    // field of view
		(FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT, // aspect ratio
		1.0f,                                       // near view-plane
		100.0f);                                    // far view-plane

	return matProjection;
}
