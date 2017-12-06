#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

    /*
    TTF_Font * font = TTF_OpenFont("/Library/Fonts/Comic Sans MS.ttf", 25);
    if (font == NULL)
        printf("font is null\n");
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface * surface = TTF_RenderText_Solid(font,
        "FAMINE", color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { 0, 0, texW, texH };

    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_RenderPresent(renderer);
    */
int main(int argc, char ** argv)
{
    int quit = 0;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window * window = SDL_CreateWindow("SDL_ttf in SDL2",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640,
        480, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    TTF_Font * font = TTF_OpenFont("/Library/Fonts/Comic Sans MS.ttf", 25);
    if (font == NULL)
        printf("font is null\n");
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface * surface = TTF_RenderText_Solid(font,
        "Welcome to Gigi Labs", color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { 0, 0, texW, texH };

    while (!quit)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                quit = 1;
                break;
        }

        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
    return 0;
}
