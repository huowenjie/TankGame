#ifndef __SHADER_H__
#define __SHADER_H__

namespace hwj
{
	// ��������֮ǰ����Ҫ���ȳ�ʼ�� opengl api
	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

	public:
		// ������ɫ���ű�
		bool LoadShaderFile(const char *vert, const char *frag);

		// ʹ�ó���
		void UseProgram();

		// �Ƴ���ɫ��
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
		// ������ɫ��������
		bool LoadFile(unsigned int shader, const char *name);
		
		// ������ɫ��
		bool CompileShader(unsigned int shader);

		// ������ɫ��
		bool AttachShader(unsigned int shader);

		// ������ɫ��
		bool DetachShader(unsigned int shader);

		// ����
		bool LinkProgram();

	protected:
		unsigned int vertId;
		unsigned int fragId;
		unsigned int progId;
	};
}

#endif // __SHADER_TOOL_H__
