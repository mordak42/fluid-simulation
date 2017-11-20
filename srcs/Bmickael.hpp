#ifndef __BMICKAEL__
# define __BMICKAEL__

#include <iostream>
#include "pool.hpp"

namespace mod1
{
class Bmickael
{
public:
	Bmickael(std::shared_ptr<Pool>pool);
	~Bmickael();

private:
	void pushImage();
	std::shared_ptr<Pool> m_pool;
};
}

#endif
