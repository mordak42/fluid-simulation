#ifndef __POOL__
# define __POOL__

#include <iostream>
#include <queue>

#include "imgData.hpp"

namespace mod1
{
class Pool {
public:
	Pool(
		std::function<bool(ImgData &)> drawOnRawImageCallback = nullptr,
		std::function<bool(ImgData &)> getRenderedImageCallback = nullptr);
	~Pool();

	bool Init(int size);
	bool DrawOnRawImage(void);
	bool GetRenderedImage(void);

private:
	std::queue<ImgData> m_actives;
	std::queue<ImgData> m_inactives;
	const std::function<bool(ImgData &)> m_drawOnRawImageCallback;
    const std::function<bool(ImgData &)> m_getRenderedImageCallback;
	bool m_ready = false;
};
}

#endif
