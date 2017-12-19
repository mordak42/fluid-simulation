
#include "graviter.hpp"

namespace mod1
{

Graviter::Graviter() {
    std::cout << "Beginning the test" << std::endl;

    cl::Platform::get(&m_all_platforms);
    if (m_all_platforms.size() == 0) {
        std::cerr << "No platforms found. Check OpenCL installation !" << std::endl;
        return;
    }

    m_default_platform = cl::Platform(m_all_platforms[0]);
    std::cout << "Using platform: "<< m_default_platform.getInfo<CL_PLATFORM_NAME>() << std::endl;

    /* get default device of the default platform */
    m_default_platform.getDevices(CL_DEVICE_TYPE_ALL, &m_all_devices);
    if (m_all_devices.size() == 0) {
        std::cerr << " No devices found. Check OpenCL installation !" << std::endl;
        return;
    }

    m_default_device = cl::Device(m_all_devices[1]);
    std::cout << "Using device: " << m_default_device.getInfo<CL_DEVICE_NAME>() << std::endl;

    /* Creation of context */
    m_context = cl::Context({m_default_device}, NULL, NULL, NULL, NULL);

    std::string fileContent = parseClFile("srcs/cl/gravity.cl");

    std::cout << fileContent.c_str() << std::endl;

    m_sources.push_back({fileContent.c_str(), fileContent.size()});

    m_program = cl::Program(m_context, m_sources);

    if (m_program.build({m_default_device}) != CL_SUCCESS){
        std::cerr << " Error building: " << m_program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(m_default_device) << std::endl;
        return;
    }

    m_buffer_grid_v = cl::Buffer(
            m_context,
            CL_MEM_READ_WRITE,
            sizeof(struct velocity_field) * GRID_WIDTH * (GRID_HEIGHT + 1));

    /* create queue to which we will push commands for the device. */
    m_queue = cl::CommandQueue(m_context, m_default_device);

    m_gravity = cl::Kernel(m_program, "gravity");
    m_gravity.setArg(0, m_buffer_grid_v);
};

#define G (GRAVITY_FACTOR * 9.81)

/* https://software.intel.com/en-us/articles/getting-the-most-from-opencl-12-how-to-increase-performance-by-minimizing-buffer-copies-on-intel-processor-graphics */

void Graviter::applyGravity() {
    serializeGridV(m_toto, m_grid_v);

    m_queue.enqueueWriteBuffer(
            m_buffer_grid_v,
            CL_TRUE,
            0,
            sizeof(struct velocity_field) * GRID_WIDTH * (GRID_HEIGHT + 1),
            m_toto);

    m_queue.enqueueNDRangeKernel(
            m_gravity,
            cl::NullRange,
            cl::NDRange(GRID_HEIGHT * (GRID_WIDTH + 1)),
            cl::NullRange);
    m_queue.finish();

    m_queue.enqueueReadBuffer(
            m_buffer_grid_v,
            CL_TRUE,
            0,
            sizeof(struct velocity_field) * GRID_WIDTH * (GRID_HEIGHT + 1),
            m_toto);

    /*
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            if (GRID_V[i][j].weight > 0) {
                GRID_V[i][j].val += -(G * DT);
            }
        }
    }
    */
    unserializeGridV(m_grid_v, m_toto);
}

Graviter::~Graviter() {
}

}
