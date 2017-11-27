#ifndef __USER_INTERFACE_HPP
# define __USER_INTERFACE_HPP

#ifdef __cplusplus
extern "C" {
#endif
#include "SDL2/SDL.h"
#ifdef __cplusplus
}
#endif

#include <iostream>
#include "pool.hpp"

namespace mod1
{
class UserInterface
{
public:
	UserInterface(const std::shared_ptr<mod1::Pool> &pool);
	~UserInterface();
	void start();

private:
	const std::shared_ptr<Pool> m_pool;
	SDL_Window					*win;
	SDL_Surface					*surface;
};
}

#endif
