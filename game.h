#pragma once
#include <vector>
#include "point.h"

enum Update
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    PAUSE
};

struct GameState
{
    GameState() : foodPoint(4, 3)
    {
        std::vector<Point> intialSnakePositions;
        intialSnakePositions.push_back(Point(8, 10));
        intialSnakePositions.push_back(Point(9, 10));
        intialSnakePositions.push_back(Point(10, 10));
        this->snakePosistions = intialSnakePositions;
        this->score = 0;
    }
    std::vector<Point> snakePosistions;
    Point foodPoint;
    int score;
};

class Game
{
public:
    Game();
    GameState state;
    bool update(Update update);
    void start();
private:
    bool checkCollision();
    bool checkFood();
};