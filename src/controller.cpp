#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "car.h"

// interface towards car to update position and speed
void Controller::MoveCar(Car &car, Car::Direction input) const {
  car.direction = input;
  return;
}

//Inputhandler for user inputs up,down, left, right
void Controller::HandleInput(bool &running, Car &car) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          MoveCar(car, Car::Direction::kUp);
          break;

        case SDLK_DOWN:
          MoveCar(car, Car::Direction::kDown);
          break;

        case SDLK_LEFT:
          MoveCar(car, Car::Direction::kLeft);
          break;

        case SDLK_RIGHT:
          MoveCar(car, Car::Direction::kRight);
          break;
      }
    }
  }
}