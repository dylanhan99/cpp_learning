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
#include "Texture.h"

namespace NoobEngine { namespace Graphics {

	class BatchRenderer2D
	{
	private:
	public:
		static void Init();
		static void Begin();
		static void End();
		static void Flush();
		static void Terminate();

		static void DrawQuad(glm::vec2 _pos, glm::vec2 _size, float _rotation, glm::vec4 _color, const char* _path);
		static void DrawQuad(glm::vec2 _pos, glm::vec2 _size, glm::vec4 _color);
		static void DrawQuad(glm::vec2 _pos, glm::vec2 _size);
		static void DrawTexture(glm::vec2 _pos, glm::vec2 _size, const char* _path, glm::vec4 _color);
		static void DrawTexture(glm::vec2 _pos, glm::vec2 _size, const char* _path);

		static void DrawLine(glm::vec2 _pos1, glm::vec2 _pos2, glm::vec4 _color);
		static void DrawLine(glm::vec2 _pos1, glm::vec2 _pos2);
		//static void DrawLine(glm::vec2 _pos1, glm::vec2 _pos2, float _width);
	private:
		//static void DrawLine

		static bool IndicesOverflow();
		static bool TexSlotOverflow();
		static bool LineVertexOverflow();
		static void NextBatch();

		static void NormalizePosition(glm::vec2& _item);
		static void NormalizeSize(glm::vec2& _item);
		static void NormalizeColor(glm::vec4& _item);
	};

}}