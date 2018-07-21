#include "Texture.h"
#include "../Utilities/Utilities.h"
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
	unsigned int bitDepth;
	// pixel data format.
	GLenum format;
	
	BYTE* pixels = Utilities::LoadImage(m_FileName.c_str(), &m_Width, &m_Height, &bitDepth);
	
	if (!pixels)
	{
		S3D_LOG("WARNING", "Unable to load image from file" + m_FileName);
		return false;
	}

	printf("Bitdepth: %d\n", bitDepth);

	switch (bitDepth)
	{
		case 16:
			format = GL_BGR;
			break;
		case 24:
			format = GL_BGR;
			break;
		default:
			format = GL_RGB;
	}

	/* for (size_t i = 0; i < m_Width * m_Height; i++)
	{
		printf("%d ", pixels[i]);
		if ((i + 1) % 3 == 0)
			printf("\n");
	} */

#if defined(OPENGLCONTEXT)
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID); 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, pixels);
#endif // OPENGLCONTEXT

	return true;
}

void Texture::Bind(unsigned int unit) const
{
	S3D_ASSERT(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}