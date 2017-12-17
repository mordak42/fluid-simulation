
#include <unistd.h>
#include <iostream>
#include <memory>

#include "frameProductor.hpp"
#include "userInterface.hpp"
#include "utils/pool.hpp"
#include "renderer/renderedFrame.hpp"

namespace mod1
{
class Mod1Implementation {
public:
    Mod1Implementation();
    ~Mod1Implementation();
    void run(void);
    void stop(void);

protected:

private:
    std::unique_ptr<FrameProductor> m_frameProductor = nullptr;
    std::unique_ptr<UserInterface> m_userInterface = nullptr;
    std::shared_ptr<lib::Pool<RenderedFrame>> m_pool;
};
}

using namespace mod1;

/* ***** Mod1's methods implementation ***** */
Mod1::Mod1() : m_implementation(new Mod1Implementation()) {}

Mod1::~Mod1() {
}

void Mod1::run()
{
    m_implementation->run();
}

void Mod1::stop()
{
    m_implementation->stop();
}


Mod1Implementation::Mod1Implementation() {
}

Mod1Implementation::~Mod1Implementation() {
}

#include "utils/gpu.hpp"

void Mod1Implementation::run(void) {
    lib::Gpu experiment;
    experiment.mainTest();

    m_pool = std::make_shared<lib::Pool<RenderedFrame>>(NB_BUFFERED_FRAMES);

    m_pool->init();
    std::cout << "initialization done" << std::endl;
    m_frameProductor.reset(new FrameProductor(m_pool));
    m_userInterface.reset(new UserInterface(m_pool, 1920, 1080));

    if (!m_frameProductor->parseFile())
        return;
    m_frameProductor->start();
    m_userInterface->init();

    /* main loop */
    m_userInterface->start();
    m_frameProductor->stop();
}

void Mod1Implementation::stop(void) {
    m_userInterface->stop();
}
