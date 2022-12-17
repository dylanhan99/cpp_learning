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
		static std::vector<Texture2D*> m_TextureSlots;
	public:
		static void Init();
		static void Begin();
		static void End();
		static void Flush();
		static void Terminate();

		static void DrawQuad(glm::vec2 _pos, glm::vec2 _size);
		static void DrawQuad(glm::vec2 _pos, glm::vec2 _size, glm::vec4 _color);
		static void DrawTexture(glm::vec2 _pos, glm::vec2 _size, const char* _path);
		static void DrawTexture(glm::vec2 _pos, glm::vec2 _size, const char* _path, glm::vec4 _color);
		//static void DrawTexture(float _x, float _y, float _w, float _h, const char* _path);

		static void DrawLine(LineVertex& _vertex1, LineVertex& _vertex2);
	private:
		static void DrawQuad(glm::vec2 _pos, glm::vec2 _size, float _rotation, glm::vec4 _color, const char* _path);
		//static void DrawLine

		static bool IndicesOverflow();
		static bool TexSlotOverflow();
		static void NextBatch();
	};

}}