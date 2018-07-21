#pragma once

#include <GL/glew.h>
#include <fstream>

#include "../Sabre3D/Sabre3Dstd.h"



class Shader 
{
	const int CREATION_ERROR = -1;
	
	const std::string m_FileName;
	unsigned int m_NumShaders;
	GLuint m_ProgramID;
	GLuint m_ShaderID;
	GLenum* m_ShaderTypes;
	GLuint* m_Shaders;
	std::vector<std::string> shaderFileNames;

public: 
	Shader(const std::string fileName, GLenum shaderTypes[], unsigned int numShaders);
	~Shader();
	void CreateProgram();
	void Bind() const;
	
private:
	Shader(const Shader& other);
	void operator=(const Shader& other){}
	bool Init(unsigned int numShaders, GLenum shaderTypes[]);
	std::string LoadShader(const std::string& fileName);
	bool Shader::CheckError(bool isShader, const std::string& file, GLuint objectID, PFNGLGETSHADERIVPROC objectPropGetter, PFNGLGETSHADERINFOLOGPROC infoLogFunc, GLenum statusType) const;
	bool CheckShaderError(GLuint shaderID, const std::string associatedFileName) const;
	bool CheckProgramError(GLuint programID) const;
	GLuint CompileShader(GLenum shaderType);
};