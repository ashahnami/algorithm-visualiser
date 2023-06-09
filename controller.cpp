#include "controller.h"
#include "qpainter.h"

Controller::Controller(QWidget *parent)
    : QWidget{parent}
{
    layout = new QGridLayout(this);
    layout -> setVerticalSpacing(0);
    layout -> setHorizontalSpacing(5);

    algorithmDropdown = new QComboBox(this);
    algorithmDropdown -> addItem("A* Algorithm");
    algorithmDropdown -> addItem("Dijkstra's Algorithm");
    layout -> addWidget(algorithmDropdown, 0, 0);

    showStepsCheckbox = new QCheckBox("Show Steps", this);
    showStepsCheckbox -> setFixedHeight(40);
    layout -> addWidget(showStepsCheckbox, 1, 0);

    allowDiagonalCheckbox = new QCheckBox("Allow Diagonal", this);
    allowDiagonalCheckbox -> setFixedHeight(40);
    layout -> addWidget(allowDiagonalCheckbox, 2, 0);

    pushButton = new QPushButton("Clear", this);
    layout -> addWidget(pushButton, 0, 1);

    setLayout(layout);
}

void Controller::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    QRect rect(5, 5, width()-10, height()-10);
    painter.setBrush(QColor(80, 80, 80));
    painter.setOpacity(0.2);
    painter.drawRect(rect);

    QWidget::paintEvent(event);
}
