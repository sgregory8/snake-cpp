#include <ncurses.h>
#include <iostream>
#include "game.h"
#include <unistd.h>

void drawGame(GameState *state)
{
    // Construct the board
    char gameBoard[22][23];
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            if (i == 0 || i == 21)
            {
                gameBoard[i][j] = '-';
            }
            else if (j == 0 || j == 21)
            {
                gameBoard[i][j] = '|';
            }
            else
            {
                gameBoard[i][j] = ' ';
            }
            // Null terminate the String for ncurses to work properly
            if (j == 22)
            {
                gameBoard[i][j] = '\0';
            }
        }
    }

    // Populate the food
    gameBoard[state->foodPoint.y + 1][state->foodPoint.x + 1] = 'F';

    // Populate the snake
    for (int i = 0; i < state->snakePosistions.size(); i++)
    {
        if (i == 0)
        {
            // Draw the head
            gameBoard[state->snakePosistions[i].y + 1][state->snakePosistions[i].x + 1] = 'H';
        }
        else
        {
            // Draw the body
            gameBoard[state->snakePosistions[i].y + 1][state->snakePosistions[i].x + 1] = 'o';
        }
    }

    // Get the border row
    char(*border)[23] = &gameBoard[0];

    // Print the top boundary
    mvprintw(0, 0, *border);

    // Print the board
    for (int k = 0; k < 20; k++)
    {
        mvprintw(k + 1, 0, gameBoard[k + 1]);
    }

    // Print the bottom boundary
    mvprintw(21, 0, *border);

    // Print the score
    std::string buf("score: ");
    buf.append(std::to_string(state->score));
    mvprintw(22, 0, &buf[0]);
}

int main()
{
    // Create the game objects
    Game game;

    WINDOW *w = initscr();
    cbreak();
    nodelay(w, true);
    keypad(w, true);
    drawGame(&game.state);

    Update lastDirection = LEFT;
    int input = getch();
    bool gameActive = true;
    while (gameActive)
    {
        input = getch();
        if (input == KEY_LEFT)
        {
            gameActive = game.update(LEFT);
            lastDirection = LEFT;
        }
        if (input == KEY_UP)
        {
            gameActive = game.update(UP);
            lastDirection = UP;
        }
        if (input == KEY_RIGHT)
        {
            gameActive = game.update(RIGHT);
            lastDirection = RIGHT;
        }
        if (input == KEY_DOWN)
        {
            gameActive = game.update(DOWN);
            lastDirection = DOWN;
        }
        else
        {
            gameActive = game.update(lastDirection);
        }
        drawGame(&game.state);
        refresh();
        usleep(200000);
    }
    endwin();
    return 0;
}