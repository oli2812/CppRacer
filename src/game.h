#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "car.h"
#include "obstacle.h"
#include <deque>


class Game {
 public:
  //public constructor for game instance
  Game(std::size_t grid_width, std::size_t grid_height);

  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  
  //getter methods for private variables
  int GetScore() const;
  int GetTime() const;
  

 private:
  Car car;
  std::deque<Obstacle> obstacles;
  int score{0};
  Uint32 run_time{0};

  void Update();
};

#endif