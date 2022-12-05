#include "mainwindow.hpp"
#include "hardware/Experiment.hpp"

#include <QVBoxLayout>
#include <QFrame>
#include <QTextStream>

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
//    statusBar();
//    statusBar()->showMessage("Ready", 10000);

    statusBar();

    // LAYOUT
    QFrame *frame = new QFrame(this);
    setCentralWidget(frame);
    QVBoxLayout *layout = new QVBoxLayout(frame);

    layout->setSpacing(10);

    // create graph and assign data to it:
    customPlot = new QCustomPlot(this);

    layout->addWidget(customPlot);


    whichExperimentCb = new QComboBox(this);
    whichExperimentCb->addItem("Резонансная кривая");
    layout->addWidget(whichExperimentCb, 0, Qt::AlignHCenter);

    startBtn = new QPushButton("Начать измерения", this);
    layout->addWidget(startBtn, 0, Qt::AlignHCenter);

    connect(startBtn, &QPushButton::clicked, this, &MainWindow::resonanceCurve);
}

MainWindow::~MainWindow()
{
}

void MainWindow::resonanceCurve()
{
    startBtn->setEnabled(false);

    auto data = exp.resonance_curve();
    QVector<double> x = QVector<double>::fromStdVector(data.first);
    QVector<double> y = QVector<double>::fromStdVector(data.second);

    QTextStream out(stdout);
    for (int i = 0; i < x.size(); i++) {
        out << x[i] << '\t' << y[i] << '\n';
    }

    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("Frequency, Hz");
    customPlot->yAxis->setLabel("Amplitude, V");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(1400, 1800);
    customPlot->yAxis->setRange(0, 3);
    customPlot->replot();

    startBtn->setEnabled(true);
}
