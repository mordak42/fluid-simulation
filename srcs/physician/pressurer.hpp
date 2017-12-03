
#ifndef __PRESSURER_HPP__
# define __PRESSURER_HPP__

#include <iostream>
#include <memory>

#include "physicItems.hpp"
#include "physicLaw.hpp"

namespace mod1
{
class Pressurer : public virtual PhysicLaw
{
public:
    Pressurer(const std::shared_ptr<PhysicItems> &physicItems);
    ~Pressurer();
    void solve_pressure(void);
	void update_velocity(void);
private:
    const std::shared_ptr<PhysicItems> &m_physicItems;
};
}

#endif
