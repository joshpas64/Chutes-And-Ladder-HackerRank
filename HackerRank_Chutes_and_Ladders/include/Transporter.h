#ifndef TRANSPORTER_H
#define TRANSPORTER_H
#include "GameBoardException.h"

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
