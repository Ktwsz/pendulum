#include "screen.cpp"
#include "diff.cpp"

using namespace std;

const int32_t radius = 10;

struct pendulum {
    double l, theta, theta_dt, theta_2dt, C;
    int color_r = 0, color_g = 0, color_b = 0;
};

int main() {
    
    const int FPS = 30;
    const double dt = 1.0/FPS;
    const double g = 9.81;

    int auto_colors[3][3] = {{255, 0, 0}, {0, 0, 255}, {0,255,0}};
    
    int n;
    cout<<"Input number of pendulums: ";
    cin>>n;
    pendulum pendulums[n];
    for (int i = 0; i < n; ++i) {
        cout<<"Input theta and length for pendulum no"<<i+1<<": ";
        cin>>pendulums[i].theta>>pendulums[i].l;
        pendulums[i].theta = theta_to_rad(pendulums[i].theta);
        pendulums[i].theta_dt = pendulums[i].theta;
        pendulums[i].C = get_C(dt, pendulums[i].l, g);
        if (i < 3) pendulums[i].color_r = auto_colors[i][0], pendulums[i].color_g = auto_colors[i][1], pendulums[i].color_b = auto_colors[i][2];
    }
    
    SDL_Window *window = draw_window("wahadlo"), *graph = draw_window("wykres");
    if (window == NULL || graph == NULL) return 1;

    SDL_Renderer *renderer = set_renderer(window), *graph_rend = set_renderer(graph);
    if (renderer == NULL || graph_rend == NULL) return 1;
    
    draw_graph_background(graph_rend);


    const int frame_delay = 1000/(FPS);
    Uint32 frame_start;
    int frame_time;

    double time_ctr = 0;

    SDL_Event e;
    bool quit = 0;
    while (!quit) {
        frame_start = SDL_GetTicks();

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                    quit = 1;
                    break;
            }
        }

        clear_rend(renderer);

        for (int i = 0; i < n; ++i) {
            pendulums[i].theta_2dt = calc_th(pendulums[i].theta, pendulums[i].theta_dt, pendulums[i].C);
            PR r = get_r(pendulums[i].theta_2dt, pendulums[i].l);

            render_pendulum(renderer, (int32_t)r.first, (int32_t)r.second, radius, pendulums[i].color_r, pendulums[i].color_g, pendulums[i].color_b);
            render_graph(graph_rend, (int32_t)r.first, (int32_t)time_ctr, pendulums[i].color_r, pendulums[i].color_g, pendulums[i].color_b);

            pendulums[i].theta = pendulums[i].theta_dt;
            pendulums[i].theta_dt = pendulums[i].theta_2dt;
        }

        SDL_RenderPresent(renderer);
        SDL_RenderPresent(graph_rend);

        frame_time = SDL_GetTicks() - frame_start;
        if(frame_delay > frame_time) {
            SDL_Delay(frame_delay - frame_time);
        }
        time_ctr += 10*dt;
    }


    SDL_DestroyRenderer(renderer); 
    SDL_DestroyRenderer(graph_rend);
    SDL_DestroyWindow(window);
    SDL_DestroyWindow(graph);
    SDL_Quit();

    return 0;
}