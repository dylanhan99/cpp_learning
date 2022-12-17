#include "nepch.h"
#include "Application.h"

#include "Window.h"
#include "Events/Input.h"


namespace NoobEngine { namespace Core {

using namespace Graphics;

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

			BatchRenderer2D::DrawTexture({ 0.f, 0.f }, { 1.f, 0.5 }, "../../assets/idk.jpg");
			BatchRenderer2D::DrawTexture({ 1.f, 0.f }, { 1.f, 0.5 }, "../../assets/idk.jpg", {1, 0.3, 0.5, 1});
			BatchRenderer2D::DrawQuad({ 0.2f, 0.2f }, { 0.1f, 0.3f }, { 0, 0.3, 0.5, 1 });
			//BatchRenderer2D::DrawQuad({ 0.f, 0.f }, { 1.f, 0.5 });

			//QuadVertex v;
			//v.Position	= glm::vec4(0.f, 0.f, 0.0f, 1.f);
			//v.Color		= glm::vec4(1.f, 1.f, 1.f, 1.0f);
			//BatchRenderer2D::SubmitQuad(v);
			//
			//QuadVertex v2;
			//v2.Position = glm::vec4(1.f, 0.5f, 0.0f, 1.f);
			//v2.Color	= glm::vec4(1.f, 0.5f, 0.0f, 1.f);
			//BatchRenderer2D::SubmitQuad(v2);
			//
			//LineVertex l = { glm::vec4(-0.5f, -0.5f, 0.0f, 1.f), glm::vec4(0.5f, 0.4f, 0.2f, 1.0f) };
			//LineVertex l2 = { glm::vec4(0.f, 0.f, 0.0f, 1.f), glm::vec4(0.6f, 0.3f, 1.f, 1.0f) };
			//BatchRenderer2D::SubmitLine(l, l2);

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