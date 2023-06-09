#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QGridLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>

class Controller : public QWidget
{
    Q_OBJECT
public:
    explicit Controller(QWidget *parent = nullptr);
    QGridLayout *layout;

    QComboBox *algorithmDropdown;
    QCheckBox *showStepsCheckbox;
    QCheckBox *allowDiagonalCheckbox;
    QPushButton *pushButton;

protected:
    void paintEvent(QPaintEvent *event) override;

signals:

};

#endif // CONTROLLER_H
