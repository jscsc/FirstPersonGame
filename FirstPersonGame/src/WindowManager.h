#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#define SCREEN_WIDTH_DEFAULT 800
#define SCREEN_HEIGHT_DEFAULT 600

class WindowManager
{

private:

	GLsizei _width;
	GLsizei _height;
	GLFWwindow* _window;

private:
	//force use of singleton with a private constructor
	WindowManager(GLsizei width, GLsizei height);

public:
	
	/** Get the singleton manager*/
	static WindowManager & getManager();
	/** wrapper for getting the singleton manager that resizes the window if necessary */
	static WindowManager & getSizedManager(GLsizei width, GLsizei height);

	~WindowManager();

	bool windowShouldClose();
	void processInput();
	void display();
	void setSize(GLsizei width, GLsizei height);
};

