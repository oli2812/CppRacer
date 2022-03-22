#include "car.h"
#include <iostream>

void Car::Update() {

  UpdatePosition();

}

void Car::UpdatePosition() {
  switch (direction) {
    case Direction::kUp:
      if (start_y > upper_limit) {
        start_y = start_y - 1;
      }
      break;

    case Direction::kDown:
      if (start_y < lower_limit) {
        start_y = start_y + 1;
      }
      break;

    case Direction::kLeft:
      if (speed > 0.005) {
        speed = speed - 0.02;
      }
      break;

    case Direction::kRight:
      speed = speed + 0.02;
      break;
  }
  direction = Car::Direction::kIdle;

  outline.x = start_x;
  outline.y = start_y;
  outline.w = car_length;
  outline.h = car_width;

  
}