#define GLFW_INCLUDE_NONE

#include <iostream>
#include <glad.h>
#include <glfw3.h>

#include "Core/Window.h"
#include "Log/Log.h"
#include "Renderer/BatchRenderer.h"

using namespace NoobEngine;

int main() {
	//MY_ASSERT_DEBUG(1 == 0);// , "Failed to execute function");
	GLFWwindow* window = Window::CreateWindow(WindowProps());
	MY_ASSERT(window);
	LOG_INFO((const char*)glGetString(GL_VERSION));

	Graphics::BatchRenderer2D renderer = Graphics::BatchRenderer2D();

	
	// Vertices data
	float vertices[] = {
	 0.5f,  0.5f, 0.0f, 1.0f,  // top right
	 0.5f, -0.5f, 0.0f, 1.0f,  // bottom right
	-0.5f, -0.5f, 0.0f, 1.0f,  // bottom left
	-0.5f,  0.5f, 0.0f, 1.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	
	const char* vertexShaderSource = "#version 330 core\n"
		"layout(location = 0) in vec4    position;\n"
		"uniform mat4 pr_matrix;"
		"uniform mat4 vw_matrix = mat4(1.0);"
		"uniform mat4 ml_matrix = mat4(1.0);"
		"void main()\n"
		"{\n"
		//"gl_Position = pr_matrix * vw_matrix * ml_matrix * position;\n"
		"gl_Position = position;\n"
		"}\0";
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int success; char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "Failed to compile VERTEX SHADER!\n";
	}

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "Failed to compile FRAGMENT SHADER!\n";
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
		std::cout << "Failed to link SHADER PROGRAM!\n";
	}

	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!Window::WindowShouldClose(window)) {
		// Input
		Window::ProcessInput(window);

		// Rendering
		Window::Clear();

		// use shader program to render item
		glUseProgram(shaderProgram);
		//glUniform4f(glGetUniformLocation(shaderProgram, "ml_matrix"), vector.x, vector.y, vector.z, vector.w);


		renderer.Begin();
		renderer.Submit(glm::vec4(0.f, 0.f, 0.0f, 1.f));
		renderer.Submit(glm::vec4(1.f, 0.5f, 0.0f, 1.f));
		renderer.End();
		renderer.Flush();

		Window::SwapBuffers(window);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return 0;
}
