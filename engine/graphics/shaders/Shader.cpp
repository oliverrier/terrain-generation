#include "Shader.h"
#include <GL/glew.h>

#include <fstream>
#include <iostream>
#include <sstream>

unsigned Shader::loadShaders(ShaderInfo* shaderInfo)
{
	if (shaderInfo == nullptr)
		throw std::runtime_error("ShaderInfo is null");

	auto program = glCreateProgram();
	auto* entry = shaderInfo;

	while (entry->type != GL_NONE)
	{
		auto shaderId = glCreateShader(entry->type);
		entry->shaderId = shaderId;
		auto str = readShader(entry->filename);
		const auto source = str.c_str();

		if (source == nullptr)
		{
			for (entry = shaderInfo; entry->type != GL_NONE; ++entry)
			{
				glDeleteShader(entry->shaderId);
				entry->shaderId = 0;
			}

			return 0;
		}

		glShaderSource(shaderId, 1, &source, nullptr);
		glCompileShader(shaderId);

		GLint hasCompiled;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &hasCompiled);

		if (!hasCompiled)
		{
			GLsizei length;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
			GLchar* log = new GLchar[length + 1];
			glGetShaderInfoLog(shaderId, length, &length, log);

			std::cerr << "Shader compilation failed: " << log << std::endl;
			delete[] log;
			log = nullptr;

			return 0;
		}

		glAttachShader(program, shaderId);
		++entry;
	}

	glLinkProgram(program);
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLsizei length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		GLchar* log = new GLchar[length + 1];
		glGetProgramInfoLog(program, length, &length, log);
		std::cerr << "Shader linking failed: " << log << std::endl;
		delete[] log;
		log = nullptr;

		for (entry = shaderInfo; entry->type != GL_NONE; ++entry)
		{
			glDeleteShader(entry->shaderId);
			entry->shaderId = 0;
		}

		return 0;
	}

	return program;
}

std::string Shader::readShader(const char* filename)
{
	std::ifstream inputFile(filename);
	if (!inputFile.is_open())
		throw std::runtime_error("Filename can’t be opened");

	std::stringstream buffer;
	buffer << inputFile.rdbuf();

	inputFile.close();
	return buffer.str();
}
