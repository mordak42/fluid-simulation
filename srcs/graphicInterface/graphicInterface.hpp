#ifndef __GRAPHIC_INTERFACE_HPP
# define __GRAPHIC_INTERFACE_HPP

#include <iostream>
#include "pool.hpp"

namespace mod1
{
class GraphicInterface
{
public:
    GraphicInterface(const std::shared_ptr<mod1::Pool> &pool);
    ~GraphicInterface();

private:
    const std::shared_ptr<Pool> m_pool;
};
}

#endif
