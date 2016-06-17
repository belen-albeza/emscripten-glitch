# emscripten-glitch

Compile natively with GCC. In order for this to work you need to have SDL2 installed in your system and link to the actual libraries (here are the paths that are created with `brew install sdl2`).

```
 gcc main.c -I/usr/local/include -D_THREAD_SAFE -L/usr/local/lib -lSDL2 -lSDL2_Image -o main
 ```

 Compile with emscripten:

```
 emcc main.c -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -o dist/index.html -O2 --preload-file assets
 ```
