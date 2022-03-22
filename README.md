# Capstone Project: CppRacer

<img src="data/traffic_simulation.gif"/>

CppRacer is a sidescrolling racing simulation. The racing car must avoid all obstacles.
It can be controlled using the arrow keys:
* up/down: moving the car up or down in the lane
* right: accelerate
* left: brake

Each passed obstacle will score one point. On top of that time to complete the whole course or time until first crash will be measured.

New levels can easily be added by editing/exchanging level input file in res folder. (see below for syntax of level file)

## Basic Build Instructions

1. Make a build directory in the top level directory: `mkdir build && cd build`
2. Compile: `cmake .. && make`
3. Run it: `./CppRacer`.

## Level input file
Own level input files can be created as a simple csv file. Each line in this file represents one column of walls on the racetrack.
Syntax:
distance // type // option1 // option2 // [1..n] (start // height)
 
* distance: indicates distance to following/next obstacle
  * -1 to be used for last obstacle to indicate end of raceway
* type: different types of obstacles can be defined:
  * b: simple block or wall
  * h= horizontally moving - a wall which is moving towards the car
  * for future extensions more types could be defined, e.g.
    -vertically moving walls
    -temporary invisible walls
    -...
* option1 & option2:
  * optional values, depending on type. E.g. movement speed, time to be invisible etc.
  * can be set to 0 if not used
* 1..n pairs of start and height indicating the start block and the height (in blocks) for each obstacle
  * combining several walls in one column allows to create gates, grates, patterns etc.
      

## Project Tasks/Rubric

Following rubric points are fulfilled with this project:

- **The project demonstrates an understanding of C++ functions and control structures** : Loops and control structures are used in the project through most classes:
    * while: obstacle.cpp, Obstacle::Init(), 
    * for: obstacle.cpp, Obstacle::Update(), 
    * if: obstacle.cpp, Obstacle::Update(), 
   
- **The project reads data from a file** : level input file is read and parsed from file in res folder
    * obstacle.cpp, Obstacle::Init()

- **The project accepts user input** : arrow keys are used to control the car utilizing the SDL library
    * controller.cpp, Controller::HandleInput()
    * car.cpp, Car::UpdatePosition()

- **The project uses object oriented programming techniques** : function is splitted into different classes/files representing their respective tasks (car, obstacle,         game etc.). Variables and methods are declared and defined in these classes and their respective header files.

- **Classes use appropriate access specifiers for class members** : access specifiers for data and methods are correctly assigned in the respective header files, e.g.:
    * car.h
    * obstacle.h

- **Class constructors utilize member initialization lists** : initialization lists are used for constructors, e.g. in:
    * game.cpp, line 6
    * renderer.cpp, line 6

- **Classes encapsulate behavior** : classes grouped by tasks including specific variables and methods. Private variables can be accessed with get-methods, e.g. in:
    * game.cpp, Game::getScore() - line 72
    * game.cpp, Game::getTime() - line 73

- **The project makes use of references in function declarations** : several methods are using pass-by-reference arguments:
    * obstacles.cpp, Obstacle::Init(std::deque<Obstacle> &obstacles) - line 8
    * obstacles.cpp, Obstacle::Update(std::deque<Obstacle> &obstacles, Car &car, int &score) - line 53
    
