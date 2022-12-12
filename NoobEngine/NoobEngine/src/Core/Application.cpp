#include "nepch.h"
#include "Application.h"

#include "Window.h"
#include "Events/Input.h"

namespace NoobEngine { namespace Core {


	Application::Application()
		: m_Renderer(nullptr), m_Shaders(nullptr)
	{

	}

	Application::~Application()
	{

	}

	void Application::Init()
	{
		MY_ASSERT(Window::CreateWindow(WindowProps()));
		m_Renderer = new Graphics::BatchRenderer2D();
		m_Shaders = new Graphics::ShaderProgram("../../assets/Shaders/vertex.shader", "../../assets/Shaders/fragment.shader");
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		LOG_INFO("Application initialized.");
	}

	void Application::Update()
	{
		while (!Window::WindowShouldClose()) {
			// Input
			if (Events::Input::OnKeyPress(GLFW_KEY_ESCAPE))
				Window::WindowShouldClose(true);

			// Rendering
			Window::Clear();

			// use shader program to render item
			//glUniform4f(glGetUniformLocation(shaderProgram, "ml_matrix"), vector.x, vector.y, vector.z, vector.w);
			m_Shaders->Bind();

			m_Renderer->Begin();
			m_Renderer->Submit(glm::vec4(0.f, 0.f, 0.0f, 1.f));
			m_Renderer->Submit(glm::vec4(1.f, 0.5f, 0.0f, 1.f));
			m_Renderer->End();
			m_Renderer->Flush();

			m_Shaders->Unbind();
			Window::SwapBuffers();
		}
	}

	void Application::Terminate()
	{
		delete m_Shaders;
		delete m_Renderer;
		Window::TerminateWindow();
		LOG_INFO("Application terminated safely.");
	}


}}