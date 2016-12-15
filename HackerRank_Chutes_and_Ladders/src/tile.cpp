#include "Tile.h"

Tile::Tile()
{
    isSource = isDest = false;
    origin = 0;
    tileTransporter = nullptr;
    transportTile = 0;
}
Tile& Tile::operator=(const Tile &tile)
{
    if(this != &tile)
    {
        isSource = tile.isSource;
        isDest = tile.isDest;
        origin = tile.origin;
        transportTile = tile.transportTile;
        if(tile.tileTransporter != nullptr)
            tileTransporter = new Transporter(tile.tileTransporter->getSource(), tile.tileTransporter->getDest());
        else
            tileTransporter = nullptr;
    }
    return *this;
}

Tile::Tile(int tileNum)
{
    isSource = isDest = false;
    origin = tileNum;
    transportTile = 0;
    tileTransporter = nullptr;
}

void Tile::setTileNum(int tileNum)
{
    if(origin == 0)
        origin = tileNum;
}

int Tile::getTileNum() const
{
    return origin;
}
bool Tile::canPutTransporter() const
{
    if(isSource || isDest)
        return false;
    return true;
}

void Tile::insertTransport(Transporter *transport, bool makeSource)
{
    if(tileTransporter != nullptr)
    {
        throw GameBoardException();
        delete transport;
    }
    if(makeSource)
        isSource = true;
    else if(makeSource == false)
        isDest = true;
    tileTransporter = transport;
}
int Tile::getPotential() const
{
    if(isDest || tileTransporter == nullptr)
        return origin;
    return tileTransporter->getDest();
}
Tile::~Tile()
{
    delete tileTransporter;
}
