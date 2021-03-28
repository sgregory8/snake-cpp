#include "game.h"
#include <vector>
#include "point.h"
#include <ctime>
#include <cstdlib>

Game ::Game()
{
    // Init random seed
    srand(time(0));
    GameState initialState;

    // Assign the state
    this->state = initialState;
}
bool Game::update(Update update)
{
    switch (update)
    {
    case LEFT:
    {
        Point point(this->state.snakePosistions[0].x - 1, this->state.snakePosistions[0].y);
        this->state.snakePosistions.insert(this->state.snakePosistions.begin(), point);
        if (checkCollision())
        {
            if (!checkFood())
            {
                this->state.snakePosistions.pop_back();
            }
            return true;
        }
        else
        {
            return false;
        }
        break;
    }
    case RIGHT:
    {
        Point point(this->state.snakePosistions[0].x + 1, this->state.snakePosistions[0].y);
        this->state.snakePosistions.insert(this->state.snakePosistions.begin(), point);
        if (checkCollision())
        {
            if (!checkFood())
            {
                this->state.snakePosistions.pop_back();
            }
            return true;
        }
        else
        {
            return false;
        }
        break;
    }
    case UP:
    {
        Point point(this->state.snakePosistions[0].x, this->state.snakePosistions[0].y - 1);
        this->state.snakePosistions.insert(this->state.snakePosistions.begin(), point);
        if (checkCollision())
        {
            if (!checkFood())
            {
                this->state.snakePosistions.pop_back();
            }
            return true;
        }
        else
        {
            return false;
        }
        break;
    }
    case DOWN:
    {
        Point point(this->state.snakePosistions[0].x, this->state.snakePosistions[0].y + 1);
        this->state.snakePosistions.insert(this->state.snakePosistions.begin(), point);
        if (checkCollision())
        {
            if (!checkFood())
            {
                this->state.snakePosistions.pop_back();
            }
            return true;
        }
        else
        {
            return false;
        }
        break;
    }
    default:
        break;
        return true;
    }
    return true;
}

bool Game::checkCollision()
{
    // Get new head posistion
    int headX = this->state.snakePosistions[0].x;
    int headY = this->state.snakePosistions[0].y;

    // Check it's not inside snake
    for (int i = 1; i < this->state.snakePosistions.size(); i++)
    {
        if (
            this->state.snakePosistions[i].x == headX &&
            this->state.snakePosistions[i].y == headY)
            return false;
    }

    // Check boundary
    if (headX < 0)
        return false;
    if (headY < 0)
        return false;
    if (headX > 19)
        return false;
    if (headX > 19)
        return false;

    // We're good continue
    return true;
}

bool Game::checkFood()
{

    // Get new head posistion
    int headX = this->state.snakePosistions[0].x;
    int headY = this->state.snakePosistions[0].y;

    if (this->state.foodPoint.x == headX && this->state.foodPoint.y == headY)
    {
        this->state.score = this->state.score + 1;
        bool validPosition = false;
        int randX;
        int randY;
        while (!validPosition)
        {
            validPosition = true;
            randX = rand() % 19;
            randY = rand() % 19;

            for (int i = 0; i < this->state.snakePosistions.size(); i++)
            {
                if (this->state.snakePosistions[i].x == randX && this->state.snakePosistions[i].y)
                {
                    validPosition = false;
                    break;
                }
            }
        }
        this->state.foodPoint = Point(randX, randY);
        return true;
    }
    return false;
}