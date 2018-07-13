#include "WindowManager.h"
#include <iostream>


// Shared variables
namespace
{
	bool glfwInitialized = false;
	bool gladInitialized = false;

	int numOfWindows = 0;
}

WindowManager::WindowManager(GLsizei width, GLsizei height) : _width(width), _height(height)
{
	++numOfWindows;

	if (!glfwInitialized)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwInitialized = true;
	}

	_window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
	if (_window == nullptr)
	{
		std::cerr << "failed to create window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(_window);

	if (!gladInitialized)
	{
		//check GLAD is working
		if (!gladLoadGLLoader((GLADloadproc)&glfwGetProcAddress))
		{
			std::cout << "failed to initialze glad" << std::endl;
			exit(-1);
		}
		gladInitialized = true;
	}

	glViewport(0, 0, _width, _height);

	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow * window, int width, int height) -> void
	{
		glViewport(0, 0, width, height);
	});
}


WindowManager::~WindowManager()
{
	--numOfWindows;
	if (numOfWindows == 0)
	{
		glfwTerminate();
	}
}

bool WindowManager::windowShouldClose() { return glfwWindowShouldClose(_window); }

void WindowManager::processInput()
{
	glfwPollEvents();
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{ //GLFW_RELEASE is the state where no key is pressed 
		glfwSetWindowShouldClose(_window, true);
	}
}

void WindowManager::display()
{
	glfwSwapBuffers(_window);
}
