#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <vector>
#include "Shader.h"
#include "Mesh.h"
#include "WindowManager.h"
#include "UtilityFunctions.h"

namespace HelloTriangle
{
	const GLsizei width = 800;
	const GLsizei height = 600;

	const char* vertextShader =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;"
		"void main()"
		"{"
		"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);"
		"}\0";

	const char* fragmentShader =
		"#version 330 core\n"
		"out vec4 FragColor;"
		"void main()"
		"{"
		"    //always render an orange color\n"
		"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
		"}\0";

	int main()
	{
		WindowManager& windowManager = WindowManager::getSizedManager(width, height);
		Shader shader(vertextShader, fragmentShader);

		std::vector<float> vertices = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		Mesh mesh(vertices);
		shader.bind();

		while (!windowManager.windowShouldClose())
		{
			// Poll input
			windowManager.processInput();

			// CLEAR SCREEN (render commands)
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// SET SHADER FOR DRAWING
			shader.bind();

			// DRAW TRIANGLE with configuration saved in vao
			mesh.draw();

			// Swap and draw
			windowManager.display();

		}

		return 0;
	}

}

int main()
{
	HelloTriangle::main();
}