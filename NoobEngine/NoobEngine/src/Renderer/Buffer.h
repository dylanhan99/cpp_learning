/**
 * @file	Buffer.h
 * @author	Han Wei, Dylan (dylanhan99@gmail.com)
 * @version 1.0
 * @date	07/12/2022
 * @brief	This file contains structures and logic pertaining to 
 *			setting up VAO, VBO and IBO.
 *			As a dynamic draw, the BufferLayout object holds all
 *			the vertices of the current batch.
 *
 */

#pragma once
#include <glfw3.h>

namespace NoobEngine { namespace Graphics {

struct BufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int _type)
	{
		switch (_type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		MY_ASSERT(false);
		return 0;
	}
};

class BufferLayout
{
private:
	std::vector<BufferElement> m_Elements;
	unsigned int m_Stride;
public:
	BufferLayout();
	~BufferLayout();

	template<typename T>
	void Push(unsigned int _count) 
	{
		MY_ASSERT(false);
	}

	template<>
	void Push<float>(unsigned int _count)
	{
		m_Elements.push_back({ GL_FLOAT, _count, GL_FALSE });
		m_Stride += _count * BufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int _count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, _count, GL_FALSE });
		m_Stride += _count * BufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<glm::vec4>(unsigned int _count)
	{
		m_Elements.push_back({ GL_FLOAT, (unsigned int)glm::vec4::length(), GL_TRUE });
		m_Stride += _count * sizeof(glm::vec4);
	}

	inline const std::vector<BufferElement>& GetElements()	const { return m_Elements; }
	inline		 unsigned int				 GetStride()	const { return m_Stride; }
};

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer();
	VertexBuffer(unsigned int _size);
	VertexBuffer(unsigned int _size, const float* _data);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

class VertexArray 
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& _vbo, const BufferLayout& _layout);
	void Bind() const;
	void Unbind() const;
};

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int *_data, unsigned int _count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};

}}