#include "nepch.h"
#include "BatchRenderer.h"

namespace NoobEngine { namespace Graphics {

	constexpr std::size_t RENDERER_QUAD_MAX_SPRITES		= 42500;
	constexpr std::size_t RENDERER_QUAD_VERTEX_SIZE		= sizeof(QuadVertex);
	constexpr std::size_t RENDERER_QUAD_SPRITE_SIZE		= RENDERER_QUAD_VERTEX_SIZE * 4;
	constexpr std::size_t RENDERER_QUAD_BUFFER_SIZE		= RENDERER_QUAD_SPRITE_SIZE * RENDERER_QUAD_MAX_SPRITES;
	constexpr std::size_t RENDERER_QUAD_INDICES_SIZE	= RENDERER_QUAD_MAX_SPRITES * 6;

	constexpr std::size_t RENDERER_LINE_MAX_LINES		= 10000;
	constexpr std::size_t RENDERER_LINE_VERTEX_SIZE		= sizeof(LineVertex);
	constexpr std::size_t RENDERER_LINE_LINE_SIZE		= RENDERER_LINE_VERTEX_SIZE * 2;
	constexpr std::size_t RENDERER_LINE_BUFFER_SIZE		= RENDERER_LINE_LINE_SIZE * RENDERER_LINE_MAX_LINES;

	struct QuadBatch
	{
		VertexArray		*VAO = nullptr;
		VertexBuffer	*VBO = nullptr;
		IndexBuffer		*IBO = nullptr;
		GLsizei			Index = 0;
		QuadVertex		*BufferBase = nullptr;
		QuadVertex		*BufferPointer = nullptr;
	};

	struct LineBatch
	{
		VertexArray		*VAO = nullptr;
		VertexBuffer	*VBO = nullptr;
		GLsizei			VertexCount = 0;
		LineVertex		*BufferBase = nullptr;
		LineVertex		*BufferPointer = nullptr;
	};

	static struct QuadBatch *m_QuadBatch = nullptr;
	static struct LineBatch *m_LineBatch = nullptr;

	void BatchRenderer2D::Init()
	{
		QuadInit();
		LineInit();
	}

	void BatchRenderer2D::Begin()
	{
		QuadBegin();
		LineBegin();
	}

	void BatchRenderer2D::End()
	{
		QuadEnd();
		LineEnd();
	}

	void BatchRenderer2D::Flush()
	{
		QuadFlush();
		LineFlush();
	}

	void BatchRenderer2D::Terminate()
	{
		QuadTerminate();
		LineTerminate();
	}

	void BatchRenderer2D::QuadInit()
	{
		m_QuadBatch = new struct QuadBatch();
		m_QuadBatch->VAO = new VertexArray();
		m_QuadBatch->VBO = new VertexBuffer(RENDERER_QUAD_BUFFER_SIZE);

		Graphics::BufferLayout layout;
		layout.Push<glm::vec4>(1);
		layout.Push<glm::vec4>(1);
		m_QuadBatch->VAO->AddBuffer(*m_QuadBatch->VBO, layout);

		m_QuadBatch->BufferBase = new QuadVertex[RENDERER_QUAD_SPRITE_SIZE];

		unsigned int* indices = (unsigned int*)malloc(RENDERER_QUAD_INDICES_SIZE * sizeof(unsigned int));
		if (!indices) {
			QuadTerminate();
			MY_ASSERT_MSG(indices, "Failed to initialize indices in BatchRenderer2D.");
		}
		unsigned int offset = 0;
		for (size_t i = 0; i < RENDERER_QUAD_INDICES_SIZE; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

		m_QuadBatch->IBO = new IndexBuffer(indices, RENDERER_QUAD_INDICES_SIZE);
		free(indices);
	}

	void BatchRenderer2D::QuadBegin()
	{
		m_QuadBatch->VBO->Bind();
		m_QuadBatch->Index = 0;
		m_QuadBatch->BufferPointer = m_QuadBatch->BufferBase;
		//m_QuadBatch->Buffer = (QuadVertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::QuadEnd()
	{
		//glUnmapBuffer(GL_ARRAY_BUFFER);
		m_QuadBatch->VBO->Unbind();
	}

	void BatchRenderer2D::QuadFlush()
	{
		m_QuadBatch->VAO->Bind();
		m_QuadBatch->IBO->Bind();
		uint32_t dataSize = (uint32_t)((uint8_t*)m_QuadBatch->BufferPointer - (uint8_t*)m_QuadBatch->BufferBase);
		m_QuadBatch->VBO->SetData(m_QuadBatch->BufferBase, dataSize);
		glDrawElements(GL_TRIANGLES, m_QuadBatch->Index, GL_UNSIGNED_INT, NULL);
		m_QuadBatch->IBO->Unbind();
		m_QuadBatch->VAO->Unbind();
	}

	void BatchRenderer2D::QuadTerminate()
	{
		delete m_QuadBatch->VAO;
		delete m_QuadBatch->VBO;
		delete m_QuadBatch->IBO;
		delete[] m_QuadBatch->BufferBase;
		delete m_QuadBatch;
	}	

	void BatchRenderer2D::SubmitQuad(QuadVertex& _vertex)
	{
		float size = 1.f;
		auto position = _vertex.Position;
		auto color = _vertex.Color;

		m_QuadBatch->BufferPointer->Position = position;
		m_QuadBatch->BufferPointer->Color = color;
		++m_QuadBatch->BufferPointer;

		m_QuadBatch->BufferPointer->Position = glm::vec4(position.x,		 position.y - size, position.z, 1);
		m_QuadBatch->BufferPointer->Color = color;
		++m_QuadBatch->BufferPointer;

		m_QuadBatch->BufferPointer->Position = glm::vec4(position.x - size, position.y - size, position.z, 1);
		m_QuadBatch->BufferPointer->Color = color;
		++m_QuadBatch->BufferPointer;

		m_QuadBatch->BufferPointer->Position = glm::vec4(position.x - size, position.y,		position.z, 1);
		m_QuadBatch->BufferPointer->Color = color;
		++m_QuadBatch->BufferPointer;

		m_QuadBatch->Index += 6;
	}


	void BatchRenderer2D::LineInit()
	{
		//m_LineBatch = new struct LineBatch();
		//m_LineBatch->VAO = new VertexArray();
		//m_LineBatch->VBO = new VertexBuffer(RENDERER_LINE_BUFFER_SIZE);
		//
		//Graphics::BufferLayout layout;
		//layout.Push<glm::vec4>(1);
		//layout.Push<glm::vec4>(1);
		//m_LineBatch->VAO->AddBuffer(*m_LineBatch->VBO, layout);
	}
	
	void BatchRenderer2D::LineBegin()
	{
		//m_LineBatch->VBO->Bind();
		//m_LineBatch->Buffer = (LineVertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::LineEnd()
	{
		//glUnmapBuffer(GL_ARRAY_BUFFER);
		//m_LineBatch->VBO->Unbind();
	}

	void BatchRenderer2D::LineFlush()
	{
		//m_LineBatch->VAO->Bind();
		//glDrawArrays(GL_LINE, 0, m_LineBatch->VertexCount);
		//m_LineBatch->VAO->Unbind();
	}

	void BatchRenderer2D::LineTerminate()
	{
		//delete m_LineBatch->VAO;
		//delete m_LineBatch->VBO;
		//delete m_LineBatch;
	}

	void BatchRenderer2D::SubmitLine(LineVertex& _vertex1, LineVertex& _vertex2)
	{
		//m_LineBatch->Buffer->Position = _vertex1.Position;
		//m_LineBatch->Buffer->Color = _vertex1.Color;
		//++m_LineBatch->Buffer;
		//
		//m_LineBatch->Buffer->Position = _vertex2.Position;
		//m_LineBatch->Buffer->Color = _vertex2.Color;
		//++m_LineBatch->Buffer;
		//
		//m_LineBatch->VertexCount += 2;
	}

}}