#pragma once
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <map>
#include <math.h>
#include <gl/GL.h>

#include "../glfw/include/GLFW/glfw3.h"

namespace Kostek
{
	class Overlay
	{
	private:
		GLFWwindow* window = NULL;
		HWND targetWindow = NULL;
		int width = NULL, height = NULL, x = NULL, y = NULL;
		LPCWSTR targetWindowName;

		bool Recenter();

	public:
		Overlay();

		bool Create(LPCWSTR windowName);

		bool Run();

		void Handle();


		//Drawing Functions
		void DrawRect(int x, int y, int width, int height,
			float r, float g, float b);
		void DrawEmptyRect(int x, int y, int width, int height,
			float r, float g, float b);
		void DrawCircle(int x, int y, float radius,
			float r, float g, float b);
		void DrawEmptyCircle(int x, int y, float radius,
			float r, float g, float b);
	};
}
