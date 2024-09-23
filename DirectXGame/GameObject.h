#pragma once
#include "types.h"

class GameObject
{
public:
	GameObject(std::string name);
	virtual ~GameObject();

	virtual void GameUpdate() = 0;
	virtual void RenderUpdate();

	void UseDebug() { _bUseDebugPanel = true; }

protected:
	std::string _name;

	Vec3 _position; // 임시적으로 화면 position

private:
	bool _bUseDebugPanel = false;
};

