
#include <csignal>
#include <iostream>
#include <memory>

#include "mod1.hpp"

namespace std {

/* Global context: */
static mod1::Mod1 *s_context = nullptr;

static void defaultSignalsHandler(int sigNum) {
    (void)sigNum;
    s_context->stop();
}

static void segvSignalsHandler(int sigNum) {
    (void)sigNum;
    cout << "Segmentation fault, you are Vcombey i think..." << endl;
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

int main(int argc, char **argv)
{
    using namespace std;

    (void)argc;
    (void)argv;

    signalSetup();
    s_context = new mod1::Mod1();
    s_context->run();
    delete s_context;

    return 0;
}
