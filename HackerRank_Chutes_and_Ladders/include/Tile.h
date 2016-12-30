#ifndef TILE_H
#define TILE_H
#include "Transporter.h"

/*
In the game of chutes and ladders, it is the goal of the player to reach the last tile (Tile 100) before all the other players.
Each tile could be a source or a destination of a chute or ladder. If it is a source then the player MUST either go down or up to the destinatation
tile the chute or ladder leads to. Usually the tile that the player moves to is determined by the roll of a six sided die. The player can only directly 
go forward by up to 1 to 6 tiles. 
*/
class Tile
{
    public:
        Tile(); //This is the default constructor called when creating an unitialized object such as an array of objects
        Tile& operator=(const Tile &tile); //Reassignment operator make two tiles equal in value but are different objects in that they have
                                        // different reference values
        Tile(int tileNum); //Alternate constructor "overloaded"
        void setTileNum(int tileNum);//way to give a tile that was initialized with the Tile() constructor a valid tile number
        ~Tile(); //deallocate any pointers used
        int getTileNum() const; 
        bool canPutTransporter() const; //Determine if a tile can be used as a source or destination for a chute or ladder
        // if it is a source or destination tile for any transporter object, it will always return false
        void insertTransport(int source , int dest, bool makeSource); //if the canPutTransporter() test passes, make this tile the source OR
                                                                // destination tile of a chute or ladder
        int getPotential() const; //When moving to a tile see, the tile it leads to if it is a chute or ladder source
    private:
        int transportTile;
        int origin; //Tile's number or place on the board
        bool isSource; // is The source tile of a transporter object (chute or ladder)
        bool isDest; // is the destination tile of a transporter object
        Transporter* tileTransporter; //Pointer to the transporter object the tile is a part of (if there is one to begin with), if there 
                                    // is no actual transporter object this private variable will be  nullptr
};

#endif // TILE_H
