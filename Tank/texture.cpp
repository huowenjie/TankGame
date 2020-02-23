#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <img/stb_image.h>

#include "app-debug.h"
#include "texture.h"

namespace hwj 
{
	TexLoader::TexLoader()
	{
	}
	
	TexLoader::~TexLoader() 
	{
	}

	int TexLoader::GenDefTextures(const char *path) 
	{
		if (!path || !path[0]) {
			LOG_INFO("NULL path!\n");
			return 0;
		}

		unsigned int texture = 0;

		// ֱͨ alpha ͨ������
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND); //�����ģʽ��ͼ
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// ָ�����ģʽ�㷨

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		// ���ز���������
		int nrChannels = 0;
		int width = 0;
		int height = 0;

		// ��תy��
		stbi_set_flip_vertically_on_load(true);
		unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		} else {
			LOG_INFO("Failed to load texture");
		}
		stbi_image_free(data);

		return texture;
	}

	void TexLoader::DelTextures(unsigned int textures)
	{
		glDeleteTextures(1, &textures);
	}
}
