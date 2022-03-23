#include "game.h"
#include <iostream>
#include "SDL.h"


Game::Game(std::size_t grid_width, std::size_t grid_height)
    : car(grid_width, grid_height) {}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  
  
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  Uint32 start_time = title_timestamp;

  int frame_count = 0;
  bool running = true;

  // intialize list of obstacles: load from file and store in deque
  Obstacle obstacle(0);
  obstacle.Init(obstacles);

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, car);
    Update();
    renderer.Render(car, obstacles);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    //measure current run time
    if (car.alive) {
      run_time = frame_end - start_time;
    }

    // update the window title every 100ms
    if (frame_end - title_timestamp >= 100) {
      renderer.UpdateWindowTitle(score, car.speed, run_time);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}


void Game::Update() {
  if (!car.alive) return;

  // update car position and speed, then move obstacles
  car.Update();
  Obstacle::Update(obstacles, car, score);

}

int Game::GetScore() const { return score; }
int Game::GetTime() const { return run_time/1000; }
