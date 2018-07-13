#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

class WindowManager
{

private:

	GLsizei _width;
	GLsizei _height;
	GLFWwindow* _window;

public:

	WindowManager(GLsizei width, GLsizei height);

	~WindowManager();

	bool windowShouldClose();
	void processInput();
	void display();
};

