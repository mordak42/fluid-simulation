
#include <csignal>
#include <iostream>
#include <memory>

#include "mod1.hpp"

/* Global context: */
static mod1::Mod1 *s_context = nullptr;

static void signalsHandler(int sigNum) {
    (void)sigNum;
    s_context->stop();
}

/* clean exit on SIGINT & SIGTERM */
static void signalSetup(void) {
    std::signal(SIGINT, &signalsHandler);
    std::signal(SIGTERM, &signalsHandler);
    std::signal(SIGQUIT, &signalsHandler);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    signalSetup();
    s_context = new mod1::Mod1();
    s_context->run();
    delete s_context;

    return 0;
}
