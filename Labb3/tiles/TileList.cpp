// Labb 3A, Tiles - Matheus Bernat (matvi959) & Caspian Süsskind (cassu286)

/*
 * The functions below define the methods declared in the class header TileList.h.
 * They define what shall happen when the user gives a certain mouse input, such as
 * moving an element to the top, removing elements, etc.
 */

#include "TileList.h"
#include <array>

TileList::TileList()
{
    size = 0;
    capacity = 10;
    tiles = new Tile[capacity]();
}

TileList::~TileList()
{
    delete[] tiles;
}

void TileList::addTile(Tile tile)
{
    if(size != capacity) {
        tiles[size] = tile;
        size++;
    } else {
        capacity = 2*capacity;
        Tile* increasedTiles = new Tile[capacity];
        copy(tiles, tiles + size, increasedTiles);
        delete [] tiles;
        tiles = increasedTiles;
    }
}

void TileList::drawAll(QGraphicsScene* scene)
{
    for(int i = 0; i < size; i++) {
        tiles[i].draw(scene);
    }
}

int TileList::indexOfTopTile(int x, int y)
{
    int index = -1;
    for(int i = 0; i < size; i++) {
        if(tiles[i].contains(x, y)) {
            index = i;
        }
    }
    return index;
}

void TileList::raise(int x, int y)
{
    int topTileIndex = indexOfTopTile(x, y);
    Tile topTile = tiles[topTileIndex];
    shiftLeft(topTileIndex);
    size--;
    addTile(topTile);
}

void TileList::lower(int x, int y)
{
    int topTileIndex = indexOfTopTile(x, y);
    Tile topTile = tiles[topTileIndex];
    for(int i = topTileIndex; i > 0; i--) {
        tiles[i] = tiles[i - 1];
    }
    tiles[0] = topTile;
}

void TileList::remove(int x, int y)
{
    shiftLeft(indexOfTopTile(x, y));
    size--;
}

void TileList::removeAll(int x, int y)
{
    int count = 0;
    for(int i = 0; i < size; i++) {
        if(tiles[i].contains(x, y)) {
            count++;
        }
    }
    for(int j = 0; j < count; j++) {
        remove(x, y);
    }
}

void TileList::shiftLeft(int topTileIndex) {
    for(int i = (topTileIndex + 1); i < size; i++) {
        tiles[i - 1] = tiles[i];
    }
}
