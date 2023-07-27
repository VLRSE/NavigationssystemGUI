#ifndef SQUAREQPUSHBUTTON_H
#define SQUAREQPUSHBUTTON_H
#include "QtWidgets/qwidget.h"
#include <QPushButton>

class SquareQPushButton : public QPushButton
{
public:
    SquareQPushButton();
    SquareQPushButton(QWidget *parent = nullptr);
    SquareQPushButton(const QString &text, QWidget *parent = nullptr );
    SquareQPushButton(const QIcon& icon, const QString &text, QWidget *parent = nullptr);
    void init();
};

#endif // SQUAREQPUSHBUTTON_H
