#ifndef TILE_H
#define TILE_H
#include "Transporter.h"

class Tile
{
    public:
        Tile();
        Tile& operator=(const Tile &tile);
        Tile(int tileNum);
        void setTileNum(int tileNum);
        ~Tile();
        int getTileNum() const;
        bool canPutTransporter() const;
        void insertTransport(Transporter *transport, bool makeSource);
        int getPotential() const;
    private:
        int transportTile;
        int origin;
        bool isSource;
        bool isDest;
        Transporter* tileTransporter;
};

#endif // TILE_H
