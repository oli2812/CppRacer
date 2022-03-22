#include "obstacle.h"
#include <iostream>
#include <fstream>
#include <deque>
#include <regex>


void Obstacle::Init(std::deque<Obstacle> &obstacles) {
  std::string line;
  std::string distance;
  std::string type;
  std::string option1;
  std::string option2;
  std::string pos;
  std::string height;

  //TODO check ob distance benötigt
  Obstacle o(0);
  SDL_Rect r;

  
  
  std::ifstream filestream("../res/level1");
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ';', ' ');
      std::istringstream linestream(line);
      linestream >> distance >> type >> option1 >> option2 ;
      
      o.distance = std::stoi(distance);
      o.type = type;
      o.option1 = std::stoi(option1);
      o.option2 = std::stoi(option2);
      o.walls.clear();

      while (linestream >> pos >> height) {
        
        r.x = 127;
        r.y = std::stoi(pos);
        r.w = 1;
        r.h = std::stoi(height);
  
        o.walls.emplace_back(r);
      }
      obstacles.emplace_back(o);

    }
  }

}


void Obstacle::Update(std::deque<Obstacle> &obstacles, Car &car, int &score) {
    
    //at least first element always needs to be visible
    if (!obstacles[0].visible) {
      obstacles[0].visible = true;
    }

    for (int i = 0; i < obstacles.size(); i++) {
      // only items visible in the screen need to be updated
      if (obstacles[i].visible) {
        int previous_column = static_cast<int>(obstacles[i].start_x);  // store x position in grid before updating
        obstacles[i].UpdatePosition(car.speed);                   // apply speed to obstacle
        int current_column = static_cast<int>(obstacles[i].start_x);   // capture x position in grid after updating

      

        // Update obstacle only if moved to new grid column
        if (current_column != previous_column) {
          if (current_column == 0) {
            // remove obstacle as it has left the screen
            obstacles.pop_front();
            score++;
          }
          else {
            obstacles[i].UpdateObstacle(current_column);
            //check for collision with car
            for (SDL_Rect &wall : obstacles[i].walls) { 
              if (SDL_HasIntersection(&car.outline, &wall)) {
                car.alive = false;
              }
            }
          }
          // check if last item of deque to avoid index out of bounds
          if ((i+1) < obstacles.size()) {
            //current item holds distance in front of new obstacle
            //only to be checked if next item is not already visible
            if (!obstacles[i+1].visible) {
              obstacles[i].distance -= 1;
            }
          }
        }
        // check if next obstacle needs to be added 
        if (obstacles[i].distance == 0  && (i+1) < obstacles.size()) {
          obstacles[i+1].visible = true;
        }
      }
    }  
}

// calculate new position of obstacle
// moved into separate method to account for different type of obstacles
// (moving, invisible,...)
void Obstacle::UpdatePosition(float speed) {

  if (this->type == "h") {
      //horizontally moving
      this->start_x -= (this->option1 * speed);
  }

  else if (this->type == "b") {
      //static block
      this->start_x -= speed;
  }

}

//each obstacle can consist of several walls -> all need to be moved
// currently only horizontal movement, also vertical movement would be possible (moving gate etc.)
void Obstacle::UpdateObstacle(int column) {
  for (SDL_Rect &wall : this->walls) {
    wall.x = column;
  }

  
}

