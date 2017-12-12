
#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 120
#include "opencl.hpp"

#include <iostream>
#include <csignal>

#include "mod1.hpp"

namespace std {
    /* Global context: */
    static mod1::Mod1 *s_context = nullptr;

    static void defaultSignalsHandler(int sigNum __attribute__((unused))) {
        if (s_context != nullptr)
            s_context->stop();
        else
            exit(EXIT_SUCCESS);
    }

    static void segvSignalsHandler(int sigNum __attribute__((unused))) {
        cout << "Segmentation fault. Please repair yours mistakes" << endl;
        exit(EXIT_FAILURE);
    }

    /* clean exit on SIGINT & SIGTERM */
    static void signalSetup(void) {
        signal(SIGINT, &defaultSignalsHandler);
        signal(SIGTERM, &defaultSignalsHandler);
        signal(SIGQUIT, &defaultSignalsHandler);

        signal(SIGSEGV, &segvSignalsHandler);
    }
}

using namespace std;

int main(const int argc __attribute__((unused)),
         const char **argv __attribute__((unused)))
{
    signalSetup();
    s_context = new mod1::Mod1();
    s_context->run();
    delete s_context;
    s_context = nullptr;
    return 0;
}
