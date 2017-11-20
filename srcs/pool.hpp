
#ifndef __POOL_HPP__
# define __POOL_HPP__

#include <iostream>
#include <queue>

#include "imgData.hpp"

namespace mod1
{
class Pool {
public:
	Pool();
	~Pool();

	bool init(int size);
	bool drawOnRawImage(ImgData **output);
	bool getRenderedImage(ImgData **output);

private:
	std::queue<ImgData> m_actives;
	std::queue<ImgData> m_inactives;
	bool m_ready = false;
};
}

#endif
