#include "Transporter.h"

Transporter::Transporter(int start, int dest)
{
    source = start;
    destination = dest;
    if(source <= 1 || destination <= 1 || source >= 100 || destination >= 100)
    {
        throw GameBoardException();
    }
    result = destination - source;
    if(result >= -1 && result <= 1)
    {
        throw GameBoardException();
    }
}
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
