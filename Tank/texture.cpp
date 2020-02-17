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

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		// 为当前绑定的纹理对象设置环绕、过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		// 加载并生成纹理
		int nrChannels = 0;
		int width = 0;
		int height = 0;
		unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
		
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		} else {
			LOG_INFO("Failed to load texture");
		}
		stbi_image_free(data);

		return texture;
	}
}
