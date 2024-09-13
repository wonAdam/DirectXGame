#pragma once
#include <windows.h>
#include <windowsx.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <D3DX10math.h>

extern ID3D11DeviceContext* devcon;           // the pointer to our Direct3D device context
extern ID3D11Device* dev;                     // the pointer to our Direct3D device interface
extern ID3D11Buffer* pCBuffer; // constant buffer
