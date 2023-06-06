#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "node.h"
#include "qlist.h"
#include "qwidget.h"

class Algorithm : public QWidget
{
    Q_OBJECT

public:
    Algorithm(QWidget *parent = nullptr);
    Node startNode;
    Node endNode;
    QList<Node*> openNodes;
    QList<Node*> closedNodes;
    QList<Node*> pathNodes;
    void update();
    bool showSteps;
    bool diagMove;
};

#endif // ALGORITHM_H
