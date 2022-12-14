#include "nepch.h"
#include "BatchRenderer.h"

namespace NoobEngine { namespace Graphics {

	constexpr std::size_t RENDERER_QUAD_MAX_SPRITES			= 42500;
	constexpr std::size_t RENDERER_QUAD_VERTEX_SIZE_BYTES	= sizeof(QuadVertex);
	constexpr std::size_t RENDERER_QUAD_SPRITE_SIZE_BYTES	= RENDERER_QUAD_VERTEX_SIZE_BYTES * 4;
	constexpr std::size_t RENDERER_QUAD_BUFFER_SIZE_BYTES	= RENDERER_QUAD_SPRITE_SIZE_BYTES * RENDERER_QUAD_MAX_SPRITES;
	constexpr std::size_t RENDERER_QUAD_INDICES_SIZE		= RENDERER_QUAD_MAX_SPRITES * 6;
	constexpr std::size_t RENDERER_QUAD_VERTEX_BUFFER_LEN	= RENDERER_QUAD_MAX_SPRITES * 4;

	constexpr std::size_t RENDERER_LINE_MAX_LINES			= 10000;
	constexpr std::size_t RENDERER_LINE_VERTEX_SIZE_BYTES	= sizeof(LineVertex);
	constexpr std::size_t RENDERER_LINE_LINE_SIZE_BYTES		= RENDERER_LINE_VERTEX_SIZE_BYTES * 2;
	constexpr std::size_t RENDERER_LINE_BUFFER_SIZE_BYTES	= RENDERER_LINE_LINE_SIZE_BYTES * RENDERER_LINE_MAX_LINES;
	constexpr std::size_t RENDERER_LINE_VERTEX_BUFFER_LEN	= RENDERER_LINE_MAX_LINES * 2;

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
		m_QuadBatch = new struct QuadBatch();
		m_QuadBatch->VAO = new VertexArray();
		m_QuadBatch->VBO = new VertexBuffer(RENDERER_QUAD_BUFFER_SIZE_BYTES);

		Graphics::BufferLayout layout;
		layout.Push<glm::vec4>(1);
		layout.Push<glm::vec4>(1);
		m_QuadBatch->VAO->AddBuffer(*m_QuadBatch->VBO, layout);

		m_QuadBatch->BufferBase = new QuadVertex[RENDERER_QUAD_VERTEX_BUFFER_LEN];

		unsigned int* indices = (unsigned int*)malloc(RENDERER_QUAD_INDICES_SIZE * sizeof(unsigned int));
		if (!indices) {
			Terminate();
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

		m_LineBatch = new struct LineBatch();
		m_LineBatch->VAO = new VertexArray();
		m_LineBatch->VBO = new VertexBuffer(RENDERER_LINE_BUFFER_SIZE_BYTES);

		layout = BufferLayout();
		layout.Push<glm::vec4>(1);
		layout.Push<glm::vec4>(1);
		m_LineBatch->VAO->AddBuffer(*m_LineBatch->VBO, layout);

		m_LineBatch->BufferBase = new LineVertex[RENDERER_LINE_VERTEX_BUFFER_LEN];
	}

	void BatchRenderer2D::Begin()
	{
		m_QuadBatch->VBO->Bind();
		m_QuadBatch->Index = 0;
		m_QuadBatch->BufferPointer = m_QuadBatch->BufferBase;

		m_LineBatch->VBO->Bind();
		m_LineBatch->VertexCount = 0;
		m_LineBatch->BufferPointer = m_LineBatch->BufferBase;
	}

	void BatchRenderer2D::End()
	{
		//m_QuadBatch->VBO->Unbind();
		//
		//m_LineBatch->VBO->Unbind();
	}

	void BatchRenderer2D::Flush()
	{
		if (m_QuadBatch->Index) {
			m_QuadBatch->VAO->Bind();
			m_QuadBatch->IBO->Bind();
			uint32_t dataSize = (uint32_t)((uint8_t*)m_QuadBatch->BufferPointer - (uint8_t*)m_QuadBatch->BufferBase);
			m_QuadBatch->VBO->SetData(m_QuadBatch->BufferBase, dataSize);
			glDrawElements(GL_TRIANGLES, m_QuadBatch->Index, GL_UNSIGNED_INT, NULL);
			m_QuadBatch->IBO->Unbind();
			m_QuadBatch->VAO->Unbind();
		}

		if (m_LineBatch->VertexCount) {
			m_LineBatch->VAO->Bind();
			uint32_t dataSize = (uint32_t)((uint8_t*)m_LineBatch->BufferPointer - (uint8_t*)m_LineBatch->BufferBase);
			m_LineBatch->VBO->SetData(m_LineBatch->BufferBase, dataSize);
			glLineWidth(2.f);
			glDrawArrays(GL_LINES, 0, m_LineBatch->VertexCount);
			m_LineBatch->VAO->Unbind();
		}
	}

	void BatchRenderer2D::Terminate()
	{
		if (m_QuadBatch) {
			delete m_QuadBatch->VAO;
			delete m_QuadBatch->VBO;
			delete m_QuadBatch->IBO;
			delete[] m_QuadBatch->BufferBase;
			delete m_QuadBatch;
		}

		if (m_LineBatch) {
			delete m_LineBatch->VAO;
			delete m_LineBatch->VBO;
			delete[] m_LineBatch->BufferBase;
			delete m_LineBatch;
		}
	}

	void BatchRenderer2D::SubmitQuad(QuadVertex& _vertex)
	{
		float size = 1.f;
		auto position = _vertex.Position;
		auto color = _vertex.Color;

		if (m_QuadBatch->Index >= RENDERER_QUAD_INDICES_SIZE) {
			Flush();
			Begin();
		}

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

	void BatchRenderer2D::SubmitLine(LineVertex& _vertex1, LineVertex& _vertex2)
	{
		if (m_LineBatch->VertexCount >= RENDERER_LINE_VERTEX_BUFFER_LEN) {
			Flush();
			Begin();
		}

		m_LineBatch->BufferPointer->Position = _vertex1.Position;
		m_LineBatch->BufferPointer->Color = _vertex1.Color;
		++m_LineBatch->BufferPointer;
		
		m_LineBatch->BufferPointer->Position = _vertex2.Position;
		m_LineBatch->BufferPointer->Color = _vertex2.Color;
		++m_LineBatch->BufferPointer;
		
		m_LineBatch->VertexCount += 2;
	}

}}