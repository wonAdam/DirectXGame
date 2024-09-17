#pragma once

#include "types.h"

class Game
{
public:
	Game();
	~Game();

	static const int32 GWinSizeX;
	static const int32 GWinSizeY;

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	void InitDevice();
	void InitViewport();
	bool InitShader();

private:
	HWND _hwnd;
	uint32 _width = 0;
	uint32 _height = 0;

private:
	// DX
	ID3D11Device* dev;                     // the pointer to our Direct3D device interface
	ID3D11DeviceContext* devcon;           // the pointer to our Direct3D device context
	IDXGISwapChain* swapchain;             // the pointer to the swap chain interface
	ID3D11RenderTargetView* backbuffer;    
	ID3D11DepthStencilView* zbuffer;	

	ID3D11VertexShader* pVS;    // the vertex shader
	ID3D11PixelShader* pPS;     // the pixel shader
};

