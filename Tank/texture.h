#ifndef __TEXTURE_H__
#define __TEXTURE_H__

namespace hwj 
{
	// 纹理信息
	typedef struct AnimTexInfo_st {
		unsigned int	mTex;
		int				mNum;
		float			mWidth;
		float			mHeight;
	} AnimTexInfo;

	// 生成默认纹理
	int GenDefTextures(const char *path);

	// 生成逐帧动画纹理
	AnimTexInfo GenAnimTextures(const char *path, int num = 1);

	// 销毁纹理对象
	void DelTextures(unsigned int textures);
}

#endif // __TEXTURE_H__
