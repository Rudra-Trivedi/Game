#include "GLSLProgram.h"
#include <assert.h>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>

GLSLProgram::GLSLProgram() :_numAttributes(0), _programId(0), _vertexID(0), _fragId(0)
{

}

GLSLProgram::~GLSLProgram()
{
}

// compile both the shaders 
void GLSLProgram::CompileShaders(const char* vertexPath, const char* fragPath)
{
	// get vertex id 
	_vertexID = glCreateShader(GL_VERTEX_SHADER);
	assert(_vertexID);

	// get frag id 
	_fragId = glCreateShader(GL_FRAGMENT_SHADER);
	assert(_fragId);

	CompileShader(vertexPath, _vertexID);
	CompileShader(fragPath, _fragId);

}

void GLSLProgram::AddAttributes(const std::string& attributeName)
{
	glBindAttribLocation(_programId, _numAttributes++, attributeName.c_str());
}

void GLSLProgram::LinkShaders()
{
	// get a program object after compiling vertex and frag shaders 
	_programId = glCreateProgram();
	assert(_programId);

	// attach both the shaders to the program 
	glAttachShader(_programId, _vertexID);
	glAttachShader(_programId, _fragId);

	// Link our program 
	glLinkProgram(_programId);

	// error handling for linking 
	GLint success = 0; 
	glGetProgramiv(_programId, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(_programId, maxLength, &maxLength, &errorLog[0]);

		glDeleteProgram(_programId);

		glDeleteShader(_vertexID);
		glDeleteShader(_fragId);

		printf("%s \n", &errorLog[0]);

		return; 
	}

	// detaching shaders after successful link 
	glDetachShader(_programId, _vertexID);
	glDetachShader(_programId, _fragId);
	glDeleteShader(_vertexID);
	glDeleteShader(_fragId);
}

void GLSLProgram::UseProgram()
{
	glUseProgram(_programId);
	for (int i = 0 ; i < _numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::UnUseProgram()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::CompileShader(const std::string& filePath, const GLuint& shaderId)
{
	// read the vertex shader 
	std::ifstream shaderFile(filePath);
	assert(!(shaderFile.fail()));

	std::string fileContents = "";
	std::string line;

	while (std::getline(shaderFile, line))
	{
		fileContents += line + "\n";
	}

	shaderFile.close();
	const char* fileString = fileContents.c_str();
	glShaderSource(shaderId, 1, &fileString, nullptr);

	// compile shader 
	glCompileShader(shaderId);

	// compile error handling 
	GLint success = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

	// error handling 
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(shaderId);

		printf("%s \n", &errorLog[0]);

		return;
	}
}
