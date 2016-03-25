#include "Texture.h"
#include "../Debugging/Logger.h"



Texture::Texture(const std::string& fileName)
	: m_FileName{fileName}, m_Width{0}, m_Height{0}
{
	Load();
}


Texture::~Texture()
{
	glDeleteTextures(1, &m_TextureID);
}

bool Texture::Load()
{
	BYTE* pixels = Utilities::LoadImage(m_FileName.c_str(), &m_Width, &m_Height);
	
	if (!pixels)
	{
		fprintf(stderr, "Unable to load image from file: %s\n", m_FileName.c_str());
		return false;
	}

	for (int i = 0; i < m_Width * m_Height; i++)
	{
		printf("%d ", pixels[i]);
		if ((i + 1) % 3 == 0)
			printf("\n");
	}
	
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID); 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	return true;
}

void Texture::Bind(unsigned int unit) const
{
	S3D_ASSERT(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}