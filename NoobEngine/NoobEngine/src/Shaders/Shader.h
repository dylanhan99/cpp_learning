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
	private:
		void Link();
		static unsigned int CreateShader(unsigned int _shaderType, const char* _shaderPath);
		static void CompileShader(unsigned int _shaderID);
	};

}}