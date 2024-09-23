#include "pch.h"
#include "types.h"
#include "Triangle.h"
#include "Game.h"

Triangle::Triangle(std::string name)
	: GameObject(name)
{
	{
		_vertices.resize(3);

		_vertices[0].position = Vec3(_position.x + - 0.5f, _position.y + -0.5f, _position.z + 0.f);
		_vertices[0].color = Color(1.f, 0.f, 0.f, 1.f);
		_vertices[1].position = Vec3(_position.x + 0.f, _position.y + 0.5f, _position.z + 0.f);
		_vertices[1].color = Color(0.f, 1.f, 0.f, 1.f);
		_vertices[2].position = Vec3(_position.x + 0.5f, _position.y + -0.5f, _position.z + 0.f);
		_vertices[2].color = Color(0.f, 0.f, 1.f, 1.f);
	}

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.ByteWidth = (uint32)(sizeof(Vertex) * _vertices.size());

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = _vertices.data();

	Game::GetDevice().CreateBuffer(&desc, &data, &_vertexBuffer);

}

void Triangle::GameUpdate()
{
}

void Triangle::RenderUpdate()
{
	GameObject::RenderUpdate();

	D3D11_MAPPED_SUBRESOURCE resource;
	ZeroMemory(&resource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	// Map the buffer to gain write access
	HRESULT hr = Game::GetDeviceContext().Map(_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);

	if (SUCCEEDED(hr))
	{
		// Assuming vertices are of a custom struct type like VertexType
		Vertex* vertices = (Vertex*)resource.pData;

		{
			vertices[0].position = Vec3(_position.x + -0.5f, _position.y + -0.5f, _position.z + 0.f);
			vertices[0].color = Color(1.f, 0.f, 0.f, 1.f);
			vertices[1].position = Vec3(_position.x + 0.f, _position.y + 0.5f, _position.z + 0.f);
			vertices[1].color = Color(0.f, 1.f, 0.f, 1.f);
			vertices[2].position = Vec3(_position.x + 0.5f, _position.y + -0.5f, _position.z + 0.f);
			vertices[2].color = Color(0.f, 0.f, 1.f, 1.f);
		}

		Game::GetDeviceContext().Unmap(_vertexBuffer, 0);
	}

	uint32 stride = sizeof(Vertex);
	uint32 offset = 0;

	// IA
	Game::GetDeviceContext().IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
	Game::GetDeviceContext().IASetInputLayout(&Game::GetDefaultInputLayout());
	Game::GetDeviceContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// VS
	Game::UseDefaultShader();

	// OM

	Game::GetDeviceContext().Draw(_vertices.size(), 0);
}
