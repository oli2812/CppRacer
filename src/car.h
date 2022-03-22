#ifndef CAR_H
#define CAR_H

#include <vector>
#include "SDL.h"

class Car {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight, kIdle };

  Car(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        start_x(5),
        start_y(grid_height / 2) {}

  void Update();

  Direction direction = Direction::kIdle;
  bool alive{true};

  
  std::vector<SDL_Rect> body;
  std::vector<SDL_Rect> spoilers;
  std::vector<SDL_Rect> tyres;
  SDL_Rect outline;

  float speed {0.0f};
  int start_x;
  int start_y;
  static int const car_length = 6;
  static int const car_width = 3;

  
 private:
  void UpdatePosition();

  int grid_width;
  int grid_height;

  int const upper_limit = 0;
  int const lower_limit = grid_height - car_width;
};

#endif