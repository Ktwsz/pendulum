#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

const int graph_offset = 20;
const int graph_spacing = 20;

SDL_Window* draw_window(const char * title) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window * window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_INPUT_FOCUS);
    if (window == NULL) {
        cout<<"err: "<<SDL_GetError()<<endl;
        return NULL;
    }

    return window;
}

SDL_Renderer* set_renderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        cout<<"err: "<<SDL_GetError()<<endl;
        return NULL;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);


    return renderer;
}

void draw_line(SDL_Renderer* renderer, int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void draw_circle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius) {
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void clear_rend(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderClear( renderer );
}

void render_pendulum(SDL_Renderer* renderer, int32_t posx, int32_t posy, int32_t radius, int color_r, int color_g, int color_b) {
    SDL_SetRenderDrawColor( renderer, color_r, color_g, color_b, 255 );
                    
    draw_circle(renderer, SCREEN_WIDTH/2+posx, posy, radius);
    draw_line(renderer, SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2+posx, posy);
}

void render_graph(SDL_Renderer* renderer, int32_t x, int32_t t, int color_r, int color_g, int color_b) {
    SDL_SetRenderDrawColor( renderer, color_r, color_g, color_b, 255 );
    draw_circle(renderer, graph_offset+t, SCREEN_HEIGHT/2+x, 2);
}


void draw_graph_background(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor( renderer, 157, 160, 163, 255 );

    for (int i = graph_offset+graph_spacing; i < SCREEN_WIDTH; i += graph_spacing) {
        SDL_RenderDrawLine(renderer, i, 0, i, SCREEN_HEIGHT);
    }
    for (int i = 0; i < SCREEN_HEIGHT; i += graph_spacing) {
        SDL_RenderDrawLine(renderer, 0, i, SCREEN_WIDTH, i);
    }

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

    SDL_RenderDrawLine(renderer, graph_offset, 0, graph_offset, SCREEN_HEIGHT);
    SDL_RenderDrawLine(renderer, 0, SCREEN_WIDTH/2, SCREEN_WIDTH, SCREEN_WIDTH/2);
    
    SDL_RenderPresent(renderer);
}
