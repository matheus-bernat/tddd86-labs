/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H


#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    Junk();
    Junk(const Unit& c);
    ~Junk();

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;

    bool attacks(const Unit &u) const override;

    void moveTowards(const Unit& u) override;

    bool isJunk() const override;

    virtual Robot* clone() override;
};

#endif // JUNK_H
