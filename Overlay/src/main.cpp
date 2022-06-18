#pragma once
#include "glfw/include/GLFW/glfw3.h"
#include "Overlay/Overlay.h"

int main()
{
	LPCWSTR windowName = L"Untitled - Notepad";
	Kostek::Overlay* overlay = new Kostek::Overlay();

	if (overlay->Create(windowName))
	{
		while (overlay->Run())
		{
			overlay->DrawEmptyRect(100, 100, 25, 25, 1, 0, 0);
			overlay->DrawRect(500, 500, 25, 25, 1, 1, 0);
			overlay->DrawCircle(200, 100, 50.f, 0, 1, 0);
			overlay->DrawEmptyCircle(300, 300, 60.f, 0, 0, 1);

			overlay->Handle();
		}
	}
	return 0;
}
