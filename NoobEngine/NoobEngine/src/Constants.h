#pragma once
#include "nepch.h"

namespace NoobEngine { 

	struct QuadVertex
	{
		glm::vec4 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
	};

	struct LineVertex
	{
		glm::vec4 Position;
		glm::vec4 Color;
	};

}
