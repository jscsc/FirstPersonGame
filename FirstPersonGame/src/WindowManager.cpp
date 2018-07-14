#include "WindowManager.h"
#include <iostream>

WindowManager & WindowManager::getManager()
{
	static WindowManager singleton{SCREEN_WIDTH_DEFAULT, SCREEN_HEIGHT_DEFAULT};
	return singleton;
}

WindowManager & WindowManager::getSizedManager(GLsizei width, GLsizei height)
{
	WindowManager& manager = getManager();
	manager.setSize(width, height);
	return manager;
}

WindowManager::WindowManager(GLsizei width, GLsizei height) : _width(width), _height(height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	_window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
	if (_window == nullptr)
	{
		std::cerr << "failed to create window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(_window);

	//check GLAD is working
	if (!gladLoadGLLoader((GLADloadproc)&glfwGetProcAddress))
	{
		std::cout << "failed to initialze glad" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, _width, _height);

	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow * window, int width, int height) -> void
	{
		glViewport(0, 0, width, height);
	});
}


WindowManager::~WindowManager()
{
	glfwTerminate();
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

void WindowManager::setSize(GLsizei width, GLsizei height)
{
	//only resize the window if we're not currently at the specified size
	if (width != _width || height != _height)
	{
		if (_window)
		{
			_width = width;
			_height = height;
			glfwSetWindowSize(_window, _width, _height);
		}
	}
}
