#ifndef __VCOMBEY__
# define __VCOMBEY__

#include <iostream>
#include "pool.hpp"

namespace mod1
{
class Vcombey
{
public:
	Vcombey(std::shared_ptr<Pool>pool);
	~Vcombey();

private:
	std::shared_ptr<Pool> m_pool;
};
}

#endif
