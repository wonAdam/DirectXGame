#pragma once
class GameObject
{
public:
	virtual void GameUpdate() = 0;
	virtual void RenderUpdate() = 0;
};

