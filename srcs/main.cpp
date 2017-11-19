/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:46:19 by bmickael          #+#    #+#             */
/*   Updated: 2017/11/18 13:46:24 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __cplusplus
extern "C" {
#endif
#include "SDL2/SDL.h"
#ifdef __cplusplus
}
#endif

#include <iostream>
#include <unistd.h>
#include "pool.hpp"

namespace mod1
{
class Draw
{
public:
	Draw ();
	~Draw ();
};
}

using namespace mod1;

Uint32 my_callbackfunc(Uint32 interval, void *param)
{
    SDL_Event event;
    SDL_UserEvent userevent;

    /* In this example, our callback pushes a function
    into the queue, and causes our callback to be called again at the
    same interval: */

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = param;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}

class Banane {
public:
	Banane();
	~Banane();
	void run();
	bool makeCoffee(ImgData &img);

private:
	void printI(void);
	int m_i = 5;
	Pool *pool;
};

/*
std::bind(&FlirdImplementation::sendInnerMsg,
			this,
			InnerMsg::RECORDING_STARTED),
*/

Banane::Banane() {};
Banane::~Banane() {};
void Banane::run(void) {
	Pool *pool = new Pool(std::bind(&Banane::makeCoffee, this));
	std::cout << pool->Init(250) << std::endl;

//	pool->DrawOnRawImage(std::bind(&Banane::makeCoffee, this));
//	pool->GetRenderedImage();

};

bool Banane::makeCoffee(ImgData &img) {
	(void)img;
	printI();
	delete(pool);
	return false;
};

void Banane::printI(void) {
	std::cout << m_i << std::endl;
}


int main(void)
{


	Banane *banane = new Banane();


	delete banane;


	SDL_Window* pWindow;
	SDL_Event	e;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER))
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    {
        /* Création de la fenêtre */

		Uint32 delay = 1000 / 25;  /* To round it down to the nearest 10 ms */
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
            //SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voie la fenêtre */

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
