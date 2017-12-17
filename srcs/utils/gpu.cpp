
#include "gpu.hpp"

#include <iostream>

using namespace lib;

Gpu::Gpu() {}

Gpu::~Gpu() {}

void Gpu::mainTest() {
    std::cout << "Beginning the test" << std::endl;

    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);
    if (all_platforms.size() == 0) {
        std::cerr << "No platforms found. Check OpenCL installation !" << std::endl;
        return;
    }
    cl::Platform default_platform = all_platforms[1];
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

    /* kernel calculates for each element C=A+B */
    std::string kernel_code =
            "void kernel simple_add(global const int* A, global const int* B, global int* C) {"
            "   C[get_global_id(0)] = A[get_global_id(0)] + B[get_global_id(0)];"
            "}";


    /* kernel calculates for each element C=A+B */
    std::string kernel_code2 =
            "void kernel simple_mul(global const int* A, global const int* B, global int* C) {"
            "   C[get_global_id(0)] = A[get_global_id(0)] * B[get_global_id(0)];"
            "   printf(\"%i \", A[get_global_id(0)]);"
            "}";

    /* Creation of context */
    cl::Context context({default_device}, NULL, NULL, NULL);

    /* Introduce program */
    cl::Program::Sources sources;

    sources.push_back({kernel_code.c_str() , kernel_code.length()});
    sources.push_back({kernel_code2.c_str() , kernel_code2.length()});

    cl::Program program(context, sources);

    if (program.build({default_device}) != CL_SUCCESS){
        std::cerr << " Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << std::endl;
        return;
    }

    /* Creation des variables locales */
//    int A[64] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
//    int B[64] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0};

    /* Introduction de la memoire partagee */
 //   cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, sizeof(int)*10);
 //   cl::Buffer buffer_B(context, CL_MEM_READ_WRITE, sizeof(int)*10);


    cl::Buffer buffer_C(context, CL_MEM_READ_WRITE, sizeof(int) * 64);
    cl::Buffer buffer_D(context, CL_MEM_READ_WRITE, sizeof(int) * 64);

    int N = 64;

    ::size_t size = N * sizeof(int); // size must be a multiple of 64
    ::size_t alignment = 4096;
    // Allocate aligned memory on the host. The particular function is OS-dependent.
    //  memalign(size_t alignment, size_t size) on Linux, release memory with free(...)
    //  _aligned_malloc(size_t size, size_t alignment) on Windows, release with _aligned_free(...)
    //  posix_memalign(void ** ptr, size_t alignment, size_t size) on OSX, release with free(...)

    int *g_results;
    int *h_results;

    posix_memalign((void **)&g_results, alignment, size);
    posix_memalign((void **)&h_results, alignment, size);



    /* create queue to which we will push commands for the device. */
    cl::CommandQueue queue(context, default_device);

    for (int i = 0; i < N; i++) {
        g_results[i] = i;
        h_results[i] = N - i - 1;
    }

    // Create an OpenCL buffer using the host pointer
    cl::Buffer buffer_A = cl::Buffer(context, CL_MEM_USE_HOST_PTR, size, h_results);
    cl::Buffer buffer_B = cl::Buffer(context, CL_MEM_USE_HOST_PTR, size, g_results);

    /* write arrays A and B to the device */
    //queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int) * 64, A);
    //queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, sizeof(int) * 64, B);




/*
    cl::KernelFunctor simple_add(
            cl::Kernel(program, "simple_add"),
            queue,cl::NullRange,
            cl::NDRange(10),
            cl::NullRange);
*/
    cl::Kernel simple_add(program, "simple_add");
    simple_add.setArg(0, buffer_A);
    simple_add.setArg(1, buffer_B);
    simple_add.setArg(2, buffer_C);

    cl::Kernel simple_mul(program, "simple_mul");
    simple_mul.setArg(0, buffer_A);
    simple_mul.setArg(1, buffer_B);
    simple_mul.setArg(2, buffer_C);



    queue.enqueueNDRangeKernel(
            simple_add,
            cl::NullRange,
            cl::NDRange(64),
            cl::NullRange);

    int C[64];
    //read result C from the device to array C

    queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0 ,sizeof(int) * 64, C);


    // Get exclusive access to the buffer
    int *t1 = (int*) queue.enqueueMapBuffer(buffer_A, CL_TRUE, CL_MAP_WRITE, 0, size);
    int *t2 = (int*) queue.enqueueMapBuffer(buffer_B, CL_TRUE, CL_MAP_WRITE, 0, size);

    t1[0] = 1000;
    t2[0] = 1000;

    queue.enqueueUnmapMemObject(buffer_A, t1);
    queue.enqueueUnmapMemObject(buffer_B, t2);


    std::cout << "result:";
    for(int i = 0; i < 64; i++)
        std::cout << C[i] << " ";
    std::cout << std::endl;

    queue.enqueueNDRangeKernel(
            simple_mul,
            cl::NullRange,
            cl::NDRange(64),
            cl::NullRange);

    //read result C from the device to array C
    queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0 ,sizeof(int) * 64, C);

    std::cout << "result:";
    for (int i=0; i < 64; i++)
        std::cout << C[i] << " ";
    std::cout << std::endl;

    queue.enqueueNDRangeKernel(
            simple_add,
            cl::NullRange,
            cl::NDRange(64),
            cl::NullRange);

    //read result C from the device to array C
    queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0 ,sizeof(int) * 64, C);

    std::cout << "result:";
    for (int i = 0; i < 64; i++)
        std::cout << C[i] << " ";
    std::cout << std::endl;

   // queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int) * 10, A);
   // queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, sizeof(int) * 10, B);


    int D[64];

    t1[0] = 11;
    t2[0] = 11;

    queue.enqueueUnmapMemObject(buffer_A, t1);
    queue.enqueueUnmapMemObject(buffer_B, t2);

    simple_mul.setArg(2, buffer_D);

    queue.enqueueNDRangeKernel(
            simple_mul,
            cl::NullRange,
            cl::NDRange(64),
            cl::NullRange);

    queue.enqueueReadBuffer(buffer_D, CL_TRUE, 0 ,sizeof(int) * 64, D);

    std::cout << "result:";
    for (int i = 0; i < 64; i++)
        std::cout << D[i] << " ";
    std::cout << std::endl;
    return;
}
