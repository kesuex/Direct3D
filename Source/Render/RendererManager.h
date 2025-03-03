#pragma once
#include <Render/Renderer.h>
#include <exception>

class RendererManager
{
public:
	RendererManager();
	~RendererManager() = default;

	static Renderer* CreateRenderer(Window* pWindow)
	{
		if (mRenderer != nullptr)
		{
			throw std::exception("Renderer is already created");
		}
		mRenderer = new Renderer(pWindow);
		return mRenderer;
	}

	static Renderer* GetRenderer()
	{
		if (mRenderer == nullptr)
		{
			
			throw std::exception("Renderer is not created");
		
		}
		return mRenderer;
	}
private:
	static inline Renderer* mRenderer = nullptr;


};