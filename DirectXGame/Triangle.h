﻿#pragma once
#include "GameObject.h"
class Triangle : public GameObject
{
public:
	Triangle(std::string name);

	virtual void GameUpdate() override;
	virtual void RenderUpdate() override;

private:
	vector<Vertex> _vertices;
	ID3D11Buffer* _vertexBuffer = nullptr;


};

