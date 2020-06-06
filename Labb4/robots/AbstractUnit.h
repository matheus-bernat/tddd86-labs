/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef UNIT_H
#define UNIT_H

#include "utilities.h"

/* Root class for all pieces on the board.
 * Subclasses are Robot and Hero (Junk is a subclass of Robot now).
 */
class AbstractUnit {
public:
    AbstractUnit();
    AbstractUnit(const AbstractUnit& u);
    AbstractUnit(const Point& p);

    /*
    * Return Point representation of Unit
    */
    Point asPoint() const;

    /*
    * Am I in the same square as u?
    */
    bool at(const AbstractUnit& u) const;

    /*
    * Can I catch u in one move?
    */
    virtual bool attacks(const AbstractUnit& u) const;

    /*
    * Take one step closer to u
    */
    virtual void moveTowards(const AbstractUnit& u);

    /*
     * Draw unit
     */
    virtual void draw() = 0;

    /*
    * Teleport. Does not check for collision
    */
    void teleport();

    /*
    * Euclidean distance to u
    */
    double distanceTo(const AbstractUnit& u) const;
private:
    int x;  // x position of this unit
    int y;  // y position of this unit

    // private helpers
    void checkBounds();
};

#endif // UNIT_H
