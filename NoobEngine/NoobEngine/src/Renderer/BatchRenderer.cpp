#include "nepch.h"
#include "BatchRenderer.h"
#include "Shaders/Shader.h"
#include "Core/Window.h"


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
		ShaderProgram	*Shaders = nullptr;

		glm::vec4 DefaultColor = { 255, 255, 255, 255 };
		float DefaultTexSlot = -1.f;
		glm::vec2 DefaultTexCoord[4] = { { 0.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f } };
	};

	struct LineBatch
	{
		VertexArray		*VAO = nullptr;
		VertexBuffer	*VBO = nullptr;
		GLsizei			VertexCount = 0;
		LineVertex		*BufferBase = nullptr;
		LineVertex		*BufferPointer = nullptr;
		ShaderProgram	*Shaders = nullptr;
	};

	std::vector<Texture2D*> m_TextureSlots = {};
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
		layout.Push<float>(1);
		layout.Push<glm::vec2>(1);
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

		m_QuadBatch->Shaders = new Graphics::ShaderProgram("../../assets/Shaders/QuadVertex.shader", "../../assets/Shaders/QuadFragment.shader");


		m_LineBatch = new struct LineBatch();
		m_LineBatch->VAO = new VertexArray();
		m_LineBatch->VBO = new VertexBuffer(RENDERER_LINE_BUFFER_SIZE_BYTES);

		layout = BufferLayout();
		layout.Push<glm::vec4>(1);
		layout.Push<glm::vec4>(1);
		m_LineBatch->VAO->AddBuffer(*m_LineBatch->VBO, layout);

		m_LineBatch->BufferBase = new LineVertex[RENDERER_LINE_VERTEX_BUFFER_LEN];
		m_LineBatch->Shaders = new Graphics::ShaderProgram("../../assets/Shaders/LineVertex.shader", "../../assets/Shaders/LineFragment.shader");
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
		for (int slot = 0; slot < m_TextureSlots.size(); ++slot)
			m_TextureSlots[slot]->Bind(slot);
		
		auto loc = glGetUniformLocation(m_QuadBatch->Shaders->GetID(), "uTextures");
		int samplers[32] = { 0 };
		for (int i = 0; i < 32; i++)
			samplers[i] = i;
		glUniform1iv(loc, 32, samplers);

		if (m_QuadBatch->Index) {
			m_QuadBatch->Shaders->Bind();
			m_QuadBatch->VAO->Bind();
			m_QuadBatch->IBO->Bind();
			uint32_t dataSize = (uint32_t)((uint8_t*)m_QuadBatch->BufferPointer - (uint8_t*)m_QuadBatch->BufferBase);
			m_QuadBatch->VBO->SetData(m_QuadBatch->BufferBase, dataSize);
			glDrawElements(GL_TRIANGLES, m_QuadBatch->Index, GL_UNSIGNED_INT, NULL);
			m_QuadBatch->IBO->Unbind();
			m_QuadBatch->VAO->Unbind();
			m_QuadBatch->Shaders->Unbind();
		}

		if (m_LineBatch->VertexCount) {
			m_LineBatch->Shaders->Bind();
			m_LineBatch->VAO->Bind();
			uint32_t dataSize = (uint32_t)((uint8_t*)m_LineBatch->BufferPointer - (uint8_t*)m_LineBatch->BufferBase);
			m_LineBatch->VBO->SetData(m_LineBatch->BufferBase, dataSize);
			glLineWidth(2.f);
			glDrawArrays(GL_LINES, 0, m_LineBatch->VertexCount);
			m_LineBatch->VAO->Unbind();
			m_LineBatch->Shaders->Unbind();
		}

		m_TextureSlots.clear();
	}

	void BatchRenderer2D::Terminate()
	{
		m_TextureSlots.clear();
		TextureCache::Terminate();
		if (m_QuadBatch) {
			delete m_QuadBatch->VAO;
			delete m_QuadBatch->VBO;
			delete m_QuadBatch->IBO;
			delete[] m_QuadBatch->BufferBase;
			delete m_QuadBatch->Shaders;
			delete m_QuadBatch;
		}

		if (m_LineBatch) {
			delete m_LineBatch->VAO;
			delete m_LineBatch->VBO;
			delete[] m_LineBatch->BufferBase;
			delete m_LineBatch->Shaders;
			delete m_LineBatch;
		}
	}

	void BatchRenderer2D::DrawQuad(glm::vec2 _pos, glm::vec2 _size, float _rotation, glm::vec4 _color, const char* _path)
	{
		auto texture = TextureCache::GetTexture2D(_path);
		float texSlot = m_QuadBatch->DefaultTexSlot;
		NormalizePosition(_pos);
		NormalizeSize(_size);
		NormalizeColor(_color);
		if (texture) {
			m_TextureSlots.push_back(texture);
			texSlot = m_TextureSlots.size() - 1;
		}

		if (IndicesOverflow() || TexSlotOverflow())
			NextBatch();

		m_QuadBatch->BufferPointer->Position = glm::vec4(_pos.x, _pos.y, 0.f, 1.f);
		m_QuadBatch->BufferPointer->Color = _color;
		m_QuadBatch->BufferPointer->TexSlot = texSlot;
		m_QuadBatch->BufferPointer->TexCoord = m_QuadBatch->DefaultTexCoord[0];
		++m_QuadBatch->BufferPointer;

		m_QuadBatch->BufferPointer->Position = glm::vec4(_pos.x, _pos.y - _size.y, 0.f, 1.f);
		m_QuadBatch->BufferPointer->Color = _color;
		m_QuadBatch->BufferPointer->TexSlot = texSlot;
		m_QuadBatch->BufferPointer->TexCoord = m_QuadBatch->DefaultTexCoord[1];
		++m_QuadBatch->BufferPointer;

		m_QuadBatch->BufferPointer->Position = glm::vec4(_pos.x + _size.x, _pos.y - _size.y, 0.f, 1.f);
		m_QuadBatch->BufferPointer->Color = _color;
		m_QuadBatch->BufferPointer->TexSlot = texSlot;
		m_QuadBatch->BufferPointer->TexCoord = m_QuadBatch->DefaultTexCoord[2];
		++m_QuadBatch->BufferPointer;

		m_QuadBatch->BufferPointer->Position = glm::vec4(_pos.x + _size.x, _pos.y, 0.f, 1.f);
		m_QuadBatch->BufferPointer->Color = _color;
		m_QuadBatch->BufferPointer->TexSlot = texSlot;
		m_QuadBatch->BufferPointer->TexCoord = m_QuadBatch->DefaultTexCoord[3];
		++m_QuadBatch->BufferPointer;

		m_QuadBatch->Index += 6;
	}

	void BatchRenderer2D::DrawQuad(glm::vec2 _pos, glm::vec2 _size)
	{
		DrawQuad(_pos, _size, m_QuadBatch->DefaultColor);
	}

	void BatchRenderer2D::DrawQuad(glm::vec2 _pos, glm::vec2 _size, glm::vec4 _color)
	{
		DrawQuad(_pos, _size, 0.f, _color, "");
	}

	void BatchRenderer2D::DrawTexture(glm::vec2 _pos, glm::vec2 _size, const char* _path, glm::vec4 _color)
	{
		DrawQuad(_pos, _size, 0.f, _color, _path);
	}

	void BatchRenderer2D::DrawTexture(glm::vec2 _pos, glm::vec2 _size, const char* _path)
	{
		DrawTexture(_pos, _size, _path, m_QuadBatch->DefaultColor);
	}

	void BatchRenderer2D::DrawLine(glm::vec2 _pos1, glm::vec2 _pos2, glm::vec4 _color)
	{
		NormalizePosition(_pos1);
		NormalizePosition(_pos2);
		NormalizeColor(_color);

		if (LineVertexOverflow())
			NextBatch();

		m_LineBatch->BufferPointer->Position = glm::vec4(_pos1.x, _pos1.y, 0.f, 1.f);
		m_LineBatch->BufferPointer->Color = _color;
		++m_LineBatch->BufferPointer;
		
		m_LineBatch->BufferPointer->Position = glm::vec4(_pos2.x, _pos2.y, 0.f, 1.f);
		m_LineBatch->BufferPointer->Color = _color;
		++m_LineBatch->BufferPointer;
		
		m_LineBatch->VertexCount += 2;
	}

	void BatchRenderer2D::DrawLine(glm::vec2 _pos1, glm::vec2 _pos2)
	{
		DrawLine(_pos1, _pos2, m_QuadBatch->DefaultColor);
	}
		
	bool BatchRenderer2D::IndicesOverflow()
	{
		if (m_QuadBatch->Index >= RENDERER_QUAD_INDICES_SIZE)
			return true;
		return false;
	}

	bool BatchRenderer2D::TexSlotOverflow()
	{
		if (m_TextureSlots.size() >= 32)
			return true;
		return false;
	}

	bool BatchRenderer2D::LineVertexOverflow()
	{
		if (m_LineBatch->VertexCount >= RENDERER_LINE_VERTEX_BUFFER_LEN)
			return true;
		return false;
	}

	void BatchRenderer2D::NextBatch()
	{
		Flush();
		Begin();
	}

	void BatchRenderer2D::NormalizePosition(glm::vec2& _item)
	{
		float amt = (_item.x / Window::GetWidth()) * 2.f;
		_item.x = -1.f + amt;
		amt = (_item.y / Window::GetHeight()) * 2.f;
		_item.y = 1.f - amt;
	}

	void BatchRenderer2D::NormalizeSize(glm::vec2& _item)
	{
		_item.x /= Window::GetWidth();
		_item.x *= 2.f;
		_item.y /= Window::GetHeight();
		_item.y *= 2.f;
	}

	void BatchRenderer2D::NormalizeColor(glm::vec4& _item)
	{
		_item.x /= 255;
		_item.y /= 255;
		_item.z /= 255;
		_item.w /= 255;
	}


}}