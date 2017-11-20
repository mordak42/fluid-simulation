
#include <memory>
#include "mod1.hpp"

/* Global context: */
static mod1::Mod1 *s_context = nullptr;

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    s_context = new mod1::Mod1();
    s_context->run();
    delete s_context;

    return 0;
}
