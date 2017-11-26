
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
#include "graphicInterface/graphicInterface.hpp"
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
    std::unique_ptr<GraphicInterface> m_graphicInterface = nullptr;
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

void Mod1Implementation::run(void) {
    m_pool = std::make_shared<Pool>(50);
    m_pool->init();
    m_frameProductor.reset(new FrameProductor(m_pool));
    m_graphicInterface.reset(new GraphicInterface(m_pool));

//	m_frameProductor.start();
//	m_graphicInterface.init();

//	m_graphicInterface.loop();



    // main loop conditionned by value
}

void Mod1Implementation::stop(void) {
//    m_graphicInterface.exit();
}





/*
*/

/*
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
*/


/*
std::bind(&FlirdImplementation::sendInnerMsg,
            this,
            InnerMsg::RECORDING_STARTED),
*/

/*
Banane::Banane() {};
Banane::~Banane() {};
void Banane::run(void) {
    m_pool = std::make_shared<Pool>(
        std::bind(&Banane::makeCoffee,
        this,
        new ImgData());
    std::cout << m_pool->Init(250) << std::endl;

//    pool->DrawOnRawImage(std::bind(&Banane::makeCoffee, this));
//    pool->GetRenderedImage();

};

bool Banane::makeCoffee(ImgData &img) {
    (void)img;
    printI();
    return false;
};

void Banane::printI(void) {
    std::cout << m_i << std::endl;
}
*/

/*
int main(void)
{
//    Banane *banane = new Banane();
//    delete banane;


    SDL_Window* pWindow;
    SDL_Event    e;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER))
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    {
        // Création de la fenêtre

        Uint32 delay = 1000 / 25;  // To round it down to the nearest 10 ms
        SDL_TimerID my_timer_id = SDL_AddTimer(delay, my_callbackfunc, NULL);
        if((pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_CENTERED,
                                                                  SDL_WINDOWPOS_CENTERED,
                                                                  640,
                                                                  480,
                                                                  SDL_WINDOW_SHOWN)))

        {
            bool continueLoopHook = true;

            while (continueLoopHook && SDL_WaitEvent(&e)) {
                switch (e.type) {
                case SDL_KEYDOWN:
                    std::cout << "SDL_KEYDOWN: scancode -> " << e.key.keysym.scancode << std::endl;
                    if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                        continueLoopHook = false;
                    break;
                case SDL_QUIT:
                    continueLoopHook = false;
                    break;
                case SDL_USEREVENT:
                    std::cout << "tick at " << SDL_GetTicks() << std::endl;
                    break;
                default:
                    break;
                }
            }
            //SDL_Delay(3000);  Attendre trois secondes, que l'utilisateur voie la fenêtre

            SDL_DestroyWindow(pWindow);
            SDL_RemoveTimer(my_timer_id);
        }
        else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
    }

    SDL_Quit();

    return 0;
}
*/
