// Labb 3A, Tiles - Matheus Bernat (matvi959) & Caspian Süsskind (cassu286)

/*
 * The functions below declare the methods in the class TileList.
 * They define what shall happen when the user gives a certain mouse input, such as
 * moving an element to the top, removing elements, etc.
 */

#ifndef TILELIST_H
#define TILELIST_H

#include <QGraphicsScene>
#include "Tile.h"

class TileList {
public:
    /* Class default constructor. */
    TileList();

    /* Class destructor. */
    ~TileList();
    /* Adds a Tile-object to the array at the first available spot. */
    void addTile(Tile tile);

    /* Draws all the Tile-objects in the array. */
    void drawAll(QGraphicsScene* scene);

    /* Returns the index of the Tile-object that lies on the top of the given coordinates. */
    int indexOfTopTile(int x, int y);

    /* Moves the object at the top of the given coordinates, to the bottom of the array. */
    void lower(int x, int y);

    /* Moves the object at the top of the given coordinates, to the top of the array. */
    void raise(int x, int y);

    /* Removes the element that lies on the top of the given coordinates. */
    void remove(int x, int y);

    /* Removes all of the Tile-objects that cover the given coordinates. */
    void removeAll(int x, int y);

private:
    /* Shifts all the Tile-objects one step to the left, starting from the object with index "topTileIndex. */
    void shiftLeft(int topTileIndex);
    Tile* tiles;
    int size;
    int capacity;

};

#endif // TILELIST_H
