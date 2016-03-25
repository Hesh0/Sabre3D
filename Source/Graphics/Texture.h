#pragma once

#include "../Utilities/Utilities.h"
#include <GL/glew.h>
#include <string>



class Texture
{
	const std::string& m_FileName;
	unsigned int m_Width;
	unsigned int m_Height;
	GLuint m_TextureID;

public:
	Texture(const std::string& fileName);
	~Texture();
	void Bind(unsigned int unit) const;

private: 
	Texture(const Texture& other);
	void operator=(const Texture& other){}
	bool Load();
};

