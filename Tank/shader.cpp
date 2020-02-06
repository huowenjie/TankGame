#include <cstdio>
#include <cstring>

#include <glad/glad.h>

#include "shader.h"
#include "app-debug.h"

namespace hwj 
{
	ShaderProgram::ShaderProgram() : 
		vertId(0), fragId(0), progId(0)
	{
	
	}

	ShaderProgram::~ShaderProgram()
	{
	
	}

	bool ShaderProgram::LoadShaderFile(const char *vert, const char *frag)
	{
		vertId = glCreateShader(GL_VERTEX_SHADER);
		if (!vertId) {
			LOG_INTO("Create vertex shader error!\n");
			return false;
		}

		fragId = glCreateShader(GL_FRAGMENT_SHADER);
		if (!fragId) {
			LOG_INTO("Create fragment shader error!\n");
			return false;
		}

		progId = glCreateProgram();
		if (!progId) {
			LOG_INTO("Create program error!\n");
			return false;
		}

		bool ret = false;

		if (!LoadFile(vertId, vert)) {
			LOG_INTO("Load vert shader error!\n");
			goto err;
		}

		if (!LoadFile(fragId, frag)) {
			LOG_INTO("Load frag shader error!\n");
			goto err;
		}

		if (!AttachShader(vertId)) {
			LOG_INTO("Attach vert shader error!\n");
			goto err;
		}

		if (!AttachShader(fragId)) {
			LOG_INTO("Attach frag shader error!\n");
			goto err;
		}

		ret = LinkProgram();
	err:
		if (!ret) {
			DeleteShader();
		}

		return ret;
	}
	
	void ShaderProgram::UseProgram()
	{
		if (glIsProgram(progId) == GL_FALSE) {
			LOG_INTO("Program not exist!\n");
			return;
		}

		glUseProgram(progId);
	}

	void ShaderProgram::DeleteShader()
	{
		DetachShader(vertId);
		DetachShader(fragId);

		glDeleteShader(vertId);
		glDeleteShader(fragId);
		glDeleteProgram(progId);

		vertId = 0;
		fragId = 0;
		progId = 0;
	}

	// ---------------------------------------------------------------------------

#ifndef CHEKC_ARGS
#define CHEKC_ARGS(name, id) \
	if (!name || !name[0]) { \
		LOG_INTO("String name is null!\n"); \
		return; \
	} \
	if (glIsProgram(progId) == GL_FALSE) { \
		LOG_INTO("Program not exist!\n"); \
		return; \
	}

	void ShaderProgram::SetBool(const char *name, bool value) const
	{
		CHEKC_ARGS(name, progId);
		glUniform1i(glGetUniformLocation(progId, name), (int)value);
	}

	void ShaderProgram::SetInt(const char *name, int value) const
	{
		CHEKC_ARGS(name, progId);
		glUniform1i(glGetUniformLocation(progId, name), value);
	}
	
	void ShaderProgram::SetFloat(const char *name, float value) const
	{
		CHEKC_ARGS(name, progId);
		glUniform1f(glGetUniformLocation(progId, name), value);
	}

	void ShaderProgram::SetVec2fv(const char *name, const float *value) const
	{
		CHEKC_ARGS(name, progId);
		glUniform2fv(glGetUniformLocation(progId, name), 1, value);
	}

	void ShaderProgram::SetVec2f(const char *name, float x, float y) const
	{
		CHEKC_ARGS(name, progId);
		glUniform2f(glGetUniformLocation(progId, name), x, y);
	}

	void ShaderProgram::SetMat3f(const char *name, const float *value) const
	{
		CHEKC_ARGS(name, progId);
		glUniformMatrix3fv(glGetUniformLocation(progId, name), 1, GL_FALSE, value);
	}

	void ShaderProgram::SetMat4f(const char *name, const float *value) const
	{
		CHEKC_ARGS(name, progId);
		glUniformMatrix4fv(glGetUniformLocation(progId, name), 1, GL_FALSE, value);
	}

#undef CHEKC_ARGS
#endif // CHEKC_ARGS
	// ---------------------------------------------------------------------------

	bool ShaderProgram::LoadFile(unsigned int shader, const char *name)
	{
		if (!name || !name[0]) {
			LOG_INTO("file name is null!\n");
			return false;
		}

		if (glIsShader(shader) == GL_FALSE) {
			LOG_INTO("Shader not exist!\n");
			return false;
		}

		bool ret = false;
		long size = 0;
		char *buff = NULL;
		char **src = NULL;

		std::FILE *file = std::fopen(name, "rb");

		if (!file) {
			LOG_INTO("open file failed!\n");
			return ret;
		}

		if (std::fseek(file, 0, SEEK_END)) {
			LOG_INTO("seek file failed!\n");
			goto err;
		}

		if ((size = std::ftell(file)) <= 0) {
			LOG_INTO("get file size failed!\n");
			goto err;
		}

		if (std::fseek(file, 0, SEEK_SET)) {
			LOG_INTO("seek file failed!\n");
			goto err;
		}

		buff = new char[size + 1];

		if (!buff) {
			LOG_INTO("mem not enough!\n");
			goto err;
		}
		std::memset(buff, 0, (size + 1) * sizeof(char));

		if (std::fread(buff, sizeof(char), size, file) != size) {
			LOG_INTO("read file error! size = %d\n", size);
			goto err;
		}

		glShaderSource(shader, 1, (const GLchar *const *)&buff, NULL);
		ret = CompileShader(shader);

	err:
		if (buff) {
			delete[] buff;
		}

		std::fclose(file);

		// 读取文件
		return ret;
	}

	bool ShaderProgram::CompileShader(unsigned int shader)
	{
		if (glIsShader(shader) == GL_FALSE) {
			LOG_INTO("Shader not exist!\n");
			return false;
		}

		glCompileShader(shader);

		GLint compRet = GL_TRUE;

		// 检查编译过程
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compRet);

		// 编译错误
		if (compRet != GL_TRUE) {
			int len = 0;

			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

			if (len <= 0) {
				LOG_INTO("Get compile log len error!\n");
				return false;
			}

			char *info = new char[len];

			if (!info) {
				LOG_INTO("mem not enough!\n");
				return false;
			}
			std::memset(info, 0, len * sizeof(char));
			
			glGetShaderInfoLog(shader, sizeof(char), NULL, info);
			LOG_INTO("%s\n", info);

			delete[] info;
			return false;
		}

		return true;
	}

	bool ShaderProgram::AttachShader(unsigned int shader)
	{
		if (glIsShader(shader) == GL_FALSE) {
			LOG_INTO("Shader not exist!\n");
			return false;
		}

		if (glIsProgram(progId) == GL_FALSE) {
			LOG_INTO("Program not exist!\n");
			return false;
		}

		glAttachShader(progId, shader);
		return true;
	}

	bool ShaderProgram::DetachShader(unsigned int shader) 
	{
		if (glIsShader(shader) == GL_FALSE) {
			LOG_INTO("Shader not exist!\n");
			return false;
		}

		if (glIsProgram(progId) == GL_FALSE) {
			LOG_INTO("Program not exist!\n");
			return false;
		}

		glDetachShader(progId, shader);
		return true;
	}

	bool ShaderProgram::LinkProgram() 
	{
		if (glIsProgram(progId) == GL_FALSE) {
			LOG_INTO("Program not exist!\n");
			return false;
		}

		glLinkProgram(progId);

		GLint linkRet = GL_TRUE;

		// 检查链接过程
		glGetProgramiv(progId, GL_LINK_STATUS, &linkRet);

		// 编译错误
		if (linkRet != GL_TRUE) {
			int len = 0;

			glGetProgramiv(progId, GL_INFO_LOG_LENGTH, &len);

			if (len <= 0) {
				LOG_INTO("Get link log len error!\n");
				return false;
			}

			char *info = new char[len];

			if (!info) {
				LOG_INTO("mem not enough!\n");
				return false;
			}
			std::memset(info, 0, len * sizeof(char));
			
			glGetProgramInfoLog(progId, sizeof(char), NULL, info);
			LOG_INTO("%s\n", info);

			delete[] info;
			return false;
		}

		return true;
	}
}
