#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include "Tile.h"
#include <sstream>
#include <string>

//Actual Gameboard object that the user plays on and has all the tiles and transporter objects associated with them
// In the hacker rank problem the source and destination tiles of all the chutes and ladder are all determined by user input 
// from a command line, console-like interface
// So to solve the problem,
/// First the board must be FULLY initialized which includes taking the user's input
// Then the game must be run with this fully setup and custom gameboard
// Goal is to find minimum number of times to get to Tile 100

class GameBoard
{
    public:
        GameBoard(); //Only these two, empty constructor and destructor are needed for this class
        ~GameBoard();
        Tile getTile(int coordinate) const; //Simple get method never needed in final program
        int startEstimation(); //Find minimum number of rolls
        void printBoard() const; //Was for testing and debugging, not needed in final program
    private:
        int totalLadders; //Number of ladders on the board (valid range : [1,15])
        int totalChutes; // Number of chutes on the board (valid range: [1,15])
        Tile *gameTiles; // Tiles of the game board, in total there are 100
        void insertLadders(); // Take user input to initialize all ladders in the gameboard
        void insertChutes(); // Take user input to initialize all chutes in the gameboard
        //Ladders and Chutes are both the same class which is Transporter
        int getBestMove(int currTile) const; //Find best tile to move forward to when making a dice roll
    public:
        void setTransporters(bool ladder);//Find best tile to move forward to when making a dice roll
        void runGame(); //Run the full game as laid out in the HackerRank example, initialize the game tiles,
                        // use user input to set the chutes and ladders of the board and "run a simulation game" to find
                        // the minimum number of moves to get to Tile 100
};

#endif // GAMEBOARD_H
