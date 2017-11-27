#ifndef __USER_INTERFACE_HPP
# define __USER_INTERFACE_HPP

#include <iostream>
#include "pool.hpp"

namespace mod1
{
class UserInterface
{
public:
    UserInterface(const std::shared_ptr<mod1::Pool> &pool);
    ~UserInterface();

private:
    const std::shared_ptr<Pool> m_pool;
};
}

#endif
