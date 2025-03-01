#include <Window/Window.h>




int main() 
{
	
	Window* basicWindow = new Window({1280,720}, "Basic Window");
	basicWindow->Initizlize();

	while (basicWindow->IsVisible())
	{
		basicWindow->Run();
	}

	delete basicWindow;

	return 0;
}