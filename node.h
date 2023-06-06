#ifndef NODE_H
#define NODE_H


class Node
{
public:
    Node() = default;
    Node(int x, int y);
    Node* parent;

    int getX();
    int getY();
    int getF();
    int getG();
    int getH();
    void setF(int f);
    void setG(int g);
    void setH(int h);
    void setPath();
    void setWalkable(bool b);
    bool isWalkable();
    void setConnection(Node* n);
    Node* getConnection();
    Node* cameFrom;
    void calculateF();

private:
    int x, y, f, g, h;
    bool isPath;
    bool walkable;
};

#endif // NODE_H
