#ifndef __TEXTURE_H__
#define __TEXTURE_H__

namespace hwj 
{
	// ����������
	class TexLoader
	{
	public:
		TexLoader();
		~TexLoader();

	public:
		// ����Ĭ������
		static int GenDefTextures(const char *path);
	};
}

#endif // __TEXTURE_H__
