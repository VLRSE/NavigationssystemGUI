#include "squareqpushbutton.h"

SquareQPushButton::SquareQPushButton() {
    init();
}
SquareQPushButton::SquareQPushButton(QWidget *parent )
    :QPushButton(parent){init();}

SquareQPushButton::SquareQPushButton(const QString &text, QWidget *parent)
    :QPushButton(text, parent){init();}

SquareQPushButton::SquareQPushButton(const QIcon &icon, const QString &text, QWidget *parent)
    :QPushButton(icon, text){
    init();
}

void SquareQPushButton::init(){
     this->setFixedSize(300,300);
    this->setMaximumSize(50,50);
    this->setBackgroundRole(QPalette::Light);
}
