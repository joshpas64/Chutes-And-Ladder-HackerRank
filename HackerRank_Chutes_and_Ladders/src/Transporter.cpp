#include "Transporter.h"
/*

Once again the premise of the transporter is fairly simple, when the player uses a transporter object it can extract its source, the tile it 
starts on, its destination, the tile it leads, or its result, the amount of tiles skipped up or down from the board

*/
// In the context of this program it is user console input that is setting the fields of the transporter 
Transporter::Transporter(int start, int dest)
{
    source = start;
    destination = dest;
    //Transporter can take you to tile 1(the start) or straight to the end (100) anything outside the range 2-99 is also invalid
    if(source <= 1 || destination <= 1 || source >= 100 || destination >= 100)
    {
        throw GameBoardException(); //Throw exception and retake input or go into error handling if given an invalid tile number
    }
    result = destination - source;
    if(result >= -1 && result <= 1) //Source and destination tiles have to be a minimum of 2 tiles apart, if they are not, throw an Exception
        //and later outer scrope program handle it
    {
        throw GameBoardException();
    }
}
//simple getter methods, fairly self-explanatory
int Transporter::getSource() const
{
    return source;
}

int Transporter::getDest() const
{
    return destination;
}
int Transporter::compute() const
{
    return result;
}
