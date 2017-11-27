
#include "userInterface.hpp"

using namespace mod1;

UserInterface::UserInterface(const std::shared_ptr<mod1::Pool> &pool) : m_pool(pool) {
}

UserInterface::~UserInterface() {}

static void		print_rect(SDL_Surface *s)
{
	SDL_Rect srcrect;
	
	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = s->w;
	srcrect.h = s->h;
	SDL_FillRect(s, &srcrect, SDL_MapRGB(s->format, 0, 0, 0));
	srcrect.x = s->w / 4;
	srcrect.y = s->h / 4;
	srcrect.w = s->w / 2;
	srcrect.h = s->h / 2;
	SDL_FillRect(s, &srcrect, SDL_MapRGB(s->format, 66, 244, 134));
}

void UserInterface::start() {
	SDL_Event		e;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER))
	{
		fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
		return ;
	}
	{
		// Création de la fenêtre
		//Uint32 delay = 1000 / 25;  // To round it down to the nearest 10 ms
		//SDL_TimerID my_timer_id = SDL_AddTimer(delay, my_callbackfunc, NULL);
		if((win = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_CENTERED,
						SDL_WINDOWPOS_CENTERED,
						640,
						480,
						SDL_WINDOW_SHOWN)))
		{
			std::cout << "LOL XD CA MARCHE" << std::endl;
			surface = SDL_GetWindowSurface(win);
			bool continueLoopHook = true;
			while (continueLoopHook && SDL_WaitEvent(&e)) {
				print_rect(surface);
				SDL_UpdateWindowSurface(win);
					switch (e.type) {
						case SDL_KEYDOWN:
							std::cout << "SDL_KEYDOWN: scancode -> " << e.key.keysym.scancode << std::endl;
							if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
								continueLoopHook = false;
							break;
						case SDL_QUIT:
							continueLoopHook = false;
							break;
							//case SDL_USEREVENT:
							//	std::cout << "tick at " << SDL_GetTicks() << std::endl;
							//	break;
						default:
							break;
					}
			}
			SDL_DestroyWindow(win);
			//SDL_RemoveTimer(my_timer_id);
		}
		else
			fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

	SDL_Quit();
}
