#ifndef __TEXTURE_H__
#define __TEXTURE_H__

namespace hwj 
{
	// 纹理生成器
	class TexLoader
	{
	public:
		TexLoader();
		~TexLoader();

	public:
		// 生成默认纹理
		static int GenDefTextures(const char *path);
	};
}

#endif // __TEXTURE_H__
