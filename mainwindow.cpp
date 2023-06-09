#include "mainwindow.h"

#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(700, 600);
    setFocus();

    pathfinding = new AStar(this);
    start = &pathfinding->gridNodes[0][0];
    end = &pathfinding->gridNodes[5][5];

    controller = new Controller(this);
    controller -> setMinimumSize(220, 100);

    connect(controller->algorithmDropdown, &QComboBox::currentIndexChanged, this, &MainWindow::onAlgorithmChange);
    connect(controller->showStepsCheckbox, &QCheckBox::stateChanged, this, &MainWindow::onShowStepsToggled);
    connect(controller->allowDiagonalCheckbox, &QCheckBox::stateChanged, this, &MainWindow::onAllowDiagonalToggled);
    connect(controller->pushButton, &QPushButton::clicked, this, &::MainWindow::onButtonClicked);
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int squareSize = 25 * zoomLevel;

    painter.setBrush(QColor(245, 245, 245));
    QPen pen(QColor(200, 200, 200));
    pen.setWidth(1);
    painter.setPen(pen);

    for(int i=0; i<height(); i+=squareSize){
        for(int j=0; j<width(); j+=squareSize){
            painter.drawRect(QRect(j, i, squareSize, squareSize));
        }
    }

    foreach(Node* node, pathfinding->borderNodes){
        int x = node->getX() * squareSize;
        int y = node->getY() * squareSize;
        painter.fillRect(x+1, y+1, squareSize-1, squareSize-1, Qt::black);
    }

    foreach(Node* node, pathfinding->openNodes){
        int x = node->getX() * squareSize + 1;
        int y = node->getY() * squareSize + 1;
        painter.fillRect(x, y, squareSize-1, squareSize-1, Qt::green);
    }

    foreach(Node* node, pathfinding->closedNodes){
        int x = node->getX() * squareSize + 1;
        int y = node->getY() * squareSize + 1;
        painter.fillRect(x, y, squareSize-1, squareSize-1, QColor(238, 75, 43));
    }

    foreach(Node* node, pathfinding->pathNodes){
        int x = node->getX() * squareSize + 1;
        int y = node->getY() * squareSize + 1;
        painter.fillRect(x, y, squareSize-1, squareSize-1, Qt::cyan);
    }

    painter.fillRect(start->getX() * squareSize + 1, start->getY() * squareSize + 1, squareSize-1, squareSize-1, Qt::red);
    painter.fillRect(end->getX() * squareSize + 1, end->getY() * squareSize + 1, squareSize-1, squareSize-1, Qt::blue);

    QWidget::paintEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    currKey = event -> key();
    if(currKey == Qt::Key_Space){
        pathfinding -> start(*start, *end);
    }
    QWidget::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    currKey = 0;
    QWidget::keyReleaseEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    drawing = true;
    handleDrawing(event);
    QWidget::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(rect().contains(event -> pos())){
        handleDrawing(event);
    }
    QWidget::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    drawing = false;
    QWidget::mouseReleaseEvent(event);
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    const double zoomFactor = 1.2;
    int numDegrees = event -> angleDelta().y() / 8;
    int numSteps = numDegrees / 15;
    double zoom = qPow(zoomFactor, numSteps);

    zoomLevel *= zoom;

    const double minZoomLevel = 0.6;
    const double maxZoomLevel = 4.0;

    zoomLevel = qBound(minZoomLevel, zoomLevel, maxZoomLevel);

    update();
}

void MainWindow::onAlgorithmChange(int index)
{
    qDebug() << "Algorithm number" << (index==0 ? "1" : "2") << "selected";
}

void MainWindow::onShowStepsToggled(int state)
{
    pathfinding->showSteps = state == 2 ? true : false;
    qDebug() << "show steps toggled";
    setFocus();
}

void MainWindow::onAllowDiagonalToggled(int state)
{
    pathfinding->diagMove = state == 2 ? true : false;
    qDebug() << "allow diagonal toggled";
    setFocus();
}

void MainWindow::onButtonClicked()
{
    pathfinding -> reset();
    setFocus();
}

void MainWindow::handleDrawing(QMouseEvent *event)
{
    int squareSize = 25 * zoomLevel;
    QPoint pos = event -> pos();
    int x = pos.x() / squareSize;
    int y = pos.y() / squareSize;
    int ind = pathfinding->findNode(pathfinding->gridNodes[x][y], pathfinding->borderNodes);

    if(drawing){
        if(currKey == Qt::Key_S){

            start = &pathfinding->gridNodes[x][y];
            if(ind != -1){
                pathfinding->borderNodes.removeAt(pathfinding->findNode(pathfinding->gridNodes[x][y], pathfinding->borderNodes));
            }
            pathfinding->reset();

        } else if(currKey == Qt::Key_E){

            end = &pathfinding->gridNodes[x][y];
            if(ind != -1){
                pathfinding->borderNodes.removeAt(pathfinding->findNode(pathfinding->gridNodes[x][y], pathfinding->borderNodes));
            }
            pathfinding->reset();

        } else if(ind == -1){
            pathfinding -> borderNodes.append(&pathfinding->gridNodes[x][y]);
            pathfinding -> gridNodes[x][y].setWalkable(false);
        }

    } else {
        if(ind != -1){
            pathfinding -> borderNodes.removeAt(ind);
            pathfinding -> gridNodes[x][y].setWalkable(true);
        }
    }
    repaint();
}


