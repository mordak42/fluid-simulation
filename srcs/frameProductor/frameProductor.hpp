#ifndef __FRAME_PRODUCTOR_HPP__
# define __FRAME_PRODUCTOR_HPP__

#include <iostream>
#include <thread>
#include "pool.hpp"
#include "renderer/renderer.hpp"
#include "physician/physician.hpp"
#include "utils/polynom.hpp"

/*
 * Some explications about auo amd new int[x][y][z] on the heap,
 * https://stackoverflow.com/questions/17258749/is-there-a-way-of-casting-a-pointer-to-an-array-type
 * https://www.reddit.com/r/cpp/comments/6ge86r/auto_for_in_class_initialization_of_nonstatic/
 * http://en.cppreference.com/w/cpp/types/decay
*/

#define auto_init(variable, value) std::decay<decltype(value)>::type variable = value

namespace mod1
{
class FrameProductor
{
public:
    FrameProductor(const std::shared_ptr<mod1::Pool> &pool);
    ~FrameProductor();
    void start();
    void stop();
//    bool parseFile(const char &buff);
    bool parseFile();

private:
    void threadHandler();
    void raytrace(ImgData *img);

    const std::shared_ptr<Pool> m_pool;
    std::unique_ptr<Renderer> m_renderer = nullptr;
    std::unique_ptr<Physician> m_physician = nullptr;
    bool m_keepGoing = false;
    auto_init(m_grid, new int[2000][1000]);
    Polynom m_groundLevel;
};
}

#endif
