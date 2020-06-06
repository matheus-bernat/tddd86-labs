// Labb 8, Trailblazer - Matheus Bernat (matvi959) & Caspian Süsskind (cassu286)

#include "costs.h"
#include "trailblazer.h"
#include "pqueue.h"
#include <stack>
#include <algorithm>
#include <queue>
#include <set>
#include <limits>

using namespace std;

/* ------- Headers -------------- */
vector<Vertex*> helpDfs(Vertex* start, Vertex* end);
void reconstructPath(vector<Vertex*>& path, Vertex* node);
/* ------------------------------ */

/* Implements dfs algorithm for finding a way between two nodes. */
vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    path = helpDfs(start, end);
    reverse(path.begin(), path.end());
    graph.resetData();
    return path;
}

/* Recursive help function for the dfs algorithm. */
vector<Vertex*> helpDfs(Vertex* start, Vertex* end) {
    if(start == end) {
        vector<Vertex*> path;
        path.push_back(end);
        end->setColor(GREEN);
        return path;
    }
    start->visited = true;
    vector<Vertex*> path;
    for(Arc* arc: start->arcs) {
        if(!arc->finish->visited) {
            path = helpDfs(arc->finish, end);
            if(!path.empty()) {
                start->setColor(GREEN);
                path.push_back(start);
                return path;
            }
        }
    }
    start->setColor(GRAY);
    return path;
}

/* Implements bfs algorithm for finding a way between two nodes. */
vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    queue<std::pair<Vertex*, vector<Vertex*>>> queue;
    vector<Vertex*> path;
    queue.push(make_pair(start, path));
    start->visited = true;
    start->setColor(YELLOW);
    while(!queue.empty()) {
        Vertex* node = queue.front().first;
        vector<Vertex*> p = queue.front().second;
        p.push_back(node);
        queue.pop();
        node->setColor(GREEN);
        if(node == end) {
            graph.resetData();
            return p;
        }
        else {
            for(Arc* arc: node->arcs) {
                if(!arc->finish->visited) {
                    arc->finish->visited = true;
                    arc->finish->setColor(YELLOW);
                    queue.push(make_pair(arc->finish, p));
                }
            }
        }
    }
    graph.resetData();
    return path;
}

/* Implements dijkstras algorithm for finding a way between two nodes. */
vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    PriorityQueue<Vertex*> pqueue;
    set<Vertex*> helpSet = {start};
    pqueue.enqueue(start, start->cost);

    for(auto node : graph.getVertexSet()) {
        if(node != start) {
            node->cost = std::numeric_limits<double>::infinity();
        }
    }

    while(!pqueue.isEmpty()) {
        Vertex* node = pqueue.dequeue();
        node->setColor(GREEN);
        node->visited = true;
        if(node == end) {
            reconstructPath(path, node);
            graph.resetData();
            return path;
        }
        for(Arc* arc : node->arcs) {
            double cost = node->cost + arc->cost;
            if(cost < arc->finish->cost) {
                arc->finish->cost = cost;
                arc->finish->previous = node;
                if(helpSet.count(arc->finish)) {
                    pqueue.changePriority(arc->finish, cost);
                }
                else {
                    arc->finish->setColor(YELLOW);
                    pqueue.enqueue(arc->finish, cost);
                }
            }
        }
    }
    graph.resetData();
    return path;
}

/* Help function that reconstructs path from the end node to the start node. */
void reconstructPath(vector<Vertex*>& path, Vertex* node) {
    do {
        path.push_back(node);
        node = node->previous;
     } while(node != nullptr);
    reverse(path.begin(), path.end());
}

/* Implements A* algorithm for finding a way between two nodes. */
vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    PriorityQueue<Vertex*> pqueue;
    set<Vertex*> helpSet = {start};
    pqueue.enqueue(start, start->heuristic(end));

    for(auto node : graph.getVertexSet()) {
        if(node != start) {
            node->cost = std::numeric_limits<double>::infinity();
        }
    }

    while(!pqueue.isEmpty()) {
        Vertex* node = pqueue.dequeue();
        node->setColor(GREEN);
        node->visited = true;
        if(node == end) {
            reconstructPath(path, node);
            graph.resetData();
            return path;
        }
        for(Arc* arc : node->arcs) {
            double cost = node->cost + arc->cost;
            if(cost < arc->finish->cost) {
                arc->finish->cost = cost;
                arc->finish->previous = node;
                if(helpSet.count(arc->finish)) {
                    pqueue.changePriority(arc->finish, cost + arc->finish->heuristic(end));
                }
                else {
                    arc->finish->setColor(YELLOW);
                    pqueue.enqueue(arc->finish, cost + arc->finish->heuristic(end));
                }
            }
        }
    }
    graph.resetData();
    return path;
}
