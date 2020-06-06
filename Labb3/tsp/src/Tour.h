// Labb 3B, TSP - Matheus Bernat (matvi959) & Caspian Süsskind (cassu286)

/*
 * The functions below declare the methods in the class Tour.
 */

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:
    /* Constructor used for testing. */
    Tour(const Point& a, const Point& b, const Point& c, const Point& d);

    /* Create an empty tour */
    Tour();

    /* Free all memory used by list nodes. */
    ~Tour();

     /* Print the tour to standard output. */
    void show();

    /* Draw the tour on scene. */
    void draw(QGraphicsScene* scene);

    /* Return number of points on tour. */
    int size();

    /* Return the total distance of the tour. */
    double distance();

    /* Insert p using nearest neighbor heuristic. */
    void insertNearest(const Point& p);

    /* Insert p using smallest increase heuristic. */
    void insertSmallest(const Point& p);

private:
    Node* firstNode;
};

#endif // TOUR_H
