
#ifndef __MOD1_HPP__
# define __MOD1_HPP__

#include <memory>

# define NB_BUFFERED_FRAMES 1

namespace mod1
{

class Mod1Implementation;

class Mod1
{
public:
    Mod1();
    ~Mod1();

    void run();
    void stop();

private:
    std::unique_ptr<Mod1Implementation> m_implementation;
};
}

#endif
