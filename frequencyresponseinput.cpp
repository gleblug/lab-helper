#include "frequencyresponseinput.hpp"
#include <QFormLayout>
#include <QLabel>

#include <iostream>

FrequencyResponseInput::FrequencyResponseInput(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Введите данные для начала эксперимента");

    QFormLayout *form = new QFormLayout(this);

    double maximum = 10e6;

    nameEdt = new QLineEdit();
    form->addRow("Имя измерения", nameEdt);

    fminEdt = new QDoubleSpinBox();
    fminEdt->setMaximum(maximum);
    fminEdt->setValue(1400);
    form->addRow("Нач. частота, Гц", fminEdt);

    fmaxEdt = new QDoubleSpinBox();
    fmaxEdt->setMaximum(maximum);
    fmaxEdt->setValue(1800);
    form->addRow("Конеч. частота, Гц", fmaxEdt);

    stepEdt = new QDoubleSpinBox();
    stepEdt->setMaximum(maximum);
    stepEdt->setValue(20);
    form->addRow("Шаг, Гц", stepEdt);

    QPushButton *confirmBtn = new QPushButton("Подтвердить");
    form->addWidget(confirmBtn);

    connect(confirmBtn, &QPushButton::clicked, this, &FrequencyResponseInput::confirm);
}

FrequencyResponseInput::~FrequencyResponseInput()
{
}

void FrequencyResponseInput::confirm()
{
    name = nameEdt->text();
    fmin = fminEdt->value();
    fmax = fmaxEdt->value();
    step = stepEdt->value();

    accept();
}

std::pair<double, double> FrequencyResponseInput::get_xRange()
{
    return std::make_pair(fmin, fmax);
}

double FrequencyResponseInput::get_step()
{
    return step;
}

QString FrequencyResponseInput::get_name()
{
    return name;
}
