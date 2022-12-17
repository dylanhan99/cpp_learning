#pragma once
#include "nepch.h"

namespace NoobEngine { namespace Graphics {

	class Texture2D
	{
	private:
		const char* m_Path;
		bool m_IsLoaded;
	public:
		unsigned int m_TextureID, m_Width, m_Height;
		Texture2D(const char* _texturePath);
		~Texture2D();
		void Bind(uint32_t _slot);
		inline bool IsLoaded() { return m_IsLoaded; }
	};

	class TextureCache
	{
	private:
	public:
		static std::unordered_map<const char*, Texture2D*> m_Textures;
		static Texture2D* Add(const char* _path);
		static Texture2D* GetTexture2D(const char* _path);
		static void Terminate();
	};

}}