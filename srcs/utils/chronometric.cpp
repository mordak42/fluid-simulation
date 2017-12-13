
#include "chronometric.hpp"

#include <iostream>

using namespace lib;

Chronometric::Chronometric() {}

Chronometric::~Chronometric() {}

void Chronometric::reset() {
    using namespace std::chrono;
    m_originTime = high_resolution_clock::now();
    m_ready = true;
}

double Chronometric::getTime() {
    if (m_ready == false) {
        std::cerr << "chronometric not initialized" << std::endl;
        return 0.;
    }
    using namespace std::chrono;
    std::chrono::high_resolution_clock::time_point timeNow = high_resolution_clock::now();

    return duration_cast<duration<double>>(timeNow - m_originTime).count();
}
