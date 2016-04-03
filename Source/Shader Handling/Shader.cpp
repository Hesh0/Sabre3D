  #include "Shader.h"
#include "../Sabre3D/Sabre3Dstd.h"
#include "../Utilities/Utilities.h"



// User passes in an array with the different shader types they're using, in the right order, might change to use bit flags.
Shader::Shader(const std::string& fileName, unsigned int numShaders, GLenum shaderTypes[])
	: m_FileName{fileName}, m_NumShaders{numShaders}
{
	m_ShaderTypes = DBG_NEW GLenum[numShaders];
	
	for (size_t i = 0; i < numShaders; i++)
		m_ShaderTypes[i] = shaderTypes[i];
	
	m_Shaders = DBG_NEW GLuint[numShaders];
	m_ProgramID = glCreateProgram();
}

Shader::~Shader()
{
	glDeleteProgram(m_ProgramID);
	delete[] m_ShaderTypes;
	delete[] m_Shaders;
}

GLuint Shader::CompileShader(GLenum shaderType)
{
	std::string extension;

	switch (shaderType)
	{
		case GL_VERTEX_SHADER:
			extension = ".vs";
			break;
		case GL_FRAGMENT_SHADER:
			extension = ".fs";
			break;
		case GL_TESS_CONTROL_SHADER:
			extension = ".tcs";
			break;
		case GL_TESS_EVALUATION_SHADER:
			extension = "tes";
			break;
		case GL_GEOMETRY_SHADER:
			extension = ".gs";
			break;
		case GL_COMPUTE_SHADER:
			extension = ".glcs";
			break;
		default:
			fprintf(stderr, "Not a recognized shader type");
			return 1;
	}
	m_ShaderID = glCreateShader(shaderType);
	std::string shaderStr = LoadShader(m_FileName + extension);
	const char* shaderSource = shaderStr.c_str();
	glShaderSource(m_ShaderID, 1, &shaderSource, nullptr);
	glCompileShader(m_ShaderID);

	return m_ShaderID;
}

void Shader::CreateProgram()
{
	size_t i;
	
	for (i = 0; i < m_NumShaders; i++)
	{
		m_Shaders[i] = CompileShader(m_ShaderTypes[i]);
		if (!CheckShaderError(m_Shaders[i], shaderFileNames[i]));
			glAttachShader(m_ProgramID, m_Shaders[i]);
	}
	glBindAttribLocation(m_ProgramID, 0, "position");
	glBindAttribLocation(m_ProgramID, 1, "texCoord");
	glLinkProgram(m_ProgramID);
	if (CheckProgramError(m_ProgramID))
		glDeleteProgram(m_ProgramID);

	for (i = 0; i < m_NumShaders; i++)
	{
		glDeleteShader(m_Shaders[i]);
	}
}

void Shader::Bind() const
{
	glUseProgram(m_ProgramID);
}

std::string Shader::LoadShader(const std::string& fileName) 
{
	std::ifstream shaderFile{fileName};
	shaderFileNames.push_back(fileName);

	if (shaderFile)
	{
		// copies contents of fileName into string in 1 go.
		std::string contents((std::istreambuf_iterator<char>(shaderFile)), (std::istreambuf_iterator<char>()));
		return contents;
	}
	S3D_LOG("WARNING", "Could not load shader " + fileName);
	
	return "";
}

// over-arching error checking function with function pointer args to remove redundant code.
bool Shader::CheckError(bool isShader, const std::string& file, GLuint objectID, PFNGLGETSHADERIVPROC objectPropGetter, PFNGLGETSHADERINFOLOGPROC infoLogFunc, GLenum statusType) const
{
	GLint status;
	// check if shader compiled or program linked successfully.
	objectPropGetter(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		// get the size of the log message.
		GLint infoLogLength;
		objectPropGetter(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<GLchar> infoLog(infoLogLength);
		infoLogFunc(objectID, infoLogLength, &infoLogLength, &infoLog[0]);
		Utilities::StripNewline(&infoLog[0]);
		std::string s(&infoLog[0]);
		if (isShader)
			S3D_LOG("WARNING", s + "in " + file);
		else
			S3D_LOG("WARNING", s + " Program " + m_FileName);
		
		return true;
	}
	
	return false;
}

bool Shader::CheckShaderError(GLuint shaderID, const std::string file) const
{
	return CheckError(true, file, shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool Shader::CheckProgramError(GLuint programID) const
{
	return CheckError(false, "", programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}