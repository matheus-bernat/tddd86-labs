/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Unit.h"
#include "constants.h"
#include "utilities.h"
#include <cstdlib>
#include <cmath>

AbstractUnit::AbstractUnit() {
    teleport();
}

AbstractUnit::AbstractUnit(const AbstractUnit& u) {
    x = u.x;
    y = u.y;
}

AbstractUnit::AbstractUnit(const Point& p) {
    x = p.x;
    y = p.y;
}

Point AbstractUnit::asPoint() const {
    return Point{x, y};
}

bool AbstractUnit::at(const AbstractUnit& u) const {
    return (x == u.x && y == u.y);
}

bool AbstractUnit::attacks(const AbstractUnit& u) const {
    return (abs(x - u.x) <= 1 &&
            abs(y - u.y) <= 1);
}

void AbstractUnit::moveTowards(const AbstractUnit& u) {
    if (x > u.x) x--;
    if (x < u.x) x++;
    if (y > u.y) y--;
    if (y < u.y) y++;
    checkBounds();
}

/*
void Unit::draw() {

}*/

void AbstractUnit::teleport() {
    x = rand_int (MIN_X, MAX_X);
    y = rand_int (MIN_Y, MAX_Y);
}

double AbstractUnit::distanceTo(const AbstractUnit& u) const {
    double dx = u.x - x;
    double dy = u.y - y;
    return sqrt(dx * dx + dy * dy);
}

/*
 * Put this unit inside playing field if outside
 */
void AbstractUnit::checkBounds() {
    if (x < MIN_X) x = MIN_X;
    if (x > MAX_X) x = MAX_X;
    if (y < MIN_Y) y = MIN_Y;
    if (y > MAX_Y) y = MAX_Y;
}
