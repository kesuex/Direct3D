#include <Window/Window.h>
#include <Render/RendererManager.h>
#include <Object/Object.h>
#include <Object/Camera.h>
#include <vector>


std::vector<Vertex> vertices =
{
	{XMFLOAT3(-0.5f, -0.5f, 0.0f),XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
	{XMFLOAT3(0.0f, 0.5f, 0.0f),  XMFLOAT4(0.0f, 0.0f, 1.0f, 0.5f) },
	{XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) }
};


std::vector<uint32_t> indices = { 0, 1, 2 };




int main()
{
	//OBJECTS ARRAY
	std::vector<Object*> objects;

	//WINDOW INITIALIZATION
	Window* window = new Window({ 1280,720 }, "Window");
	window->Initialize();

	//RENDERER INITIALIZATION
	Renderer* renderer = RendererManager::CreateRenderer(window);
	//Camera* camera = new Camera({ 0.0f, 0.0f, -3.0f }, window->GetSize().X, window->GetSize().Y});
	Camera* camera = new Camera({ 0.0f, 0.0f, -3.0f }, { window->GetSize().X, window->GetSize().Y });

	//OBJECT INITIALIZATION
	Object* cube = new Object(vertices, indices);
	objects.push_back(cube);

	


	//RENDER LOOP
	while (window->IsVisible())
	{
		window->Run();
		renderer->ClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		camera->HandleInputs(window->GetWindowHandler());
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