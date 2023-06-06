#ifndef ASTARALGORITHM_H
#define ASTAR_H

#include "node.h"
#include "algorithm.h"

#include <QWidget>

class AStar : public Algorithm
{
public:
    AStar(QWidget *parent);
    void start(Node start, Node end);
    void findPath();
    int calculateH(Node a);
    Node lowestFCost(QList<Node*> nodes);
    int calculateDistance(Node a, Node b);
    bool isEqual(Node a, Node b);
    int findNode(Node n, QList<Node*> nodes);
    void calculatePath();
    void reset();

    Node gridNodes[1000][1000];
    QList<Node*> borderNodes;

};

#endif // ASTAR_H
