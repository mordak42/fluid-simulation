
#ifndef __PHYSICIAN_HPP__
# define __PHYSICIAN_HPP__

#include <iostream>
#include <memory>
#include "pool.hpp"

namespace mod1
{
class Physician
{
public:
	Physician(const std::shared_ptr<mod1::Pool> &pool);
	~Physician();

private:
	const std::shared_ptr<Pool> m_pool;
};
}

#endif
