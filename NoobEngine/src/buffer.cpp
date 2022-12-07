#include "Buffer.h"

namespace NoobEngine { namespace Graphics {

	/**
	 * Buffer Layout
	 */

	BufferLayout::BufferLayout()
		: m_Stride(0)
	{

	}

	BufferLayout::~BufferLayout()
	{

	}

	template<>
	void BufferLayout::Push<float>(unsigned int _count)
	{
		m_Elements.push_back({ GL_FLOAT, _count, GL_FALSE });
		m_Stride += _count * BufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void BufferLayout::Push<unsigned int>(unsigned int _count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, _count, GL_FALSE });
		m_Stride += _count * BufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void BufferLayout::Push<glm::vec4>(unsigned int _count)
	{
		m_Elements.push_back({ GL_FLOAT, (unsigned int)glm::vec4::length(), GL_TRUE });
		m_Stride += _count * sizeof(glm::vec4);
	}

	/**
	 * Vertex Array
	 */
	
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::AddBuffer(const VertexBuffer& _vbo, const BufferLayout& _layout)
	{
		Bind();
		_vbo.Bind();

		const auto& elements = _layout.GetElements();
		for (unsigned int i = 0, offset = 0; i < elements.size(); ++i) {
			const auto& element = elements[i];
			glVertexAttribPointer(i, element.count, element.type, element.normalized, 
				_layout.GetStride(), (const GLvoid*)offset);
			offset += element.count * BufferElement::GetSizeOfType(element.type);
		}
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	/**
	 * Vertex Buffer
	 */

	VertexBuffer::VertexBuffer(unsigned int _size)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, _size, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	/**
	 * Index Buffer
	 */

	IndexBuffer::IndexBuffer(const unsigned int* _data, unsigned int _count)
		: m_Count(_count)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(unsigned int), _data, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}}