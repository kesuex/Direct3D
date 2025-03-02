#include "Renderer.h"
#include <Window/Window.h>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>

std::string GetProjectDirectory()
{
	std::string fullpath = __FILE__;
	size_t found = fullpath.find_last_of("\\/");
	if (found != std::string::npos)
	{
		std::string projectDir = fullpath.substr(0, found);
		
		found = projectDir.find_last_of("\\/");
		if (found != std::string::npos)
		{
			return projectDir.substr(0, found);
		}		
		
	}
	return "";
}

std::string ReadHLSLFile(const std::string& filename)
{
	std::string absolutePath = GetProjectDirectory() + "/Shaders/" + filename;
	std::ifstream file(absolutePath);
	if (!file.is_open())
	{
		std::cerr << "Error: Failed to open file " << absolutePath << std::endl;
		return "";
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();

	return buffer.str();
}

Renderer::Renderer(Window* pWindow) : mWindow(pWindow), mDevice(nullptr), mDeviceContext(nullptr), 
										mSwapchain(nullptr), mRenderTargetView(nullptr)
{
	CreateDevice();
	CreateSwapchain();
	CreateRenderTargetView();
	CreateShaders();
	CreateInputLayout();
}

void Renderer::CreateDevice()
{
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels, 1,
		D3D11_SDK_VERSION, mDevice.GetAddressOf(), nullptr, mDeviceContext.GetAddressOf())))
	{
		printf("Failed to create device");
		abort();

	}
	else
		printf("Device created successfully");
	

}

void Renderer::CreateSwapchain()
{
	DXGI_SWAP_CHAIN_DESC swapchainDesc = {};
	swapchainDesc.BufferDesc.Width = mWindow->GetSize().X;
	swapchainDesc.BufferDesc.Height = mWindow->GetSize().Y;
	swapchainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapchainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapchainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapchainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDesc.BufferCount = 1;
	swapchainDesc.OutputWindow = mWindow->GetWindowNativeHandler();
	swapchainDesc.Windowed = true;
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapchainDesc.Flags = 0;

	ComPtr<IDXGIDevice> dxgiDevice;
	mDevice.As(&dxgiDevice);

	ComPtr<IDXGIAdapter> dxgiAdapter;
	dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf());

	ComPtr<IDXGIFactory> dxgiFactory;
	dxgiAdapter->GetParent(IID_PPV_ARGS( &dxgiFactory));

	if (FAILED(dxgiFactory->CreateSwapChain(mDevice.Get(), &swapchainDesc, mSwapchain.GetAddressOf())))
	{
		printf("Failed to create swapchain");
		abort();
	}
	else
		printf("Swapchain created successfully");

}

void Renderer::CreateRenderTargetView()
{
	ComPtr<ID3D11Texture2D> colorBuffer;
	mSwapchain->GetBuffer(0, IID_PPV_ARGS(&colorBuffer));

	if (FAILED(mDevice->CreateRenderTargetView(colorBuffer.Get(), nullptr, mRenderTargetView.GetAddressOf())))
	{
		printf("Failed to create render target view");
		abort();
	}
	else
		printf("Render target view created successfully");
	
}

void Renderer::ClearColor(XMFLOAT4 color)
{
	float clearColor[] = { color.x, color.y, color.z, color.w };
	mDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), clearColor);
}

void Renderer::Draw(uint32_t indexCount)
{
	mDeviceContext->Draw(indexCount, 0);
}

void Renderer::Present()
{
	mSwapchain->Present(1, 0);
}

void Renderer::CreateShaders()
{
	ComPtr<ID3DBlob> errorBlob;
	const std::string pixelShaderCode = ReadHLSLFile("PixelShader.hlsl");

	D3DCompile(pixelShaderCode.c_str(), pixelShaderCode.length(), nullptr, nullptr, nullptr, 
		"main", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &mVertexShaderBlob, &errorBlob);

	if (errorBlob.Get() != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		printf("%s", (char*)errorBlob->GetBufferPointer());	
	}
	

	if (FAILED(mDevice->CreatePixelShader(mVertexShaderBlob->GetBufferPointer(),
		mVertexShaderBlob->GetBufferSize(), nullptr, mPixelShader.GetAddressOf())))
	{
		printf("Failed to create pixel shader");
		abort();
	}
	else
		printf("Pixel shader created successfully");



	const std::string vertexShaderCode = ReadHLSLFile("VertexShader.hlsl");
	D3DCompile(vertexShaderCode.c_str(), vertexShaderCode.length(), nullptr, nullptr, nullptr,
		"main", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &mVertexShaderBlob, &errorBlob);

	if (errorBlob.Get() != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		printf("%s", (char*)errorBlob->GetBufferPointer());
	}
	if (FAILED(mDevice->CreateVertexShader(mVertexShaderBlob->GetBufferPointer(),
		mVertexShaderBlob->GetBufferSize(), nullptr, mVertexShader.GetAddressOf())))
	{
		printf("Failed to create vertex shader");
		abort();
	}
	else
		printf("Vertex shader created successfully");
}

void Renderer::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC inputElementDescs[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	mDevice->CreateInputLayout(inputElementDescs, 2, mVertexShaderBlob->GetBufferPointer(),
							mVertexShaderBlob->GetBufferSize(), mInputLayout.GetAddressOf());
}

void Renderer::SetPipeline()
{
	// Создаём описание рендер-стейта для альфа-блендинга
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// Создание объекта рендер-стейта
	HRESULT hr = mDevice->CreateBlendState(&blendDesc, &mBlendState);
	if (FAILED(hr))
	{
		std::cerr << "Error: Failed BlendState " << std::endl;
	}

	// Устанавливаем созданный рендер-стейт
	mDeviceContext->OMSetBlendState(mBlendState.Get(), nullptr, 0xFFFFFFFF);
	mDeviceContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), nullptr);
	mDeviceContext->PSSetShader(mPixelShader.Get(), nullptr, 0);
	mDeviceContext->VSSetShader(mVertexShader.Get(), nullptr, 0);
	mDeviceContext->IASetInputLayout(mInputLayout.Get());
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT viewport = {};
	viewport.Width = (float)mWindow->GetSize().X;
	viewport.Height = (float)mWindow->GetSize().Y;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	mDeviceContext->RSSetViewports(1, &viewport);
}


