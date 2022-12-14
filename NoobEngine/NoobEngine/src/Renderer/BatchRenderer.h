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
		//BatchRenderer2D();
		//~BatchRenderer2D();

		static void Init();
		static void Begin();
		static void End();
		static void Flush();
		static void Terminate();
		//void Submit(Vertex& _vertex); depractaed

		static void QuadInit();
		static void QuadBegin();
		static void QuadEnd();
		static void QuadFlush();
		static void QuadTerminate();
		static void SubmitQuad(QuadVertex& _vertex);

		static void LineInit();
		static void LineBegin();
		static void LineSubmit() {};
		static void LineEnd();
		static void LineFlush();
		static void LineTerminate();
		static void SubmitLine(LineVertex& _vertex1, LineVertex& _vertex2);
	};

}}