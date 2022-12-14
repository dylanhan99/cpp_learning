/**
 * @file	BatchRenderer.h
 * @author	Han Wei, Dylan (dylanhan99@gmail.com)
 * @version 1.0
 * @date	07/12/2022
 * @brief	
 *
 */

#pragma once
#include "Buffer.h"
#include "Constants.h"

namespace NoobEngine { namespace Graphics {

	class BatchRenderer2D
	{
	public:
		static void Init();
		static void Begin();
		static void End();
		static void Flush();
		static void Terminate();

		static void SubmitQuad(QuadVertex& _vertex);

		static void SubmitLine(LineVertex& _vertex1, LineVertex& _vertex2);
	};

}}