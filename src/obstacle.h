#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <deque>
#include <vector>
#include <string>
#include "SDL.h"
#include "car.h"

class Obstacle {
 public:

  Obstacle(int dist)
      : distance(dist) {}

  void static Update(std::deque<Obstacle> &obstacles, Car &car, int &score);
  void static Init(std::deque<Obstacle> &obstacles);

  
  std::vector<SDL_Rect> walls;

  float start_x = 127.0;
  float start_y = 0.0;
  int distance = 0;
  std::string type;
  int option1 = 0;
  int option2 = 0;
  bool visible = false;

  
 private:
  void UpdatePosition(float speed);
  void UpdateObstacle(int column);

};

#endif