#pragma once

#include "types.h"

class Game
{
public:
	Game();
	~Game();

	static const int32 GWinSizeX;
	static const int32 GWinSizeY;

	static Game& Get() { return *_instance;  }

	static ID3D11Device& GetDevice() { return *Get()._dev; }
	static ID3D11DeviceContext& GetDeviceContext() { return *Get()._devcon; }
	static ID3DBlob& GetVSBlob() { return *Get()._vsBlob; }
	static ID3D11InputLayout& GetDefaultInputLayout() { return *Get()._inputLayout; }

	static void UseDefaultShader();

private:
	static unique_ptr<Game> _instance;

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	void InitDevice();
	void InitImGui();
	void InitViewport();
	bool InitShader();

private:
	HWND _hwnd;
	uint32 _width = 0;
	uint32 _height = 0;

private:
	// DX
	ID3D11Device* _dev;                     // the pointer to our Direct3D device interface
	ID3D11DeviceContext* _devcon;           // the pointer to our Direct3D device context
	IDXGISwapChain* _swapchain;             // the pointer to the swap chain interface
	ID3D11RenderTargetView* _backbuffer;    
	ID3D11DepthStencilView* _zbuffer;	

	ID3D11VertexShader* _pVS;    // the vertex shader
	ID3D11PixelShader* _pPS;     // the pixel shader
	ID3DBlob* _vsBlob = nullptr;
	ID3DBlob* _psBlob = nullptr;
	ID3D11InputLayout* _inputLayout = nullptr;
	D3D11_VIEWPORT _viewport;

	class Triangle* t = nullptr;
	class Triangle* t2 = nullptr;

	bool _bDummyCheckbox = false;
	float _dummyFloat = 0.0f;
	float _dummyColor[3];
	int _dummyCounter = 0;
};

