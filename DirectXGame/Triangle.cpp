#include "pch.h"
#include "types.h"
#include "Triangle.h"
#include "Game.h"

Triangle::Triangle()
{
	{
		_vertices.resize(3);

		_vertices[0].position = Vec3(-0.5f, -0.5f, 0.f);
		_vertices[0].color = Color(1.f, 0.f, 0.f, 1.f);
		_vertices[1].position = Vec3(0.f, 0.5f, 0.f);
		_vertices[1].color = Color(0.f, 1.f, 0.f, 1.f);
		_vertices[2].position = Vec3(0.5f, -0.5f, 0.f);
		_vertices[2].color = Color(0.f, 0.f, 1.f, 1.f);
	}

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
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
