#include <SDL.h>
#include <iostream>
#include <math.h>

struct Location {
  int x;
  int y;
};

class Point {
public:
  double Angle;
  double X;
  double Y;

  double TriangleWave(double input, double multiplier) {
    double output =
        (2 * std::abs(std::fmod(((input - 0.5) * multiplier), 2) - 1)) - 1;
    return output;
  }
  struct Location GetLocation(double input, double angle) {
    double GetX = input * std::cos(angle);
    double GetY = input * std::sin(angle);
    Location loc = {GetX, GetY};
    return loc;
  }
};

int main(int argc, char *argv[]) {
  // Initilize SDL, otherwise return an error.
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not be initialized!" << std::endl
              << "SDL_Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Initialize window, otherwise return an error.
  SDL_Window *window =
      SDL_CreateWindow("CMake Project 1", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cout << "Window could not be created!" << std::endl
              << "SDL_Error: " << SDL_GetError() << std::endl;

    return 1;
  } else {
    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
      std::cout << "Renderer could not be created!" << std::endl
                << "SDL_Error: " << SDL_GetError() << std::endl;
      return 1;
    } else {
      // Set some initial variables
      int directionkey = 0b0000;
      int facing = 0b0001;
      bool quit = false;
      bool debug = false;

      while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
          switch (e.type) {
          case SDL_QUIT:
            quit = true;
            break;

          default:
            break;
          }
        }

				
				
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
      }
      SDL_DestroyRenderer(renderer);
    }
    SDL_DestroyWindow(window);
  }
  // Quit SDL and exit the program
  SDL_Quit();

  return 0;
}