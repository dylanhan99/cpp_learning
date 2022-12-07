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
#include <vector>
#include <glad.h>
#include <glm.hpp>
#include "Log.h"

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

	inline const std::vector<BufferElement>& GetElements()	const { return m_Elements; }
	inline		 unsigned int				 GetStride()	const { return m_Stride; }
};

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(unsigned int _size);
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
	IndexBuffer(const unsigned int *_data, unsigned int _count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};

}}