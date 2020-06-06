/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>

GameState::GameState(){}

GameState::GameState(int numberOfRobots) {
    for (int i = 0; i < numberOfRobots; i++) {
        Robot* robot = new Robot();
        while (!isEmpty(*robot)) {
            // Move to empty place
            robot->teleport();
        }
        robotsAndJunks.push_back(robot);
    }
    teleportHero();
}

GameState::GameState(const GameState& other) {
    this->hero = other.hero;
    for(Robot* robot: other.robotsAndJunks) {
        this->robotsAndJunks.push_back(robot->clone());
    }
}

GameState::~GameState() {
    for(Robot* robot: robotsAndJunks) {
        delete robot;
    }
}

GameState& GameState::operator=(const GameState& other) {
    if(this != &other) {
        // Free memory, remove old robots/junks

        for(Robot* robot : robotsAndJunks) {
            delete robot;
        }
        // Clear vector of pointers, doesn't point to robots anymore
        this->robotsAndJunks.clear();

        this->hero = other.hero;
        for(Robot* robot : other.robotsAndJunks) {
            this->robotsAndJunks.push_back(robot->clone());
        }
    }
    return *this;
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    for (size_t i = 0; i < robotsAndJunks.size(); ++i)
        robotsAndJunks[i]->draw(scene);
    hero.draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for (unsigned int i = 0; i < robotsAndJunks.size(); i++) {
        robotsAndJunks[i]->moveTowards(hero);
    }
}

int GameState::countCollisions() {
    int numberDestroyed = 0;
    unsigned int i = 0;

    while (i < robotsAndJunks.size()) {

        bool collision = (countRobotsAt(*robotsAndJunks[i]) > 1);

        if(collision && !robotsAndJunks[i]->isJunk()) {
            // Create junk
            Junk* junk = new Junk(*robotsAndJunks[i]);
            // Remove robot
            delete robotsAndJunks[i];
            robotsAndJunks[i] = junk;
            numberDestroyed++;
        }
        i++;
    }
    return numberDestroyed;
}


bool GameState::anyRobotsLeft() const {
    for (size_t i = 0; i < robotsAndJunks.size(); i++) {
        if (!robotsAndJunks[i]->isJunk()) {
            return true; // dvs, om det finns ett enda objekt i robots vektorn, betyder det att det finns robotar kvar
        }
    }
    return false;
}

bool GameState::heroDead() const {
    return !isEmpty(hero);
}

bool GameState::isSafe(const Unit& unit) const {
    for (unsigned int i = 0; i < robotsAndJunks.size(); i++) {
        if (!robotsAndJunks[i]->isJunk() && robotsAndJunks[i]->attacks(unit)) { // robots på väg till unit
            return false;
        } else if (robotsAndJunks[i]->at(unit)){ // Junk som redan befinner sig på unit
            return false;
        }
    }
    return true;
}

void GameState::moveHeroTowards(const Unit& dir) {
    hero.moveTowards(dir);
}

Hero GameState::getHero() const {return hero;}

/*
 * Free of robots and junk.
 */
bool GameState::isEmpty(const Unit& unit) const {
    for (size_t i = 0; i < robotsAndJunks.size(); ++i) {
        if (robotsAndJunks[i]->at(unit))
            return false;
    }
    return true;
}

/*
 * How many robots (AND JUNKS) are there at unit?
 */
int GameState::countRobotsAt(const Unit& unit) const {
    int count = 0;
    for (size_t i = 0; i < robotsAndJunks.size(); ++i) {
        if (robotsAndJunks[i]->at(unit))
            count++;
    }
    return count;
}






