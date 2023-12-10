#pragma once
#include <GL/glew.h>
#include <string>
class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void CompileShaders(const char* vertexPath, const char* fragPath);
	void AddAttributes(const std::string& attributeName);
	void LinkShaders();

	// use program 
	void UseProgram();

	//unuse program
	void UnUseProgram();
private:

	void CompileShader(const std::string& filePath, const GLuint& shaderID);

	int _numAttributes;
	GLuint _programId;
	GLuint _vertexID;
	GLuint _fragId;

};

