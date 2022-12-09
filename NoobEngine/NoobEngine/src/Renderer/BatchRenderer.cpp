#include "nepch.h"
#include "Renderer/BatchRenderer.h"

namespace NoobEngine { namespace Graphics {

	BatchRenderer2D::BatchRenderer2D()
		: m_VAO(), m_VBO(RENDERER_BUFFER_SIZE),
		m_IndexCount(0), m_Buffer(nullptr)
	{
		Graphics::BufferLayout layout;
		layout.Push<glm::vec4>(1);
		m_VAO.AddBuffer(m_VBO, layout); 
		
		unsigned int indices[RENDERER_INDICES_SIZE];
		unsigned int offset = 0;
		for (size_t i = 0; i < RENDERER_INDICES_SIZE; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

		m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		free(m_IBO);
	}

	void BatchRenderer2D::Begin()
	{
		m_VBO.Bind();
		m_Buffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::Submit(glm::vec4 _pos)
	{
		float size = 1.f;
		
		m_Buffer->Position = _pos;
		++m_Buffer;

		m_Buffer->Position = glm::vec4(_pos.x,		  _pos.y - size, _pos.z, 1);
		++m_Buffer;

		m_Buffer->Position = glm::vec4(_pos.x - size, _pos.y - size, _pos.z, 1);
		++m_Buffer;

		m_Buffer->Position = glm::vec4(_pos.x - size, _pos.y,		 _pos.z, 1);
		++m_Buffer;

		m_IndexCount += 6;
	}

	void BatchRenderer2D::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		m_VBO.Unbind();
	}

	void BatchRenderer2D::Flush()
	{
		m_VAO.Bind();
		m_IBO->Bind();
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);
		m_IBO->Unbind();
		m_VAO.Unbind();
		m_IndexCount = 0;
	}

}}