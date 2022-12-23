#ifndef FREQUENCYRESPONSEINPUT_HPP
#define FREQUENCYRESPONSEINPUT_HPP

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QMainWindow>
#include <QDoubleSpinBox>

class FrequencyResponseInput : public QDialog
{
    Q_OBJECT

public:
    explicit FrequencyResponseInput(QWidget *parent = nullptr);
    ~FrequencyResponseInput();

    std::pair<double, double> get_xRange();
    double get_step();
    QString get_name();

private slots:
    void confirm();

private:
    QLineEdit *nameEdt;
    QDoubleSpinBox *fminEdt;
    QDoubleSpinBox *fmaxEdt;
    QDoubleSpinBox *stepEdt;

    QPushButton *confirmBtn;

    QString name;
    double fmin;
    double fmax;
    double step;
};

#endif // FREQUENCYRESPONSEINPUT_HPP
