#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>

#define SCREEN_WIDTH 480
#define NUM_POINTS 360

struct Location {
  double x;
  double y;
};

// Methods
double DegreeToRadians(double degree) {
    double pi = 2 * std::acos(0.0);
    const double ratio = pi / 180;
    return degree * ratio;
}
double RadiansToDegree(double degree) {
    double pi = 2 * std::acos(0.0);
    const double ratio = 180 / pi;
    return degree * ratio;
}

double TriangleWave(double input, double multiplier) {
  double output =
      (2 * std::abs(std::fmod(((input - 0.5) * (multiplier / 100 )), 2) - 1)) - 1;
  return output;
}
struct Location GetLocation(double input, double angle) {
  double GetX = input * std::cos(angle);
  double GetY = input * std::sin(angle);
  Location loc = {GetX, GetY};
  return loc;
}

void RenderFivePixel(SDL_Renderer* renderer, int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
    SDL_RenderDrawPoint(renderer, x+1, y);
    SDL_RenderDrawPoint(renderer, x-1, y);
    SDL_RenderDrawPoint(renderer, x, y+1);
    SDL_RenderDrawPoint(renderer, x, y-1);
}


// Main function
int main(int argc, char *argv[]) {
  // Initilize SDL, otherwise return an error.
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not be initialized!" << std::endl
              << "SDL_Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Initialize window, otherwise return an error.
  SDL_Window *window =
      SDL_CreateWindow("Bounce", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_WIDTH, SDL_WINDOW_SHOWN);

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

        // SDL has been started, start doing things
        bool quit = false;

        double points[NUM_POINTS];

        for (int i = 0; i < NUM_POINTS; i++) {
            points[i] = DegreeToRadians((i + 1) * ((360 * (1 + std::trunc(NUM_POINTS / 360))) / NUM_POINTS)+90);
            // std::cout << (RadiansToDegree(points[i]) - 90) << std::endl;
        }
        double t = 0;

        // Primary loop
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
        if (t >= 0) { SDL_RenderClear(renderer); }
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        for (int i = 0; i < NUM_POINTS; i++) {
            double p = points[i];

            double rad = TriangleWave(p, t);
            Location loc = GetLocation(rad * 200, p);

            // SDL_RenderDrawPoint(renderer, (loc.x) + (SCREEN_WIDTH / 2), (loc.y) + (SCREEN_WIDTH / 2));
            RenderFivePixel(renderer, (loc.x) + (SCREEN_WIDTH / 2), (loc.y) + (SCREEN_WIDTH / 2));
        }
        SDL_RenderPresent(renderer);
        t = t + 0.0005;

      }
      SDL_DestroyRenderer(renderer);
    }
    SDL_DestroyWindow(window);
  }
  // Quit SDL and exit the program
  SDL_Quit();

  return 0;
}