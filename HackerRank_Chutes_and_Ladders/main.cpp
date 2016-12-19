#include <iostream>
#include <string>
#include "GameBoard.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl; //Default code with codeblocks can obviously omit
    GameBoard gBoard = GameBoard(); //Create a gameboard
    gBoard.runGame(); //Run the game and determine the minimum number of dice rolls for a certain combination of chutes and ladders
    return 0;
}
