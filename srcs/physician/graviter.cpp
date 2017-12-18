
#include "graviter.hpp"

#include "opencl.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

static std::string readFile(std::string filename)
{
    std::ifstream file;
    file.open(filename);
    std::stringstream strstream;
    strstream << file.rdbuf();
    return strstream.str();
}

namespace mod1
{

Graviter::Graviter() {};
    
#define G (GRAVITY_FACTOR * 9.81)


void Graviter::applyGravity() {

    std::cout << "Beginning the test" << std::endl;

    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);
    if (all_platforms.size() == 0) {
        std::cerr << "No platforms found. Check OpenCL installation !" << std::endl;
        return;
    }
    cl::Platform default_platform = all_platforms[0];
    std::cout << "Using platform: "<< default_platform.getInfo<CL_PLATFORM_NAME>() << std::endl;

    /* get default device of the default platform */
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if (all_devices.size() == 0) {
        std::cerr << " No devices found. Check OpenCL installation !" << std::endl;
        return;
    }
    cl::Device default_device = all_devices[0];
    std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << std::endl;

    /* Creation of context */
    cl::Context context({default_device}, NULL, NULL, NULL, NULL);

    cl::Program::Sources sources;

    std::string fileContent = readFile("srcs/cl/gravity.cl");

    std::cout << fileContent.c_str() << std::endl;

    sources.push_back({fileContent.c_str(), fileContent.size()});



    cl::Program program(context, sources);

    if (program.build({default_device}) != CL_SUCCESS){
         std::cerr << " Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << std::endl;
         return;
     }

    cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, sizeof(struct velocity_field) * GRID_WIDTH * (GRID_HEIGHT + 1));
   // cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, sizeof(struct velocity_field) * 256);

    /* create queue to which we will push commands for the device. */
       cl::CommandQueue queue(context, default_device);

       cl::Kernel gravity(program, "gravity");
        gravity.setArg(0, buffer_A);

        //struct velocity_field m_grid_v[GRID_WIDTH][GRID_HEIGHT + 1];





        for (int y = 0; y < (GRID_HEIGHT + 1); y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                m_toto[x * (GRID_HEIGHT + 1) + y] = m_grid_v[x][y];
                //m_toto[y * GRID_WIDTH + x].val = -1;
            }
        }

     //   for (int i = 0; i < (GRID_WIDTH * (GRID_HEIGHT + 1)); i++)
     //       m_toto[i].val = 42;

        //struct velocity_field C[256];

        //for (int i = 0; i < 256; i++)
        //    C[i].val = 42;

       queue.enqueueWriteBuffer(
               buffer_A,
               CL_TRUE,
               0,
              sizeof(struct velocity_field) * GRID_WIDTH * (GRID_HEIGHT + 1),
           //    256 * sizeof(struct velocity_field),
               m_toto);

       queue.enqueueNDRangeKernel(
               gravity,
               cl::NullRange,
               cl::NDRange(GRID_HEIGHT * (GRID_WIDTH + 1)),
        //       cl::NDRange(256),
               cl::NullRange);

       queue.enqueueReadBuffer(
               buffer_A,
               CL_TRUE,
               0,
               sizeof(struct velocity_field) * GRID_WIDTH * (GRID_HEIGHT + 1),
               m_toto);


       for (int i = 0; i < (GRID_WIDTH * (GRID_HEIGHT + 1)); i++)
       {
           m_grid_v[i / (GRID_HEIGHT + 1)][i % (GRID_HEIGHT + 1)] = m_toto[i];
         //  m_grid_v[i / (GRID_HEIGHT + 1)][i % (GRID_HEIGHT + 1)].val = -3;
       }


       /*
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            if (GRID_V[i][j].weight > 0) {
                GRID_V[i][j].val += -(G * DT);
            }
        }
    }
    */

    //exit (1);
}

Graviter::~Graviter() {
}

}
