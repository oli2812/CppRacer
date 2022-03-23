#ifndef CAR_H
#define CAR_H

#include <vector>
#include "SDL.h"

class Car {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight, kIdle };

  //pblic constructor, also initializing start position of car
  Car(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        start_x(5),
        start_y(grid_height / 2) {}

  void Update();

  Direction direction = Direction::kIdle;

  // alive remains true as long as car has not crashed
  bool alive{true};

  // car is defined as SDL rectangle
  SDL_Rect outline;
  static int const car_length = 6;
  static int const car_width = 3;

  float speed {0.0f};
  int start_x;
  int start_y;
  
 private:
  //private method calculating new car position and speed
  void UpdatePosition();

  int grid_width;
  int grid_height;

  // upper and lower limit of screen=racetrack for input check
  int const upper_limit = 0;
  int const lower_limit = grid_height - car_width;
};

#endif