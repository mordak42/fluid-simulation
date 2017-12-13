
#ifndef __CHRONOMETRIC_HPP__
# define __CHRONOMETRIC_HPP__

#include <chrono>

namespace lib
{
class Chronometric
{
public:
    Chronometric();
    ~Chronometric();

    void reset();
    double getTime();

private:
    std::chrono::high_resolution_clock::time_point m_originTime;
    bool m_ready = false;
};
}
#endif
