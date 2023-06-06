#include "algorithm.h"

Algorithm::Algorithm(QWidget *parent)
    : QWidget(parent)
{

}

void Algorithm::update(){
    this->parentWidget()->repaint();
}
