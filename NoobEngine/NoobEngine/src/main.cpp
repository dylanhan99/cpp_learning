#include "nepch.h"

#include "Core/Window.h"
#include "Renderer/BatchRenderer.h"
#include "Shaders/Shader.h"

#define GLFW_INCLUDE_NONE
using namespace NoobEngine;

int main() {
	//MY_ASSERT_DEBUG(1 == 0);// , "Failed to execute function");
	GLFWwindow* window = Window::CreateWindow(WindowProps());
	MY_ASSERT(window);
	LOG_INFO((const char*)glGetString(GL_VERSION));

	Graphics::BatchRenderer2D renderer;
	Graphics::ShaderProgram shader("../../assets/Shaders/vertex.shader", "../../assets/Shaders/fragment.shader");
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!Window::WindowShouldClose(window)) {
		// Input
		Window::ProcessInput(window);

		// Rendering
		Window::Clear();

		// use shader program to render item
		//glUniform4f(glGetUniformLocation(shaderProgram, "ml_matrix"), vector.x, vector.y, vector.z, vector.w);
		shader.Bind();

		renderer.Begin();
		renderer.Submit(glm::vec4(0.f, 0.f, 0.0f, 1.f));
		renderer.Submit(glm::vec4(1.f, 0.5f, 0.0f, 1.f));
		renderer.End();
		renderer.Flush();

		shader.Unbind();
		Window::SwapBuffers(window);
	}

	return 0;
}
