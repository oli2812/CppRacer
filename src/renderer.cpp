#include "renderer.h"
#include <iostream>
#include <string>
#include <vector>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("CppRacer", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Car const car, std::deque<Obstacle> obstacles) {
  SDL_Rect block;

  int block_size = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);


  // Render car's body
  
  if (!car.alive) {
    //set draw color to red to indicate crash
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    block.x = car.outline.x * block_size;
    block.y = car.outline.y * block_size;
    block.w = car.outline.w * block_size;
    block.h = car.outline.h * block_size;

    SDL_RenderFillRect(sdl_renderer, &block);
  }
  else {
    //green car
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
    block.x = car.outline.x * block_size;
    block.y = car.outline.y * block_size;
    block.w = car.outline.w * block_size;
    block.h = car.outline.h * block_size;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  

  // Render obstacles
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  for (Obstacle &obstacle : obstacles) {
    if (obstacle.visible) {
      for (SDL_Rect &wall : obstacle.walls) {
        block.x = wall.x * block_size;
        block.y = wall.y * block_size;
        block.w = block_size;
        block.h = wall.h * block_size;
        
        SDL_RenderFillRect(sdl_renderer, &block);
      }
    }
  }
  

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}


void Renderer::UpdateWindowTitle(int score, float speed, Uint32 run_time) {
  std::string title{"Speed: " + std::to_string((int)(100*speed)) 
                + " Score: " + std::to_string(score) 
                + " Time: " + std::to_string(run_time/1000)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
