#ifndef __TEXTURE_H__
#define __TEXTURE_H__

namespace hwj 
{
	// ������Ϣ
	typedef struct AnimTexInfo_st {
		unsigned int	mTex;
		int				mNum;
		float			mWidth;
		float			mHeight;
	} AnimTexInfo;

	// ����Ĭ������
	int GenDefTextures(const char *path);

	// ������֡��������
	AnimTexInfo GenAnimTextures(const char *path, int num = 1);

	// �����������
	void DelTextures(unsigned int textures);
}

#endif // __TEXTURE_H__
