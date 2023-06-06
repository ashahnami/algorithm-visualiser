#include "astar.h"

#include <iostream>
#include <algorithm>
#include <Windows.h>
#include "limits.h"
#include <QWidget>
#include <QTimer>

AStar::AStar(QWidget *parent)
    : Algorithm(parent)
{
    for(int i=0; i<1000; i++){
        for(int j=0; j<1000; j++){
            gridNodes[i][j] = Node(i, j);
            gridNodes[i][j].setG(INT_MAX);
        }
    }

    startNode = gridNodes[0][0];
    endNode = gridNodes[5][5];

    showSteps = false;
    diagMove = false;
}

void AStar::start(Node start, Node end){
    startNode = start;
    endNode = end;

    findPath();
    calculatePath();

    this->update();

    qDebug() << "Final cost: " << gridNodes[endNode.getX()][endNode.getY()].getF() << '\n';
}

void AStar::findPath(){

    gridNodes[startNode.getX()][startNode.getY()].setG(0);
    gridNodes[startNode.getX()][startNode.getY()].setH(calculateH(startNode));
    gridNodes[startNode.getX()][startNode.getY()].calculateF();
    openNodes.append(&gridNodes[startNode.getX()][startNode.getY()]);

    while(!(openNodes.isEmpty())){
        Node currNode = lowestFCost(openNodes);

        closedNodes.append(&gridNodes[currNode.getX()][currNode.getY()]);
        openNodes.removeAt(findNode(currNode, openNodes));

        int currX = currNode.getX();
        int currY = currNode.getY();

        if(isEqual(currNode, endNode)) return;

        if(diagMove){
            for(int y=currY-1; y<=currY+1; y++){
                for(int x=currX-1; x<=currX+1; x++){

                    if(x < 0 || x >= 1000 || y < 0 || y >= 1000) continue;
                    if(y == currNode.getY() && x == currNode.getX()) continue;
                    if(!gridNodes[x][y].isWalkable()) continue;
                    if(findNode(gridNodes[x][y], closedNodes) != -1) continue;

                    int gCost = currNode.getG() + calculateDistance(gridNodes[x][y], currNode);

                    if(gCost < gridNodes[x][y].getG()){
                        gridNodes[x][y].cameFrom = &gridNodes[currNode.getX()][currNode.getY()];
                        gridNodes[x][y].setG(gCost);
                        gridNodes[x][y].setH(calculateDistance(gridNodes[x][y], endNode));
                        gridNodes[x][y].calculateF();

                        if(findNode(gridNodes[x][y], openNodes) == -1){
                            openNodes.append(&gridNodes[x][y]);
                        }
                    }
                }
            }
        } else {
            for(int y=currY-1; y<=currY+1; y++){
                for(int x=currX-1; x<=currX+1; x++){

                    if((x == currX-1 && y == currY-1) || (x == currX-1 && y == currY+1) || (x == currX+1 && y == currY-1) || (x == currX+1 && y == currY+1)) continue;
                    if(x < 0 || x >= 1000 || y < 0 || y >= 1000) continue;
                    if(y == currNode.getY() && x == currNode.getX()) continue;
                    if(!gridNodes[x][y].isWalkable()) continue;
                    if(findNode(gridNodes[x][y], closedNodes) != -1) continue;

                    int gCost = currNode.getG() + calculateDistance(gridNodes[x][y], currNode);

                    if(gCost < gridNodes[x][y].getG()){
                        gridNodes[x][y].cameFrom = &gridNodes[currNode.getX()][currNode.getY()];
                        gridNodes[x][y].setG(gCost);
                        gridNodes[x][y].setH(calculateDistance(gridNodes[x][y], endNode));
                        gridNodes[x][y].calculateF();

                        if(findNode(gridNodes[x][y], openNodes) == -1){
                            openNodes.append(&gridNodes[x][y]);
                        }
                    }
                }
            }
        }

        if(showSteps){
            this->update();
            Sleep(100);
        }
    }
}

int AStar::findNode(Node n, QList<Node*> nodes){
    for(int i=0; i<nodes.size(); i++){
        if(isEqual(n, *nodes[i])) return i;
    }
    return -1;
}

void AStar::calculatePath(){
    Node* curr = &gridNodes[endNode.getX()][endNode.getY()];
    while(curr->cameFrom != NULL){
        pathNodes.append(curr);
        curr = curr->cameFrom;
    }
}

void AStar::reset()
{
    for(Node* n: pathNodes){
        n->setConnection(NULL);
    }

    for(Node *n: pathNodes){
        gridNodes[n->getX()][n->getY()].setG(INT_MAX);
        gridNodes[n->getX()][n->getY()].setH(calculateH(gridNodes[n->getX()][n->getY()]));
        gridNodes[n->getX()][n->getY()].calculateF();
    }

    for(Node *n: closedNodes){
        gridNodes[n->getX()][n->getY()].setG(INT_MAX);
        gridNodes[n->getX()][n->getY()].setH(calculateH(gridNodes[n->getX()][n->getY()]));
        gridNodes[n->getX()][n->getY()].calculateF();
    }

    for(int i=0; i<1000; i++){
        for(int j=0; j<1000; j++){
            gridNodes[i][j].setG(INT_MAX);
            gridNodes[i][j].setH(INT_MAX);
            gridNodes[i][j].calculateF();
        }
    }

    openNodes.clear();
    closedNodes.clear();
    pathNodes.clear();

    gridNodes[startNode.getX()][startNode.getY()].setG(0);
    gridNodes[startNode.getX()][startNode.getY()].setH(0);
    gridNodes[startNode.getX()][startNode.getY()].calculateF();

    qDebug() << "start node f cost" << gridNodes[startNode.getX()][startNode.getY()].getH();
    qDebug() << "end node f cost" << gridNodes[endNode.getX()][endNode.getY()].getH();

    parentWidget()->repaint();
}

int AStar::calculateDistance(Node a, Node b){
    int dx = abs(a.getX() - b.getX());
    int dy = abs(a.getY() - b.getY());

//    if(diagMove) return (10 * (dx + dy)) + (-6 * dx);
//    else return dx + dy;
    return dx + dy;
}

int AStar::calculateH(Node a){
    return calculateDistance(a, endNode);
}

Node AStar::lowestFCost(QList<Node*> nodes){
    Node lowestFCostNode = *nodes[0];
    int lowestFCost = nodes[0]->getF();

    for(int i=0; i<nodes.size(); i++){
        if(nodes[i]->getF() < lowestFCost){
            lowestFCostNode = *nodes[i];
            lowestFCost = nodes[i]->getF();
        }
    }

    return lowestFCostNode;
}

bool AStar::isEqual(Node a, Node b){
    return a.getX()==b.getX() && a.getY()==b.getY();
}
