#include "pch.h"
#include "Game.h"

const int32 Game::GWinSizeX = 800;
const int32 Game::GWinSizeY = 600;

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_width = GWinSizeX;
	_height = GWinSizeY;

    InitDevice();
    InitViewport();
    InitShader();
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
    scd.BufferDesc.Width = GWinSizeX;                    // set the back buffer width
    scd.BufferDesc.Height = GWinSizeY;                  // set the back buffer height
    scd.OutputWindow = _hwnd;                                // the window to be used
    scd.SampleDesc.Count = 4;                               // how many multisamples
    scd.Windowed = TRUE;                                    // windowed/full-screen mode
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow full-screen switching

    // create a device, device context and swap chain using the information in the scd struct
    D3D11CreateDeviceAndSwapChain(NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        NULL,
        NULL,
        NULL,
        D3D11_SDK_VERSION,
        &scd,
        &swapchain,
        &dev,
        NULL,
        &devcon);

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
    dev->CreateTexture2D(&texd, NULL, &pDepthBuffer);

    D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
    ZeroMemory(&dsvd, sizeof(dsvd));

    dsvd.Format = DXGI_FORMAT_D32_FLOAT;
    dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

    dev->CreateDepthStencilView(pDepthBuffer, &dsvd, &zbuffer);
    pDepthBuffer->Release();

    // get the address of the back buffer
    ID3D11Texture2D* pBackBuffer;
    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // use the back buffer address to create the render target
    dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
    pBackBuffer->Release();

    // set the render target as the back buffer
    devcon->OMSetRenderTargets(1, &backbuffer, zbuffer);

    // Set the viewport
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = GWinSizeX;
    viewport.Height = GWinSizeY;
    viewport.MinDepth = 0; // 객체가 깊이 버퍼에 가장 가까이 있을 수 있는 최대값은 0.0입니다 
    viewport.MaxDepth = 1; // 객체가 깊이 버퍼에 가장 멀리 있을 수 있는 최대값은 1.0입니다

    devcon->RSSetViewports(1, &viewport);
}

bool Game::InitShader()
{
    // load and compile the two shaders
    ID3DBlob* vsBlob = nullptr;
    ID3DBlob* psBlob = nullptr;

    const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

    HRESULT hr1_0 = D3DCompileFromFile(
        L"Default.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VS",
        "vs_5_0",
        0,
        compileFlag,
        &vsBlob,
        nullptr);

    if (FAILED(hr1_0))
    {
        if (vsBlob)
        {
            OutputDebugStringA((char*)vsBlob->GetBufferPointer());
            vsBlob->Release();
            return false;
        }
    }

    if (!vsBlob)
    {
        return false;
    }

    HRESULT hr1_1 = dev->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &pVS);

    if (FAILED(hr1_1))
    {
        if (vsBlob)
        {
            OutputDebugStringA((char*)vsBlob->GetBufferPointer());
            vsBlob->Release();
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
        &psBlob,
        nullptr);
    if (FAILED(hr2_0))
    {
        if (psBlob)
        {
            OutputDebugStringA((char*)psBlob->GetBufferPointer());
            psBlob->Release();
            return false;
        }
    }

    if (!psBlob)
    {
        return false;
    }

    HRESULT hr2_1 = dev->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pPS);
    if (FAILED(hr2_1))
    {
        if (psBlob)
        {
            OutputDebugStringA((char*)psBlob->GetBufferPointer());
            psBlob->Release();
            return false;
        }
    }

    return true;
}

void Game::Update()
{

}

void Game::Render()
{

}
