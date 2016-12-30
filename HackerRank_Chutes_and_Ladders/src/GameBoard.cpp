#include "GameBoard.h"
#include <iostream>
//Default constructor
GameBoard::GameBoard()
{
    totalLadders = 0;
    totalChutes = 0; //By default the gameboard will have 0 chutes and 0 ladders until it takes user input to set and constructor them
    gameTiles = new Tile[100]; //A chutes and ladders game usually has 100 tiles, so in this case the gameboard will have a dynamically allocated
                                // array of 100 tiles
    /**/
    for(int i = 0; i < 100; i++)
    {
        gameTiles[i].setTileNum(i + 1); //All tiles can be assigned there a tile Number ranging from 1 - 100
        //This statements sets all those tile Numbers accordingly
    }
}

void GameBoard::insertLadders()
{
        while(true) //This is for exception handling, if any errors are caught, go back and retake input until the input is valid
        {
            try
            {
                int source, dest;
                std::stringstream stream;
                std::string inpts;
                std::getline(std::cin, inpts);
                stream << inpts;
                stream >> source;
                stream >> dest;
                stream.clear();
                stream.str(""); //Take two space separated numbers and parse them into the integer variables source and dest
                                //Also note, since these are ladders (dest - source) must > 1
                                // and clear the stringstream buffers right after
                if(dest - source <= 1 || dest <= 0 || source <= 0 || source > 100 || dest > 100) //Invalid tile range
                {
                    std::cout << "Sorry that was invalid input, please try again..." << std::endl; //Error message
                    continue; //Move to another while iteration, taking new input
                }
                if(!(gameTiles + source - 1)->canPutTransporter() || !(gameTiles + dest - 1)->canPutTransporter())
                {
                    //If the tiles already have chutes or ladders associated with them, they are not valid
                    std::cout << "Sorry you can put a ladder there, that tile is taken, try again ..." << std::endl;//Output error message
                    continue; //Skip this iteration and move to next iteration of while loop
                }
                                                                                        // and destination tiles
                (gameTiles + source - 1)->insertTransport(source, dest,true); //Make source tile associated with the chute or ladder marked as the
                                                                                                //source tile of that transporter
                (gameTiles + dest - 1)->insertTransport(source, dest,false); // Make the destination associated with the chute or ladder marked as the destination tile 
                                                                                                //of that transporter
                break; //Once all input is valid and verified break out of loop and exit method
            }
            catch(GameBoardException &gE) //If the insertTransport constructor raises an exception during construction catch it
                                            // and retake the input by moving to the next iteration of the while loop
            {
                std::cout << "Sorry that was invalid tile please try again" << std::endl; //Output Error Message
                continue;
            }
            catch(...) //Catch and handle any other exception by outputting error message and retaking input
            {
                std::cout << "Sorry something is wrong with your input try again please..." << std::endl;
                continue;
            }
        }
}

void GameBoard::insertChutes()
{
    while(true)
    {
        try
        {
            int source, dest;
            std::stringstream stream;
            std::string inpts;
            std::getline(std::cin, inpts);
            stream << inpts;
            stream >> source >> dest;
            stream.clear();
            stream.str("");
            if(dest - source >= -1 || dest <= 0 || source <= 0 || source > 100 || dest > 100)
            //Take two space separated numbers and parse them into the integer variables source and dest
            // Also note since these are chutes, that dest - source must be < -1
                                // and clear the stringstream buffers right after
            {
                std::cout << "Sorry those tiles do not exist in this type of board, try again ..." << std::endl; // Output Error Message
                continue; //Skip remaining code, and move to next iteration of while loop
            }
            if(!(gameTiles + source - 1)->canPutTransporter() || !(gameTiles + dest - 1)->canPutTransporter())
            {
                //If the tiles already have chutes or ladders associated with them, they are not valid
                std::cout << "Sorry those tiles are already marked, try again..." << std::endl; // Output Error Message
                continue; //Skip remaining code, and move to next iteration of while loop
            }
            Transporter *currentLadder = new Transporter(source,dest);//Make a new transporter object ptr with the corresponding source
                                                                        // and destination tiles
            (gameTiles + source - 1)->insertTransport(currentLadder,true);//Make source tile associated with the chute or ladder marked as the
                                                                                                //source tile of that transporter
            (gameTiles + dest - 1)->insertTransport(currentLadder,false);//Make destination tile associated with the chute or ladder marked as the
                                                                                                //destination tile of that transporter
            break; //Once all input is valid and verified exit and return from this method
        }
        catch(GameBoardException &gE)
        {
            std::cout << "Sorry that was invalid tile placement, try again ...." << std::endl; // Output Error Message
            continue; //Skip remaining code, and move to next iteration of while loop
        }
        catch(...)
        {
            std::cout << "Sorry something is wrong with those entries try again please" << std::endl; // Output Error Message
            continue; //Skip remaining code, and move to next iteration of while loop
        }
    }
}

void GameBoard::setTransporters(bool ladder)
{
    std::stringstream stream;
    std::string inpts;
    int ladderCount;
    std::getline(std::cin,inpts);
    stream << inpts;
    stream >> ladderCount;
    stream.clear();
    stream.str("");
    inpts = ""; //Take a single number from the command line and parse it into the integer variable ladderCount (ladderCount basically denotese the
                                                                                                         //amount of chutes or ladders in the 
    if(ladderCount <= 0 || ladderCount > 15) // The valid range is [1,15] if not in this range, throw exception
        throw;
    if(ladder) //if ladder == true then do insertladders() creating ladder objects
    {
        totalLadders = ladderCount;
        for(int i = 0; i < ladderCount; i++)
            insertLadders();
    }
    else //if ladder == false then execute insertChutes() creating chutes objects
    {
        totalChutes = ladderCount;
        for(int i = 0; i < ladderCount; i++)
            insertChutes();
    }
}

Tile GameBoard::getTile(int coordinate) const //Simple getter method was not used or needed in main program can omit if you'd like
{
    return gameTiles[coordinate - 1];
}

void GameBoard::printBoard() const //Was for testing and debugging, can omit from final program 
{
    for(int i = 0; i < 100; i++)
    {
        std::cout << "Tile: " << (gameTiles + i)->getTileNum() << " " << (gameTiles + i)->canPutTransporter() << " " << (gameTiles + i)->getPotential() << std::endl;
    }
}
int GameBoard::startEstimation() //Essentially a run-through of the hacker-rank problem
{
    int currentTile = 1; //Like always player starts at tile 1
    int newTile = currentTile; //Copy of currentTile to have a backup for the sake of keeping track
    int diceRolls = 0; //Number of moves so far
    while(newTile < 100) //Goal is to get to 100, or in other words make currentTile == 100
    {
        newTile = getBestMove(currentTile); //Find the best (highest tile or 100) tile you can get from one of the six dice roll outcomes
        currentTile = newTile; // make that tile the current tile
        diceRolls++; //increment until terminating condition is reached
    }
    return diceRolls;
}

int GameBoard::getBestMove(int currTile) const
{
    int bestTile = 0; //Best tile that can be moved to
    int temp = 0; //Current tile option givem
    for(int i = 1; i < 7; i++)
    {
        if(currTile + i == 100) //If goal is reached (get to 100)
        {
            return 100; // return 100 so outside program can terminate as well
        }
        temp = (gameTiles + i + currTile - 1 )->getPotential(); //for the current tile being tested get its "potential", meaning
                                    // if it is a destination or has no transporter the tileNum itself is the transport
                                    // if it is a source, return the transporter's corresponding destination tileNumber as the "potential"
        if(temp > bestTile) //compare to the current bestTile option
        {
            bestTile = temp;//If the current temp value is bigger, replace bestTile with temp's value
        }
    }
    return bestTile;
}
void GameBoard::runGame() //Full run through including the user input step all combined into one method
{
    setTransporters(true); //Set ladders of the board
    setTransporters(false); // Set chutes of the board
    //printBoard();
    int result = startEstimation(); //Find the minimum rolls needed to get to 100, basically getting really lucky
    std::cout << "There were a total of " << result << " dice rolls!" << std::endl; //Output number of dice rolls
    return;
}
GameBoard::~GameBoard()
{
    delete[] gameTiles; //deallocate gameTiles array
}
