
#ifdef __cplusplus
extern "C" {
#endif
#include "SDL2/SDL.h"
#ifdef __cplusplus
}
#endif

#include <unistd.h>
#include <iostream>
#include <memory>
#include "mod1.hpp"
#include "frameProductor/frameProductor.hpp"
#include "userInterface/userInterface.hpp"
#include "pool.hpp"

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
    std::shared_ptr<Pool> m_pool;
};
}

using namespace mod1;

/* ***** Mod1's methods implementation ***** */
Mod1::Mod1()
  : m_implementation(new Mod1Implementation()) {}

Mod1::~Mod1() {}

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

Uint32 my_callbackfunc(Uint32 interval, void *param)
{
    SDL_Event event;
    SDL_UserEvent userevent;

    // In this example, our callback pushes a function
    // into the queue, and causes our callback to be called again at the
    // same interval:

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = param;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}

#include <unistd.h>

void Mod1Implementation::run(void) {
    m_pool = std::make_shared<Pool>(250);
    m_pool->init();
    std::cout << "initialisation done" << std::endl;
    m_frameProductor.reset(new FrameProductor(m_pool));
    m_userInterface.reset(new UserInterface(m_pool, 1920, 1080));

    m_frameProductor->start();

/*
    while (1) {
        usleep(1000000 / 25);
        ImgData *img = m_pool->popRenderedFrame();
        if (img == nullptr)
            continue;
        m_pool->pushOutdatedFrame(img);
        (void)img;
    }
*/

    m_userInterface->init();
    m_userInterface->start();

    // m_userInterface.loop();
    // main loop conditionned by value
}

void Mod1Implementation::stop(void) {
//    m_userInterface.exit();
}
