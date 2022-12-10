#include "nepch.h"
#include "Utils.h"


namespace NoobEngine { namespace Utilities {

		std::string ReadFile(const char* _filePath)
		{
			std::ifstream file;
			file.open(_filePath, std::ifstream::in);

			if (file.fail()) {
				LOG_ERROR("Failed to open file '%s'.", _filePath);
				return "";
			}

			std::stringstream buffer;
			buffer << file.rdbuf();
			//std::string str(buffer.str());
			//LOG_TRACE(str.c_str());
			file.close();
			return buffer.str();
		}

}}