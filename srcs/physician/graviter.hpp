
#ifndef __GRAVITER_HPP__
# define __GRAVITER_HPP__

#include "opencl.hpp"

#define GRAVITY_FACTOR 1

#include <iostream>
#include <memory>

#include "physicItems.hpp"
#include "physicLaw.hpp"

namespace mod1
{
class Graviter : public virtual PhysicLaw, public virtual PhysicItems
{
public:
     Graviter();
    ~Graviter();
    void solve_pressure(void);
    void update_velocity(void);
    void applyGravity();
private:
    struct velocity_field m_toto[GRID_WIDTH * (GRID_HEIGHT + 1)];

    std::vector<cl::Platform> m_all_platforms;
    cl::Platform m_default_platform;
    std::vector<cl::Device> m_all_devices;
    cl::Device m_default_device;
    cl::Context m_context;
    cl::Program::Sources m_sources;
    cl::Program m_program;
    cl::Buffer m_buffer_grid_v;
    cl::CommandQueue m_queue;
    cl::Kernel m_gravity;
};
}

#endif
