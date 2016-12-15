#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include "Tile.h"
#include <sstream>
#include <string>

class GameBoard
{
    public:
        GameBoard();
        ~GameBoard();
        Tile getTile(int coordinate) const;
        int startEstimation();
        void printBoard() const;
    private:
        int totalLadders;
        int totalChutes;
        Tile *gameTiles;
        void insertLadders();
        void insertChutes();
        int getBestMove(int currTile) const;
    public:
        void setTransporters(bool ladder);
        void runGame();
};

#endif // GAMEBOARD_H
