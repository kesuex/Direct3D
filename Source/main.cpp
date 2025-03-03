#include <Window/Window.h>
#include <Render/RendererManager.h>
#include <Object/Object.h>
#include <Object/Camera.h>
#include <vector>
#include <iostream>

std::vector<Vertex> vertices =
{
	// передн€€ грань
	{ { -0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f} }, // 0
	{ { -0.5f, 0.5f, -0.5f},  {0.0f, 1.0f, 0.0f, 1.0f} }, // 1
	{ { 0.5f, 0.5f,-0.5f},    {0.0f, 0.0f, 1.0f, 1.0f} }, // 2
	{ { 0.5f, -0.5f, -0.5f},  {1.0f, 1.0f, 0.0f, 1.0f} }, // 3

	// задн€€ грань
	{XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) }, // 4
	{XMFLOAT3(-0.5f, 0.5f, 0.5f),  XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) }, // 5
	{XMFLOAT3(0.5f, 0.5f, 0.5f),   XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) }, // 6
	{XMFLOAT3(0.5f, -0.5f, 0.5f),  XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f) }  // 7
};



std::vector<uint32_t> indices = 
{ 
	// ѕередн€€ грань
	
	0, 1, 3,
	1, 2, 3,

	// «адн€€ грань
	7, 5, 4,
	7, 6, 5,

	// Ћева€ грань
	4, 5, 1,
	4, 1, 0,

	// ѕрава€ грань
	3, 2, 6,
	3, 6, 7,

	// ¬ерхн€€ грань
	1, 5, 6,
	1, 6, 2,

	// Ќижн€€ грань
	0, 3, 7,
	0, 7, 4



};




int main() 
{
	//OBJECTS ARRAY
	std::vector<Object*> objects;

	//WINDOW INITIALIZATION
	Window* window = new Window({1280,720}, "Window");
	window->Initialize();

	//RENDERER INITIALIZATION
	Renderer* renderer = RendererManager::CreateRenderer(window);
	Camera* camera = new Camera({ 0.0f, 0.0f, -3.0f }, {window->GetSize().X, window->GetSize().Y});

	//OBJECT INITIALIZATION
	Object* triangle = new Object(vertices, indices);
	objects.push_back(triangle);

	
	//RENDER LOOP
	while (window->IsVisible())
	{
		window->Run();
		renderer->ClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		camera->HandleInputs(window->GetWindowHandler());
		camera->UpdateMatrix();
		renderer->SetPipeline();
		for (auto& object : objects)
		{
			object->SetProps();
			
			object->UpdateMatrix(camera->GetViewMatrix(), camera->GetProjectionMatrix());
			renderer->Draw(object->GetIndexCount());
			
		}
		
		renderer->Present();
	}

	delete camera;
	delete window;
	delete renderer;

	return 0;
}