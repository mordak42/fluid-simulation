
#include <csignal>
#include <iostream>

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

#ifdef __cplusplus
extern "C" {
#endif
#include "openblas/cblas.h"
#ifdef __cplusplus
}
#endif

#include <stdio.h>

void testBlast(void) {
    int i = 0;
    double A[6] = {1.0, 2.0, 1.0, -3.0, 4.0, -1.0};
    double B[6] = {1.0, 2.0, 1.0, -3.0, 4.0, -1.0};
    double C[9] = {.5, .5, .5, .5, .5, .5, .5, .5, .5};

    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans, 3, 3, 2, 1, A, 3, B, 3, 2, C, 3);

    for(i = 0; i < 9; i++)
        printf("%lf ", C[i]);
    printf("\n");
}

using namespace std;

int main(const int argc __attribute__((unused)),
         const char **argv __attribute__((unused)))
{
    testBlast();
    signalSetup();
    s_context = new mod1::Mod1();
    s_context->run();
    delete s_context;
    s_context = nullptr;
    return 0;
}
