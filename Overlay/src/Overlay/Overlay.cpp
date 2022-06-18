#include "Overlay.h"

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %s\n", description);
}

Kostek::Overlay::Overlay()
{
}

bool Kostek::Overlay::Create(LPCWSTR windowName)
{
	this->targetWindowName = windowName;
	this->targetWindow = FindWindow(NULL, windowName);
	if (!this->targetWindow) { return false; }

	/*
	RECT rect;
	if (!GetWindowRect(this->targetWindow, &rect)) { return false; }

	this->width = rect.right - rect.left;
	this->height = rect.bottom - rect.top;
	this->x = rect.left;
	this->y = rect.top;
	*/
	if (!this->Recenter()) { return false; }

	if (!glfwInit()) { return false; };

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
	glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);

	this->window = glfwCreateWindow(this->width,
		this->height,
		"Kostek Overlay",
		NULL,
		NULL);

	glfwSetWindowPos(this->window, this->x, this->y);

	if (!window) { return false; };

	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	glfwDefaultWindowHints();

	glfwShowWindow(this->window);

	return true;
}

bool Kostek::Overlay::Run()
{
	if (glfwWindowShouldClose(this->window)) { return false; };

	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, this->width, this->height, 0, 0, 1);
	glViewport(0, 0, this->width, this->height);

	if (!this->Recenter()) { return false; }

	return true;
}

bool Kostek::Overlay::Recenter()
{
	HWND newWindow = FindWindow(NULL, this->targetWindowName);
	if (!newWindow) { return false; }
	RECT rect;
	GetWindowRect(newWindow, &rect);
	if (this->x != rect.left ||
		this->y != rect.top ||
		this->width != rect.right - rect.left ||
		this->height != rect.bottom - rect.top)
	{
		this->x = rect.left;
		this->y = rect.top;
		this->width = rect.right - rect.left;
		this->height = rect.bottom - rect.top;

		glfwSetWindowPos(this->window, this->x, this->y);
		glfwSetWindowSize(this->window, this->width, this->height);
	}

	return true;
}

void Kostek::Overlay::Handle()
{
	glfwSwapBuffers(this->window);
	glfwPollEvents();
}

void Kostek::Overlay::DrawRect(int x, int y, int width, int height, float r, float g, float b)
{
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex2f(x, y + height);
	glColor3f(r, g, b);
	glVertex2f(x + width, y + height);
	glColor3f(r, g, b);
	glVertex2f(x + width, y);
	glColor3f(r, g, b);
	glVertex2f(x, y);
	glEnd();
}

void Kostek::Overlay::DrawEmptyRect(int x, int y, int width, int height, float r, float g, float b)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex2f(x, y + height);
	glColor3f(r, g, b);
	glVertex2f(x + width, y + height);
	glColor3f(r, g, b);
	glVertex2f(x + width, y);
	glColor3f(r, g, b);
	glVertex2f(x, y);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Kostek::Overlay::DrawCircle(int x, int y, float radius, float r, float g, float b)
{
	float twicePi = 2.0 * 3.1415926f;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(r, g, b);
	glVertex2f(x, y);
	for (uint16_t i = 0; i < 100; i++)
	{
		glColor3f(r, g, b);
		glVertex2f((x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20))));
	}
	glEnd();
}

void Kostek::Overlay::DrawEmptyCircle(int x, int y, float radius, float r, float g, float b)
{
	glBegin(GL_LINE_LOOP);
	for (uint16_t i = 0; i < 100; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(100);
		float x2 = radius * cosf(theta);
		float y2 = radius * sinf(theta);
		glColor3f(r, g, b);
		glVertex2f(x2 + x, y2 + y);
	}
	glEnd();
}

