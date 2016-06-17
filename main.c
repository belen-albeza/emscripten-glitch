#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#if __EMSCRIPTEN__
#include <emscripten.h>
#endif

// =============================================================================
// GLOBALS
// =============================================================================

SDL_Window *g_window = NULL;
SDL_Surface *g_screen = NULL;

// =============================================================================
// UTILS
// =============================================================================

SDL_Surface* load_image(char *filename) {
    SDL_Surface *optimized = NULL;
    SDL_Surface *raw = IMG_Load(filename);

    if (raw == NULL) {
        fprintf(stderr, "Unable to load image %s - %s\n", filename,
            SDL_GetError());
    }
    else {
        optimized = SDL_ConvertSurface(raw, g_screen->format, 0);
        if (optimized == NULL) {
            fprintf(stderr, "Unable to optimize image %s - %s", filename,
                SDL_GetError());
        }
        SDL_SetSurfaceBlendMode(optimized, SDL_BLENDMODE_BLEND);
    }
    return optimized;
}

void draw_image(SDL_Surface *image, int x, int y) {
    SDL_Rect rect = {x, y, image->w, image->h};
    SDL_BlitSurface(image, NULL, g_screen, &rect);
}


// =============================================================================
// MAIN
// =============================================================================

unsigned int startup(char *title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 0;
    }
    else {
        g_window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            550, 600,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
        g_screen = SDL_GetWindowSurface(g_window);
        SDL_GL_SetSwapInterval(1);
        return 1;
    }
}

int main (int argc, char **argv) {
    SDL_Surface *screen = NULL;
    SDL_Window *window = NULL;

    if (startup("Space Shooter")) {
        SDL_Surface *background = load_image("assets/background.png");
        SDL_Surface *ship = load_image("assets/captain.png");

        draw_image(background, 0, 0);
        draw_image(ship, 100, 100);
        SDL_UpdateWindowSurface(g_window);

        #if __EMSCRIPTEN__
        #else
            SDL_Delay(5000);
        #endif

        SDL_FreeSurface(background);
        SDL_FreeSurface(ship);
    }
    else {
        printf("Could not initialise SDL\n");
    }

    SDL_DestroyWindow(g_window);
    SDL_Quit();
    return 0;
}
