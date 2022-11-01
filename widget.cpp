#include "widget.hpp"
#include "ui_widget.h"
#include <QFrame>
#include <QGridLayout>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QFrame *frame1 = new QFrame(this); // создаем виджет
    frame1->setFrameStyle(QFrame::Box); // устанавливаем рамки фрейма
    frame1->setCursor(Qt::SizeAllCursor); // задаем тип курсора SizeAllCursor для фрейма

    QFrame *frame2 = new QFrame(this); // создаем виджет
    frame2->setFrameStyle(QFrame::Box); // устанавливаем рамки фрейма
    frame2->setCursor(Qt::WaitCursor); // задаем тип курсора WaitCursor для фрейма

    QFrame *frame3 = new QFrame(this); // создаем виджет
    frame3->setFrameStyle(QFrame::Box); // устанавливаем рамки фрейма
    frame3->setCursor(Qt::PointingHandCursor); // задаем тип курсора PointingHandCursor для фрейма


    QPushButton *quitBtn = new QPushButton("Quit", this);
//    quitBtn->setGeometry(50, 40, 75, 30);

    connect(quitBtn, &QPushButton::clicked, qApp, &QApplication::quit);

    // Группируем все фреймы в одну строку
    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(frame1, 1, 0);
    grid->addWidget(frame2, 0, 1);
    grid->addWidget(frame3, 1, 2);
    grid->addWidget(quitBtn, 1, 2);

    setLayout(grid);
}

Widget::~Widget()
{
    delete ui;
}

