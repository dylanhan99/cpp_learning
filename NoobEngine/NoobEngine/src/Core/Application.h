#pragma once
#include "Renderer/BatchRenderer.h"
#include "Shaders/Shader.h"

namespace NoobEngine { namespace Core {

	class Application
	{
	private:
		Graphics::BatchRenderer2D* m_Renderer;
		Graphics::ShaderProgram* m_Shaders;
	public:
		Application();
		~Application();

		void Init();
		void Update();
		void Terminate();
	};

}}