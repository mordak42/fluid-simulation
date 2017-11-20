#ifndef __RENDERER__
# define __RENDERER__

#include <iostream>
#include <memory>
#include "pool.hpp"

namespace mod1
{
class Renderer
{
public:
	Renderer(const std::shared_ptr<mod1::Pool> &pool);

//	const std::shared_ptr<flir::Frame> &pool
	~Renderer();

private:
	void pushImage();
	const std::shared_ptr<Pool> m_pool;
};
}

#endif
