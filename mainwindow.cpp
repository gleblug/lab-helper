#include "mainwindow.hpp"
#include "hardware/Experiment.hpp"
#include "frequencyresponseinput.hpp"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QTextStream>

#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Lab Helper");

//    // MENU BAR
//    QMenu *file = menuBar()->addMenu("&Файл");
//    QMenu *measures = menuBar()->addMenu("&Измерения");
//    QMenu *devices = menuBar()->addMenu("&Устройства");
//    QMenu *info = menuBar()->addMenu("&Инфо");

//    // file actions
//    QAction *open = new QAction("&Открыть", this);
//    file->addAction(open);

//    QAction *save = new QAction("&Сохранить", this);
//    file->addAction(save);

//    QAction *quit = new QAction("&Выход", this);
//    file->addAction(quit);

//    // measures actions
//    QAction *new_measure = new QAction("&Новая серия измерений");
//    measures->addAction(new_measure);
//    connect(new_measure, &QAction::triggered,
//            this, &MainWindow::new_measure_window_show);

//    // devices actions
//    QAction *devices_list = new QAction("&Список устройств", this);
//    devices->addAction(devices_list);

//    QAction *new_device = new QAction("&Новое устройство", this);
//    devices->addAction(new_device);

//    devices->addSeparator();

//    QAction *auto_devices = new QAction("&Автоматическое подключение", this);
//    devices->addAction(auto_devices);

//    // info actions
//    QAction *about = new QAction("&О программе", this);
//    info->addAction(about);


//    // STATUS BAR
    statusBar();
    statusBar()->showMessage("Пожалуйста, подключите устройства", 10000);

    statusBar();

    // LAYOUT
    QFrame *frame = new QFrame(this);
    setCentralWidget(frame);
    QVBoxLayout *vbox = new QVBoxLayout(frame);

    vbox->setSpacing(10);

//     create graph and assign data to it:
    customPlot = new QCustomPlot(this);
    customPlot->legend->setVisible(true);
    vbox->addWidget(customPlot);

    QGridLayout *grid = new QGridLayout();
    vbox->addLayout(grid);

    connectGenBtn = new QPushButton("Подключить генератор", this);
    grid->addWidget(connectGenBtn, 0, 0);

    connectOscBtn = new QPushButton("Подключить осциллограф", this);
    grid->addWidget(connectOscBtn, 1, 0);

    whichExperimentCb = new QComboBox(this);
    whichExperimentCb->addItem("АЧХ контура");
    whichExperimentCb->addItem("ФЧХ контура");
    whichExperimentCb->addItem("Процесс установления");
    whichExperimentCb->addItem("Процесс затухания");
    grid->addWidget(whichExperimentCb, 0, 1, 1, 3);
    whichExperimentChanged();

    startBtn = new QPushButton("Начать измерения", this);
    startBtn->setDisabled(true);
    grid->addWidget(startBtn, 1, 1, 1, 3);


    connect(connectGenBtn, &QPushButton::clicked, this, &MainWindow::connectGenerator);
    connect(connectOscBtn, &QPushButton::clicked, this, &MainWindow::connectOscilloscope);

    connect(startBtn, &QPushButton::clicked, this, &MainWindow::startExperiment);

    connect(whichExperimentCb, &QComboBox::currentTextChanged, this, &MainWindow::whichExperimentChanged);
}

MainWindow::~MainWindow()
{    
}

void MainWindow::connectGenerator()
{
    try
    {
        gen = new Generator();

        connectGenBtn->setDisabled(true);
        connectGenBtn->setText("Генератор подключен");

        if (!connectOscBtn->isEnabled())
            enableToStart();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void MainWindow::connectOscilloscope()
{
    try
    {
        osc = new Oscilloscope();

        connectOscBtn->setDisabled(true);
        connectOscBtn->setText("Осциллограф подключен");

        if (!connectGenBtn->isEnabled())
            enableToStart();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void MainWindow::startExperiment()
{
    QString xLabel;
    QString yLabel;
    std::pair<double, double> xRange;
    std::pair<double, double> yRange;
    QVector<double> x;
    QVector<double> y;
    QString name;

    switch (whichExperiment)
    {
        case 0:
    {
        double step = 10;

        FrequencyResponseInput dlg(this);

        if (dlg.exec())
        {
            xRange = dlg.get_xRange();
            step = dlg.get_step();
            name = dlg.get_name();
        }
        else
            return;

        xLabel = "Частота, Гц";
        yLabel = "Амплитуда, В";

        startBtn->setDisabled(true);

        auto data = exp->frequency_response(xRange.first, xRange.second, step);
        x = QVector<double>::fromStdVector(data.first);
        y = QVector<double>::fromStdVector(data.second);

        yRange.first = *std::min_element(std::begin(y), std::end(y));
        yRange.second = *std::max_element(std::begin(y), std::end(y));

        break;
    }
        default:
    {
        statusBar()->showMessage("Невозможно начать эксперимент!", 5000);
        return;
    }
    }

    customPlot->addGraph();
    customPlot->graph()->setData(x, y);
    customPlot->graph()->setName(name);

    customPlot->xAxis->setLabel(xLabel);
    customPlot->yAxis->setLabel(yLabel);

    customPlot->xAxis->setRange(xRange.first, xRange.second);
    customPlot->yAxis->setRange(yRange.first, yRange.second);

    customPlot->replot();

    startBtn->setEnabled(true);
}

void MainWindow::whichExperimentChanged()
{
    whichExperiment = whichExperimentCb->currentIndex();
    switch (whichExperiment) {

    }
}

void MainWindow::enableToStart()
{
    startBtn->setEnabled(true);
    exp = new Experiment(*gen, *osc);
}
