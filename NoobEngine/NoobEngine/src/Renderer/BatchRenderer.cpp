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
		VertexArray*	VAO = nullptr;
		VertexBuffer*	VBO = nullptr;
		IndexBuffer*	IBO = nullptr;
		GLsizei			Index = 0;
		QuadVertex*		Buffer = nullptr;
	};

	struct LineBatch
	{
		VertexArray		VAO;
		VertexBuffer	VBO;
		LineVertex*		Buffer = nullptr;
	};

	static struct QuadBatch* m_QuadBatch = nullptr;
	static struct LineBatch* m_LineBatch = nullptr;

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
		m_QuadBatch->Buffer = (QuadVertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::QuadEnd()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		m_QuadBatch->VBO->Unbind();
	}

	void BatchRenderer2D::QuadFlush()
	{
		m_QuadBatch->VAO->Bind();
		m_QuadBatch->IBO->Bind();
		glDrawElements(GL_TRIANGLES, m_QuadBatch->Index, GL_UNSIGNED_INT, NULL);
		m_QuadBatch->IBO->Unbind();
		m_QuadBatch->VAO->Unbind();
		m_QuadBatch->Index = 0;
	}

	void BatchRenderer2D::QuadTerminate()
	{
		delete m_QuadBatch->VAO;
		delete m_QuadBatch->VBO;
		delete m_QuadBatch->IBO;
		delete m_QuadBatch;
	}	

	void BatchRenderer2D::SubmitQuad(QuadVertex& _vertex)
	{
		float size = 1.f;
		auto position = _vertex.Position;
		auto color = _vertex.Color;

		m_QuadBatch->Buffer->Position = position;
		m_QuadBatch->Buffer->Color = color;
		++(m_QuadBatch->Buffer);

		m_QuadBatch->Buffer->Position = glm::vec4(position.x,		 position.y - size, position.z, 1);
		m_QuadBatch->Buffer->Color = color;
		++(m_QuadBatch->Buffer);

		m_QuadBatch->Buffer->Position = glm::vec4(position.x - size, position.y - size, position.z, 1);
		m_QuadBatch->Buffer->Color = color;
		++(m_QuadBatch->Buffer);

		m_QuadBatch->Buffer->Position = glm::vec4(position.x - size, position.y,		position.z, 1);
		m_QuadBatch->Buffer->Color = color;
		++(m_QuadBatch->Buffer);

		m_QuadBatch->Index += 6;
	}


	void BatchRenderer2D::LineInit()
	{

	}
	
	void BatchRenderer2D::LineBegin()
	{

	}

	void BatchRenderer2D::LineEnd()
	{

	}

	void BatchRenderer2D::LineFlush()
	{

	}

	void BatchRenderer2D::LineTerminate()
	{
		//delete[] m_LineBatch->Buffer;
		//delete m_LineBatch;
	}

	//void BatchRenderer2D::Submit(Vertex& _vertex)
	//{
	//	static unsigned int m_BufferCount = 0;
	//	float size = 1.f;
	//	auto position = _vertex.Position;
	//	auto color = _vertex.Color;
	//	
	//	m_Buffer->Position = position;
	//	m_Buffer->Color = color;
	//	++m_Buffer;
	//
	//	m_Buffer->Position = glm::vec4(position.x, position.y - size, position.z, 1);
	//	m_Buffer->Color = color;
	//	++m_Buffer;
	//	
	//	m_Buffer->Position = glm::vec4(position.x - size, position.y - size, position.z, 1);
	//	m_Buffer->Color = color;
	//	++m_Buffer;
	//	
	//	m_Buffer->Position = glm::vec4(position.x - size, position.y, position.z, 1);
	//	m_Buffer->Color = color;
	//	++m_Buffer;
	//
	//	if (m_BufferCount % 4 == 0)
	//		m_IndexCount += 6;
	//}

}}