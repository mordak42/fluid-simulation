
#ifndef __IMG_DATA_HPP__
# define __IMG_DATA_HPP__
# define SIZE 1920 * 1080 * 3

namespace mod1
{
class ImgData {
public:
	ImgData();
	~ImgData();

	char img[SIZE] = {0};
	bool isReady = false;
};
}

#endif
