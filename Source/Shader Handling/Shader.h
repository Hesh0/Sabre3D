#pragma once

#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <string>

class Shader 
{
	const std::string& m_FileName;
	unsigned int m_NumShaders;
	GLuint m_ProgramID;
	GLuint m_ShaderID;
	GLenum* m_ShaderTypes;
	GLuint* m_Shaders;

public: 
	Shader(const std::string& fileName, unsigned int numShaders, GLenum shaderTypes[]);
	~Shader();
	void CreateProgram();
	void Bind() const;
	
private:
	Shader(const Shader& other);
	void operator=(const Shader& other){}
	std::string LoadShader(std::string& fileName) const;
	bool CheckError(GLuint shaderID, PFNGLGETSHADERIVPROC objectPropGetter, PFNGLGETSHADERINFOLOGPROC infoLogFunc, GLenum status) const;
	bool CheckShaderError(GLuint shaderID) const;
	bool CheckProgramError(GLuint programID) const;
	GLuint CompileShader(GLenum shaderType);
};