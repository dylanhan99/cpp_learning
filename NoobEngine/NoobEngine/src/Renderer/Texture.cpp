#include "nepch.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace NoobEngine { namespace Graphics {

	std::unordered_map<const char*, Texture2D*> TextureCache::m_Textures = {};

	Texture2D::Texture2D(const char* _texturePath)
		: m_TextureID(0), m_Width(0), m_Height(0), m_Path(), m_IsLoaded(false)
	{
		int width, height, channels;
		stbi_uc* data = nullptr;
		data = stbi_load(_texturePath, &width, &height, &channels, 0);

		if (data) {
			m_IsLoaded = true;
			m_Width = width;
			m_Height = height;

			GLenum internalFormat = 0, dataFormat = 0;
			if (channels == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else if (channels == 3)
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}

			glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
			glTextureStorage2D(m_TextureID, 1, internalFormat, m_Width, m_Height);

			glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
		}

		stbi_image_free(data);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void Texture2D::Bind(uint32_t _slot)
	{
		glActiveTexture(GL_TEXTURE0 + _slot);
		glBindTextureUnit(_slot, m_TextureID);
	}

	Texture2D* TextureCache::Add(const char* _path)
	{
		Texture2D* tex = new Texture2D(_path);
		if (tex->IsLoaded())
			m_Textures.insert({ _path, tex });
		return tex;
	}

	Texture2D* TextureCache::GetTexture2D(const char* _path)
	{
		Texture2D* tex = nullptr;
		if (m_Textures.find(_path) == m_Textures.end())
			tex = Add(_path);
		return tex;
	}

	void TextureCache::Terminate()
	{
		LOG_INFO("TextureCache cleared.");
		for (auto& it : m_Textures)
			delete it.second;
		m_Textures.clear();
	}

}}