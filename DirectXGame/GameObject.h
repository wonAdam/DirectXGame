#pragma once

#include "Common.h"

class GameObject {
protected:
    Vector3 _position;
    Vector3 _rotation;

    GameObject(Vector3 position, Vector3 rotation)
        : _position(position), _rotation(rotation) {}

public:
    virtual void RenderTick() = 0;

    void Translate(Vector3 translation) {
        _position.x += translation.x;
        _position.y += translation.y;
        _position.z += translation.z;
    }

    void Rotate(Vector3 rotation) {
        _rotation.x += rotation.x;
        _rotation.y += rotation.y;
        _rotation.z += rotation.z;
    }
};


