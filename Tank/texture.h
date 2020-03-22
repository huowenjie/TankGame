#ifndef __TEXTURE_H__
#define __TEXTURE_H__

namespace hwj 
{
	// 纹理信息
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

	// 逐帧动画纹理
	class AnimTexInfo : public TexInfo
	{
	public:
		AnimTexInfo() : mNum(0) {}

	public:
		unsigned int mNum;
	};

	// 生成默认纹理
	int GenDefTextures(const char *path);

	// 生成纹理信息对象
	TexInfo GenTexInfo(const char *path);

	// 生成逐帧动画纹理
	AnimTexInfo GenAnimTextures(const char *path, int num = 1);

	// 销毁纹理对象
	void DelTextures(unsigned int textures);
}

#endif // __TEXTURE_H__
