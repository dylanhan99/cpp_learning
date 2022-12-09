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

namespace NoobEngine { namespace Graphics {

	struct Vertex 
	{
		glm::vec4 Position;
	};

	constexpr std::size_t RENDERER_MAX_SPRITES = 42500;
	constexpr std::size_t RENDERER_VERTEX_SIZE = sizeof(Vertex);
	constexpr std::size_t RENDERER_SPRITE_SIZE = RENDERER_VERTEX_SIZE * 4;
	constexpr std::size_t RENDERER_BUFFER_SIZE = RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES;
	constexpr std::size_t RENDERER_INDICES_SIZE = RENDERER_MAX_SPRITES * 6;

	class BatchRenderer2D
	{
	private:
		VertexArray		m_VAO;
		VertexBuffer	m_VBO;
		IndexBuffer *m_IBO;
		GLsizei			m_IndexCount;
		Vertex			*m_Buffer;
	public:
		BatchRenderer2D();
		~BatchRenderer2D();

		void Begin();
		void Submit(glm::vec4 _pos);
		void End();
		void Flush();
	};

}}