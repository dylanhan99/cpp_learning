#pragma once

namespace NoobEngine { namespace Graphics {

	class ShaderProgram
	{
	private:
		unsigned int m_ProgramID;

		unsigned int m_VertexID;
		unsigned int m_FragmentID;
	public:
		ShaderProgram(const char* _vertexPath, const char* _fragmentPath);
		~ShaderProgram();

		void Bind();
		void Unbind();
		inline const unsigned int GetID() const { return m_ProgramID; }
	private:
		void Link();
		static unsigned int CreateShader(unsigned int _shaderType, const char* _shaderPath);
		static bool CompileShader(unsigned int _shaderID);
	};

}}