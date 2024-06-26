#include "nepch.h"
#include "Application.h"

#include "Window.h"
#include "Events/Input.h"


namespace NoobEngine { namespace Core {

using namespace Graphics;
using namespace Events;

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Init()
	{
		MY_ASSERT(Window::CreateWindow(WindowProps()));
		//m_Renderer = new Graphics::BatchRenderer2D();
		BatchRenderer2D::Init();
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

			BatchRenderer2D::Begin();
			BatchRenderer2D::DrawTexture({ 0, 0 }, { Window::GetWidth(), 100 }, "../../assets/idk.jpg");
			BatchRenderer2D::DrawTexture({ 200, 200 }, { 150, 100 }, "../../assets/idk.jpg", {255, 122, 123, 125});
			BatchRenderer2D::DrawQuad({ Input::GetCursorX(), Input::GetCursorY() }, { 20, 20 }, { 15, 30, 45, 255 });
			BatchRenderer2D::DrawQuad({ 450, 700 }, { 320, 50 });

			BatchRenderer2D::DrawLine({ Window::GetWidth()*0.5f, 0 }, { Window::GetWidth() * 0.5f, Window::GetHeight() });
			BatchRenderer2D::DrawLine({ 0, Window::GetHeight() * 0.5f }, { Window::GetWidth(),Window::GetHeight() * 0.5f }, { 0.6f, 0.3f, 1.f, 1.0f });

			BatchRenderer2D::End();
			BatchRenderer2D::Flush();

			Window::SwapBuffers();
		}
	}

	void Application::Terminate()
	{
		BatchRenderer2D::Terminate();
		Window::TerminateWindow();
		LOG_INFO("Application terminated safely.");
	}


}}