
#include <csignal>
#include <iostream>

#include "mod1.hpp"

namespace std {
    /* Global context: */
    static mod1::Mod1 *s_context = nullptr;

    static void defaultSignalsHandler(int sigNum __attribute__((unused))) {
        exit(EXIT_FAILURE);
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

int main(const int argc __attribute__((unused)),
         const char **argv __attribute__((unused)))
{
    using namespace std;

    signalSetup();
    s_context = new mod1::Mod1();
    s_context->run();
    delete s_context;
    return 0;
}
