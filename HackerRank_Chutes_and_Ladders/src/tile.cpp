#include "Tile.h"

Tile::Tile()
{
    isSource = isDest = false; //All tiles, on default, will have no transporters a part of them or associated with them
    // This means they start as not being either source or destination tiles
    origin = 0;//By default, tile's tilenumber starts at 0, an invalid number in the context of the game, but these get set upon initialization
    //of the full game
    tileTransporter = nullptr; //By default all tiles have no transporter (no chute or ladder attached to them) so this is initialized as a nullptr
    transportTile = 0;
}
Tile& Tile::operator=(const Tile &tile)//One of the BIG 3 assignment operator overloader
{
    if(this != &tile) //No need to do additional processing if they are the same object, just return it
    {
        isSource = tile.isSource; //Replace the source, destination, and tile number fields with the values of those in the right operand
        isDest = tile.isDest; //Since the is an assignment operator overload, just like a constructor overload ( Tile(const &Tile)) private 
                                // members can be referenced directly
        origin = tile.origin;
        transportTile = tile.transportTile; //NOTE this field ended up not being needed in the final program so you can delete this in yours
        if(tile.tileTransporter != nullptr) //If right operand has an actual transporter object make a new transporter object whose field values 
            // are copies of the field values of the right Tile's transporter (in this case the left Tile in {i.e. Tile a = Tile b} would be the *this object
            // where the right operand is the Tile whose values are being COPIED into the field's of the left tile or the *this object)
            tileTransporter = new Transporter(tile.tileTransporter->getSource(), tile.tileTransporter->getDest());
            //Also to be safe I should have deleted any contents that the left Tile tileTransporter had before reassignment to be safe
        else
            tileTransporter = nullptr;
            // If no transporter object in right operand, reset left tile's tileTransporter to null
    }
    return *this;
}
//This constructor below ended up not being needed in the final program so you can disregard it, I opted to use the setTileNum method instead
Tile::Tile(int tileNum) //Same as Tile() but here user can set the tileNum 
{
    isSource = isDest = false;
    origin = tileNum;
    transportTile = 0;
    tileTransporter = nullptr;
}

void Tile::setTileNum(int tileNum)
{
    if(origin == 0) //If the Tile's origin field is invalid (a tile cannot have a value of 0) then set the Tile'so origin field to tileNum
        origin = tileNum; //For the most part a general setter method
}

int Tile::getTileNum() const //Generic getter method, ended up not being used in the final program so no need to write this method
{
    return origin;
}
bool Tile::canPutTransporter() const //Determine if a Tile has a chute or ladder attached to it, used for testing in outside scope program
{
    if(isSource || isDest) //If it is a source or destination tile, it is not available to have any additonal chutes or ladders attached to it
        return false;
    return true; //If this is not the case, then it is available
}

void Tile::insertTransport(Transporter *transport, bool makeSource)
{
    if(tileTransporter != nullptr) //If for some reason the Tile already has a chute or ladder attached to it raise Exception
                                // and delete the parameter transport object pointer since it is not valid in this context
    {
        throw GameBoardException();
        delete transport;
    }
    if(makeSource) 
        isSource = true; //Make this tile the source tile of the chute or ladder
    else if(makeSource == false) //Make this tile the destination tile of the chute or ladder
        isDest = true;
    tileTransporter = transport; //Make this tile associated with the transport pointer
}
int Tile::getPotential() const //Where the game logic actually comes into play
/*
When you play chutes and ladders you roll a dice which will give you a number in the range (1-6)
Whatever that number you get from your roll you move that number of tiles from your  current position
(i.e. you're at tile 53 and roll a 3 you, you must progress 3 tiles forward to tile 56)
If that tile has no chute or ladder attached to it, you are done, and either roll again or give your turn to the next player
If that tile is a SOURCE of chute or ladder you must progress to whatever tile it takes you.
If the 56 tile was a source of a ladder whose destination is 83 then the player will move all the way to 83, then progress from there
If the 56 tile was a source of a chute whose destination is 32 then the player will go down to 32, the progress from there.
Also note, if that 56 tile was a DESTINATION tile for a chute or a ladder, the player does not move, the player must stay there as if
there was no chute or ladder there at all, and progress from there into another roll by that player or another player 
*/
{
    if(isDest || tileTransporter == nullptr) //If the tile has no chute or ladder associated with it, or is a destination tile just return
        // the tile's origin or tile number
        return origin;
    return tileTransporter->getDest(); //If it is a source tile for a chute or ladder return the destination tile or tileNumber that the Transporter
    //object associated with it returns
}
Tile::~Tile()
{
    delete tileTransporter; //Was the only dynamically allocated field in the class so, it is the only one that needs to be explicitly deleted
}
