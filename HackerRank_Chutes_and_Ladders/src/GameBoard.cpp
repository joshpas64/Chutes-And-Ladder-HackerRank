#include "GameBoard.h"
#include <iostream>
GameBoard::GameBoard()
{
    totalLadders = 0;
    totalChutes = 0;
    gameTiles = new Tile[100];
    for(int i = 0; i < 100; i++)
    {
        gameTiles[i].setTileNum(i + 1);
    }
}

void GameBoard::insertLadders()
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
                stream >> source;
                stream >> dest;
                stream.clear();
                stream.str("");
                if(dest - source <= 1 || dest <= 0 || source <= 0 || source > 100 || dest > 100)
                {
                    std::cout << "Sorry that was invalid input, please try again..." << std::endl;
                    continue;
                }
                if(!(gameTiles + source - 1)->canPutTransporter() || !(gameTiles + dest - 1)->canPutTransporter())
                {
                    std::cout << "Sorry you can put a ladder there, that tile is taken, try again ..." << std::endl;
                    continue;
                }
                Transporter *currentLadder = new Transporter(source,dest);
                (gameTiles + source - 1)->insertTransport(currentLadder,true);
                (gameTiles + dest - 1)->insertTransport(currentLadder,false);
                break;
            }
            catch(GameBoardException &gE)
            {
                std::cout << "Sorry that was invalid tile please try again" << std::endl;
                continue;
            }
            catch(...)
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
            {
                std::cout << "Sorry those tiles do not exist in this type of board, try again ..." << std::endl;
                continue;
            }
            if(!(gameTiles + source - 1)->canPutTransporter() || !(gameTiles + dest - 1)->canPutTransporter())
            {
                std::cout << "Sorry those tiles are already marked, try again..." << std::endl;
                continue;
            }
            Transporter *currentLadder = new Transporter(source,dest);
            (gameTiles + source - 1)->insertTransport(currentLadder,true);
            (gameTiles + dest - 1)->insertTransport(currentLadder,false);
            break;
        }
        catch(GameBoardException &gE)
        {
            std::cout << "Sorry that was invalid tile placement, try again ...." << std::endl;
            continue;
        }
        catch(...)
        {
            std::cout << "Sorry something is wrong with those entries try again please" << std::endl;
            continue;
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
    inpts = "";
    if(ladderCount <= 0 || ladderCount > 15)
        throw;
    if(ladder)
    {
        totalLadders = ladderCount;
        for(int i = 0; i < ladderCount; i++)
            insertLadders();
    }
    else
    {
        totalChutes = ladderCount;
        for(int i = 0; i < ladderCount; i++)
            insertChutes();
    }
}

Tile GameBoard::getTile(int coordinate) const
{
    return gameTiles[coordinate - 1];
}

void GameBoard::printBoard() const
{
    for(int i = 0; i < 100; i++)
    {
        std::cout << "Tile: " << (gameTiles + i)->getTileNum() << " " << (gameTiles + i)->canPutTransporter() << " " << (gameTiles + i)->getPotential() << std::endl;
    }
}
int GameBoard::startEstimation()
{
    int currentTile = 1;
    int newTile = currentTile;
    int diceRolls = 0;
    while(newTile < 100)
    {
        newTile = getBestMove(currentTile);
        currentTile = newTile;
        diceRolls++;
    }
    return diceRolls;
}

int GameBoard::getBestMove(int currTile) const
{
    int bestTile = 0;
    int temp = 0;
    for(int i = 1; i < 7; i++)
    {
        if(currTile + i == 100)
        {
            return 100;
        }
        temp = (gameTiles + i + currTile - 1 )->getPotential();
        if(temp > bestTile)
        {
            bestTile = temp;
        }
    }
    return bestTile;
}
void GameBoard::runGame()
{
    setTransporters(true);
    setTransporters(false);
    //printBoard();
    int result = startEstimation();
    std::cout << "There were a total of " << result << " dice rolls!" << std::endl;
    return;
}
GameBoard::~GameBoard()
{
    delete gameTiles;
}
