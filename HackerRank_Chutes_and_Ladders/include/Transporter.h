#ifndef TRANSPORTER_H
#define TRANSPORTER_H
#include "GameBoardException.h"

/*
Transporter objects are the actual chutes and ladders classes of the game. These are very simple objects with only methods being get and set 
, looking back this could have been just a struct for the purpose of just this hackerRank problem. Obviously not every tile contains a
chute or ladder so in this case instead we use Transporter pointers and denote the lack of a chute or ladder on a tile (meaning it is
not a source or destination tile for a chute or ladder) with a nullptr
*/
class Transporter
{
    public:
        Transporter(int start, int dest);
        int compute() const;
        int getSource() const;
        int getDest() const;
    private:
        int source;
        int destination;
        int result;
};

#endif // TRANSPORTER_H
