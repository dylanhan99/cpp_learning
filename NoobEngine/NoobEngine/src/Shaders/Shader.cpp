#include "nepch.h"
#include "Shader.h"
#include "Utilities/Utils.h"

namespace NoobEngine { namespace Graphics {
	ShaderProgram::ShaderProgram(const char* _vertexPath, const char* _fragmentPath)
	{
		m_ProgramID = glCreateProgram();
		m_VertexID = CreateShader(GL_VERTEX_SHADER, _vertexPath);
		m_FragmentID = CreateShader(GL_FRAGMENT_SHADER, _fragmentPath);

		if (!CompileShader(m_VertexID))
			LOG_ERROR("Failed to compile shader '%s'.", _vertexPath);
		if (!CompileShader(m_FragmentID))
			LOG_ERROR("Failed to compile shader '%s'.", _fragmentPath);

		Link();
	}

	ShaderProgram::~ShaderProgram()
	{
		Unbind();
		glDeleteShader(m_VertexID);
		glDeleteShader(m_FragmentID);
		glDeleteProgram(m_ProgramID);
	}
	
	void ShaderProgram::Bind()
	{
		glUseProgram(m_ProgramID);
	}

	void ShaderProgram::Unbind()
	{
		glUseProgram(0);
	}

	void ShaderProgram::Link()
	{
		glAttachShader(m_ProgramID, m_VertexID);
		glAttachShader(m_ProgramID, m_FragmentID);
		glLinkProgram(m_ProgramID);
		int success; char infoLog[512];
		glGetShaderiv(m_ProgramID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_ProgramID, sizeof(infoLog), NULL, infoLog);
			LOG_ERROR("Failed to link shader program '%d'.", m_ProgramID);
		}
	}

	unsigned int ShaderProgram::CreateShader(unsigned int _shaderType, const char* _shaderPath)
	{
		unsigned int id = glCreateShader(_shaderType);
		std::string str = Utilities::ReadFile(_shaderPath);
		const char* src = str.c_str();
		if (str.empty()) {
			LOG_ERROR("Failed to create '%d' shader using '%s'.", _shaderType, _shaderPath);
			return -1;
		}
		LOG_TRACE("%s\n%s", _shaderPath, src);
		glShaderSource(id, 1, &src, NULL); // create read file stuff
		return id;
	}
	
	bool ShaderProgram::CompileShader(unsigned int _shaderID)
	{
		glCompileShader(_shaderID);
		int success; char infoLog[512];
		glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(_shaderID, sizeof(infoLog), NULL, infoLog);
			//LOG_ERROR("Failed to compile shader '%d'.", _shaderID);
			return false;
		}
		return true;
	}

}}
