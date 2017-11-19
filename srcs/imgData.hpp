
#ifndef __IMG_DATA__
# define __IMG_DATA__
# define SIZE 1920 * 1080
namespace mod1
{
class ImgData {
public:
	char img[SIZE] = {0};
	bool isReady = false;
};
}

#endif
