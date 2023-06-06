#include "node.h"

Node::Node(int x, int y)
    : x(x), y(y)
{
    isPath = false;
    walkable = true;
    cameFrom = nullptr;
}

int Node::getX(){return x;}
int Node::getY(){return y;}
int Node::getF(){return f;}
int Node::getG(){return g;}
int Node::getH(){return h;}
void Node::setF(int f){this->f = f;}
void Node::setG(int g){this->g = g;}
void Node::setH(int h){this->h = h;}

void Node::setPath(){
    isPath=true;
}

void Node::setWalkable(bool b){
    if(b) walkable = true;
    else walkable = false;
}

bool Node::isWalkable(){
    return walkable;
}

void Node::setConnection(Node* n){
    cameFrom = n;
}

Node* Node::getConnection(){
    return cameFrom;
}

void Node::calculateF(){
    f = g + h;
}
