#ifndef __TEXTURE_H__
#define __TEXTURE_H__

namespace hwj 
{
	// ������Ϣ
	class TexInfo 
	{
	public:
		TexInfo() : 
			mTex(0), mWidth(0.0f), mHeight(0.0f) {}

	public:
		unsigned int mTex;
		float		 mWidth;
		float		 mHeight;
	};

	// ��֡��������
	class AnimTexInfo : public TexInfo
	{
	public:
		AnimTexInfo() : mNum(0) {}

	public:
		unsigned int mNum;
	};

	// ����Ĭ������
	int GenDefTextures(const char *path);

	// ����������Ϣ����
	TexInfo GenTexInfo(const char *path);

	// ������֡��������
	AnimTexInfo GenAnimTextures(const char *path, int num = 1);

	// �����������
	void DelTextures(unsigned int textures);
}

#endif // __TEXTURE_H__
