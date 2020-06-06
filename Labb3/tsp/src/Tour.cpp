// Labb 3B, TSP - Matheus Bernat (matvi959) & Caspian Süsskind (cassu286)

/*
 * The functions below define the methods declared in the class header Tour.h.
 * They contain functionality to show the tour, draw the tour, calculate the
 * distance of the tour and build the tour itself.
 */

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{
    firstNode = nullptr;
}

Tour::Tour(const Point& a, const Point& b, const Point& c, const Point& d) // KOMPLETTERING: ändrades till const&
{
    Node* node1 = new Node(a);
    Node* node2 = new Node(b);
    Node* node3 = new Node(c);
    Node* node4 = new Node(d);
    firstNode = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node1;
}

Tour::~Tour()
{
    Node* current = firstNode;
    Node* next = nullptr;
    do {
        next = current->next;
        delete current;
        current = next;
    } while(current != firstNode);
}

void Tour::show()
{
    if(firstNode != nullptr) {
        Node* current = firstNode;
        do {
            cout << (current->point).toString() << endl;
            current = current->next;
        } while(current != firstNode);
    }
}

void Tour::draw(QGraphicsScene *scene)
{
    if(firstNode != nullptr) {
        Node* current = firstNode;
        do {
            current->point.drawTo(current->next->point, scene);
            current = current->next;
        } while(current != firstNode);
    }
}

int Tour::size()
{
    int size = 0;
    if(firstNode != nullptr) {
        Node* current = firstNode;
        do {
            current = current->next;
            size++;
        } while(current != firstNode);
    }
    return size;
}

double Tour::distance()
{
    double distance = 0;
    if(firstNode != nullptr) {
        Node* current = firstNode;
        do {
            distance += (current->point).distanceTo(current->next->point);
            current = current->next;
        } while(current != firstNode);
    }
    return distance;
}

void Tour::insertSmallest(const Point& p) // KOMPLETTERING: ändrades till const&
{
    if(firstNode != nullptr) {
        Node* current = firstNode;
        Node* closestNode = nullptr;
        double distance = p.distanceTo(current->point) + p.distanceTo(current->next->point) - current->point.distanceTo(current->next->point);
        closestNode = current;
        current = current->next;
        int newDistance;
        while(current != firstNode) {
            newDistance = p.distanceTo(current->point) + p.distanceTo(current->next->point) - current->point.distanceTo(current->next->point);
            if(distance > newDistance) {
                closestNode = current;
                distance = newDistance;
            }
            current = current->next;
        }
        Node* newNode = new Node(p, closestNode->next);
        closestNode->next = newNode;
    } else {
        firstNode = new Node(p);
        firstNode->next = firstNode;
    }
}

void Tour::insertNearest(const Point& p) // KOMPLETTERING: ändrades till const&
{
    if(firstNode != nullptr) {
        Node* current = firstNode;
        Node* closestNode = nullptr;
        double distance = p.distanceTo(current->point);
        closestNode = current;
        current = current->next;
        while(current != firstNode) {
            if(distance > p.distanceTo(current->point)) {
                closestNode = current;
                distance = p.distanceTo(current->point);
            }
            current = current->next;
        }
        Node* newNode = new Node(p, closestNode->next);
        closestNode->next = newNode;
    } else {
        firstNode = new Node(p);
        firstNode->next = firstNode;
    }
}
