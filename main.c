#include <time.h>
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600

#define DROP_COUNT 600

typedef struct {
    float x, y;
    float speed;
    float length;
} Drop;

Drop drops[DROP_COUNT];

void reset_drop(Drop *d) {
    d->x = rand() % WIDTH;
    d->y = rand() % HEIGHT - HEIGHT;
    d->speed = 6 + rand() % 12;
    d->length = 8 + rand() % 20;
}

int main() {
    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *win = SDL_CreateWindow(
        "rain",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer *render = SDL_CreateRenderer(
        win, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    for (int i = 0; i < DROP_COUNT; i++) reset_drop(&drops[i]);

    int rung = 1;
    SDL_Event e;

    float wind = 0.6f;

    while (rung) {
        while (SDL_PollEvent(&e)) if (e.type == SDL_QUIT) rung = 0;

        SDL_SetRenderDrawColor(render, 10, 15, 25, 255);
        SDL_RenderClear(render);

        SDL_SetRenderDrawColor(render, 130, 180, 255, 255);

        for (int i = 0; i < DROP_COUNT; i++) {
            Drop *d = &drops[i];

            d->y += d->speed;
            d->x += wind;

            if (d->y > HEIGHT) reset_drop(d);
            SDL_RenderDrawLine(
                render,
                (int)d->x, (int)d->y,
                (int)d->x, (int)(d->y + d->length)
            );
        }

        SDL_RenderPresent(render);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
