#include "inc/SDL.h"
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Paint",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << " Error:" << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        std::cerr << "Error" << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    bool quit = false;
    bool drawing = false;
    bool existed=false;
    SDL_Event event;
    int prevx,prevy;
    int x, y;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                        {
                            drawing = true;
                            existed=false;
                            prevx=x;
                            prevy=y;
                        }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                            drawing = false;
                            existed=true;
                    }
                    break;
            }
        }

        if (drawing) {

            SDL_GetMouseState(&x, &y);
            

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_Rect brush = { x - 2, y - 2, 4, 4 }; 
            SDL_RenderFillRect(renderer, &brush);
            if(!existed)
            {
                prevx=x;
                prevy=y;
                existed=true;
            }
                int ndots=64;//sqrt(pow((prevx-x),2)+pow((prevy-y),2))/16;
                double deltax=x,deltay=y;
                for(int i=0;i<ndots;i++)
                {
                   
                    SDL_Rect brush = { (int)deltax - 2, (int)deltay - 2, 4, 4 };
                    SDL_RenderFillRect(renderer, &brush);
                    deltax=deltax+((double)(prevx-x)/ndots);
                    deltay=deltay+((double)(prevy-y)/ndots);
                    cout<<deltax<<" "<<deltay<<endl;
                }
                prevx=x;
                prevy=y;
            
            SDL_RenderPresent(renderer); 
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}