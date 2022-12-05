#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "hardware/Experiment.hpp"

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>

#include <qcustomplot.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void resonanceCurve();

private:
    Experiment exp;
    QPushButton *startBtn;
    QComboBox *whichExperimentCb;
    QCustomPlot *customPlot;
};
#endif // MAINWINDOW_HPP
