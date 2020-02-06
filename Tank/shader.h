#ifndef __SHADER_H__
#define __SHADER_H__

namespace hwj
{
	// 创建本类之前，需要首先初始化 opengl api
	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

	public:
		// 加载着色器脚本
		bool LoadShaderFile(const char *vert, const char *frag);

		// 使用程序
		void UseProgram();

		// 移除着色器
		void DeleteShader();

	public:
		void SetBool(const char *name, bool value) const;
		void SetInt(const char *name, int value) const;
		void SetFloat(const char *name, float value) const;

		void SetVec2fv(const char *name, const float *value) const;
		void SetVec2f(const char *name, float x, float y) const;
	
		void SetMat3f(const char *name, const float *value) const;
		void SetMat4f(const char *name, const float *value) const;
	
	protected:
		// 加载着色器并编译
		bool LoadFile(unsigned int shader, const char *name);
		
		// 编译着色器
		bool CompileShader(unsigned int shader);

		// 附加着色器
		bool AttachShader(unsigned int shader);

		// 分离着色器
		bool DetachShader(unsigned int shader);

		// 链接
		bool LinkProgram();

	protected:
		unsigned int vertId;
		unsigned int fragId;
		unsigned int progId;
	};
}

#endif // __SHADER_TOOL_H__
