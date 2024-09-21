#include "pch.h"
#include "Game.h"
#include "Triangle.h"

const int32 Game::GWinSizeX = 800;
const int32 Game::GWinSizeY = 600;

unique_ptr<Game> Game::_instance;

Game::Game()
{
    _instance = unique_ptr<Game>(this);
}

Game::~Game()
{

}

void Game::UseDefaultShader()
{
    auto& devcon = GetDeviceContext();

    devcon.VSSetShader(Get()._pVS, nullptr, 0);
    devcon.PSSetShader(Get()._pPS, nullptr, 0);
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_width = GWinSizeX;
	_height = GWinSizeY;

    InitDevice();
    InitViewport();
    InitShader();

    t = new Triangle();
}

void Game::InitDevice()
{
    // create a struct to hold information about the swap chain
    DXGI_SWAP_CHAIN_DESC scd;

    // clear out the struct for use
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // fill the swap chain description struct
    scd.BufferCount = 1;                                    // one back buffer
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
    scd.BufferDesc.Width = GWinSizeX;                       // set the back buffer width
    scd.BufferDesc.Height = GWinSizeY;                      // set the back buffer height
    scd.OutputWindow = _hwnd;                               // the window to be used
    scd.SampleDesc.Count = 1;                               // how many multisamples
    scd.Windowed = TRUE;                                    // windowed/full-screen mode
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow full-screen switching

    // create a device, device context and swap chain using the information in the scd struct
    D3D11CreateDeviceAndSwapChain(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        NULL,
        NULL,
        NULL,
        D3D11_SDK_VERSION,
        &scd,
        &_swapchain,
        &_dev,
        NULL,
        &_devcon);

}

void Game::InitViewport()
{
    D3D11_TEXTURE2D_DESC texd;
    ZeroMemory(&texd, sizeof(texd));

    texd.Width = GWinSizeX;
    texd.Height = GWinSizeY;
    texd.ArraySize = 1;
    texd.MipLevels = 1;
    texd.SampleDesc.Count = 4;
    texd.Format = DXGI_FORMAT_D32_FLOAT;
    texd.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    ID3D11Texture2D* pDepthBuffer;
    _dev->CreateTexture2D(&texd, NULL, &pDepthBuffer);

    D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
    ZeroMemory(&dsvd, sizeof(dsvd));

    dsvd.Format = DXGI_FORMAT_D32_FLOAT;
    dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

    _dev->CreateDepthStencilView(pDepthBuffer, &dsvd, &_zbuffer);
    pDepthBuffer->Release();

    // get the address of the back buffer
    ID3D11Texture2D* pBackBuffer;
    _swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // use the back buffer address to create the render target
    _dev->CreateRenderTargetView(pBackBuffer, NULL, &_backbuffer);
    pBackBuffer->Release();

    // set the render target as the back buffer
    _devcon->OMSetRenderTargets(1, &_backbuffer, _zbuffer);

    // Set the viewport
    ZeroMemory(&_viewport, sizeof(D3D11_VIEWPORT));

    _viewport.TopLeftX = 0;
    _viewport.TopLeftY = 0;
    _viewport.Width = GWinSizeX;
    _viewport.Height = GWinSizeY;
    _viewport.MinDepth = 0; 
    _viewport.MaxDepth = 1; 

    _devcon->RSSetViewports(1, &_viewport);
}

bool Game::InitShader()
{
    const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

    HRESULT hr1_0 = D3DCompileFromFile(
        L"Default.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VS",
        "vs_5_0",
        0,
        compileFlag,
        &_vsBlob,
        nullptr);

    if (FAILED(hr1_0))
    {
        if (_vsBlob)
        {
            OutputDebugStringA((char*)_vsBlob->GetBufferPointer());
            _vsBlob->Release();
            return false;
        }
    }

    if (!_vsBlob)
    {
        return false;
    }

    HRESULT hr1_1 = _dev->CreateVertexShader(_vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), nullptr, &_pVS);

    if (FAILED(hr1_1))
    {
        if (_vsBlob)
        {
            OutputDebugStringA((char*)_vsBlob->GetBufferPointer());
            _vsBlob->Release();
            return false;
        }
    }


    HRESULT hr2_0 = D3DCompileFromFile(
        L"Default.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PS",
        "ps_5_0",
        0,
        compileFlag,
        &_psBlob,
        nullptr);
    if (FAILED(hr2_0))
    {
        if (_psBlob)
        {
            OutputDebugStringA((char*)_psBlob->GetBufferPointer());
            _psBlob->Release();
            return false;
        }
    }

    if (!_psBlob)
    {
        return false;
    }

    HRESULT hr2_1 = _dev->CreatePixelShader(_psBlob->GetBufferPointer(), _psBlob->GetBufferSize(), nullptr, &_pPS);
    if (FAILED(hr2_1))
    {
        if (_psBlob)
        {
            OutputDebugStringA((char*)_psBlob->GetBufferPointer());
            _psBlob->Release();
            return false;
        }
    }

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);
    _dev->CreateInputLayout(layout, count, _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), &_inputLayout);

    return true;
}

void Game::Update()
{

}

void Game::Render()
{
    static const float _clearColor[4] = { 0.f, 0.f, 0.f, 0.f };

    // Render Begin
    {
        _devcon->OMSetRenderTargets(1, &_backbuffer, nullptr);
        _devcon->ClearRenderTargetView(_backbuffer, _clearColor);
        _devcon->RSSetViewports(1, &_viewport);
    }

    t->RenderUpdate();

    // Render End
    {
        _swapchain->Present(1, 0);
    }
}
