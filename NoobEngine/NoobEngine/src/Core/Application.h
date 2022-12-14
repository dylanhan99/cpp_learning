#pragma once
#include "Renderer/BatchRenderer.h"

namespace NoobEngine { namespace Core {

	class Application
	{
	private:

	public:
		Application();
		~Application();

		void Init();
		void Update();
		void Terminate();
	};

}}