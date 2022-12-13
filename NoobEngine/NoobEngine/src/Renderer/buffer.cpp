#include "nepch.h"
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

	/**
	 * Vertex Array
	 */
	
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
		Unbind();
	}

	VertexArray::~VertexArray()
	{
		Unbind();
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
			glEnableVertexAttribArray(i);
			offset += element.count * BufferElement::GetSizeOfType(element.type);
		}
		
		_vbo.Unbind();
		Unbind();
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

	VertexBuffer::VertexBuffer()
		: m_RendererID(0)
	{
		
	}

	VertexBuffer::VertexBuffer(unsigned int _size)
	{
		glGenBuffers(1, &m_RendererID);
		Bind();
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, _size, NULL, GL_DYNAMIC_DRAW);
		Unbind();
	}

	VertexBuffer::VertexBuffer(unsigned int _size, const float* _data)
	{
		glGenBuffers(1, &m_RendererID);
		Bind();
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, _size, _data, GL_STATIC_DRAW);
		Unbind();
	}

	VertexBuffer::~VertexBuffer()
	{
		Unbind();
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

	IndexBuffer::IndexBuffer()
		: m_RendererID(0), m_Count(0)
	{

	}

	IndexBuffer::IndexBuffer(const unsigned int* _data, unsigned int _count)
		: m_Count(_count)
	{
		glGenBuffers(1, &m_RendererID);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(unsigned int), _data, GL_STATIC_DRAW);
		Unbind();
	}

	IndexBuffer::~IndexBuffer()
	{
		Unbind();
		glDeleteBuffers(1, &m_RendererID);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}}