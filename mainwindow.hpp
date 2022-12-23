#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "hardware/Experiment.hpp"

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>

#include <qcustomplot.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startExperiment();
    void connectGenerator();
    void connectOscilloscope();

    void whichExperimentChanged();
    void enableToStart();

private:
    Experiment *exp;
    Generator *gen;
    Oscilloscope *osc;

    QVector<double> resonanceResponseParam;

    QCustomPlot *customPlot;
    QComboBox *whichExperimentCb;
    int whichExperiment;

    QPushButton *startBtn;

    QPushButton *connectOscBtn;
    QPushButton *connectGenBtn;
};
#endif // MAINWINDOW_HPP
