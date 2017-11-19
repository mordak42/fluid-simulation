#ifndef __POOL__
# define __POOL__

#include <iostream>
#include <queue>
#include "imgData.hpp"

namespace mod1
{
class Pool {
public:
	Pool();
	~Pool();

	bool Init(int size);
	bool GetRawImage(ImgData& image);
	bool GetRenderedImage(ImgData& image);

private:
	std::queue<ImgData> m_actives;
	std::queue<ImgData> m_inactives;
	bool m_ready = false;
};
}

#endif
