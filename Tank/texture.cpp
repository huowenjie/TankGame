#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <img/stb_image.h>
#include <cstring>

#include "app-debug.h"
#include "texture.h"

namespace hwj 
{
	int GenDefTextures(const char *path) 
	{
		if (!path || !path[0]) {
			LOG_INFO("NULL path!\n");
			return 0;
		}

		unsigned int texture = 0;

		// 直通 alpha 通道处理
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND); //开混合模式贴图
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// 指定混合模式算法

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

		// 翻转y轴
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

	TexInfo GenTexInfo(const char *path) 
	{
		TexInfo info;

		if (!path || !path[0]) {
			LOG_INFO("NULL path!\n");
			return info;
		}

		unsigned int texture = 0;

		// 直通 alpha 通道处理
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND); //开混合模式贴图
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// 指定混合模式算法

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

		// 翻转y轴
		stbi_set_flip_vertically_on_load(true);
		unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

		info.mTex = texture;
		info.mWidth = static_cast<float>(width);
		info.mHeight = static_cast<float>(height);

		GLint format = nrChannels <= 3 ? GL_RGB : GL_RGBA;

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,
				0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		} else {
			LOG_INFO("Failed to load texture");
		}
		stbi_image_free(data);

		return info;
	}

	AnimTexInfo GenAnimTextures(const char *path, int num)
	{
		AnimTexInfo info;

		if (!path || !path[0]) {
			LOG_INFO("NULL path!\n");
			return info;
		}

		unsigned int texture = 0;

		// 直通 alpha 通道处理
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND); //开混合模式贴图
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// 指定混合模式算法

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

		// 翻转y轴
		stbi_set_flip_vertically_on_load(true);
		unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			info.mHeight = static_cast<float>(height);
			info.mWidth	 = static_cast<float>(width);
			info.mNum	 = (width > height) ? (width / height) : (height / width);
			info.mTex	 = texture;
		} else {
			LOG_INFO("Failed to load texture");
		}
		stbi_image_free(data);

		return info;
	}

	void DelTextures(unsigned int textures)
	{
		glDeleteTextures(1, &textures);
	}
}
