#ifndef __POOL__
# define __POOL__

#include <iostream>
#include <queue>

#include "imgData.hpp"

namespace mod1
{
class Pool {
public:
	Pool(std::function<bool(ImgData &)> cb = nullptr);
	~Pool();

	bool Init(int size);
	bool DrawOnRawImage(std::function<bool(ImgData &img)>draw);
	bool GetRenderedImage(std::function<bool(ImgData &img)>draw);

private:
	std::queue<ImgData> m_actives;
	std::queue<ImgData> m_inactives;
	std::function<bool>m_drawOnRawImageCallback(void);
	std::function<bool>m_GetRenderedImageCallback(ImgData &img);
	bool m_ready = false;
};
}

#endif
