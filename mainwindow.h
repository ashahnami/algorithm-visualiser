#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "astar.h"
#include "node.h"
#include "qpainter.h"
#include <QMouseEvent>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createGrid(int rows, int cols);
    void handleDrawing(QMouseEvent *event);
    Node* start;
    Node* end;
    bool drawing;
    int currKey;
    void startSearch();
    AStar *pathfinding;
    double zoomLevel = 1;
    QPainter painter;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

public slots:
    void onShowStepsToggled(int state);
    void onAllowDiagonalToggled(int state);
    void onClearButtonPressed();
};
#endif // MAINWINDOW_H
