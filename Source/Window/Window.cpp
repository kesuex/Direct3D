#include "Window.h"



Window::Window(WindowSize size, const std::string& title): mSize(size), mTitle(title)
{

}

Window::~Window()
{
	glfwTerminate();
}

void Window::Initialize()
{
	if (!glfwInit())
	{
		printf("Failed to initialize GLWF!");
		abort();
	}
	else {
		printf(" GLWF initialized sucsessfully!");
	}

	mWindow = glfwCreateWindow(mSize.X, mSize.Y, mTitle.c_str(), nullptr, nullptr);


	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	if (mWindow == nullptr)
	{
		printf("Failed to initialize GLWF!");
		abort();
	}
	else {
		printf(" GLWF initialized sucsessfully!");
	}
}

void Window::Run()
{
	glfwPollEvents();
}
