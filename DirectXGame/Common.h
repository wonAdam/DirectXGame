#pragma once

#include "DXInclude.h"

struct VERTEX
{
    FLOAT X, Y, Z;      // position
    D3DXCOLOR Color;    // color
};

struct Vector3 {

    float x, y, z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct Color {
    float r, g, b, a;

    Color() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
    Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}
};