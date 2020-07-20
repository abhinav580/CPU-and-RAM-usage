#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTimer>
#include<iostream>
#include "logger.h"
#include<fstream>
#include<QResizeEvent>
#include<QDebug>
#include<QStyle>
#include<QSize>
#include<QDesktopWidget>
using namespace std;
size_t previous_idle_time=0, previous_total_time=0, idle_time,total_time;


vector<size_t> get_cpu_times() {
    ifstream proc_stat("/proc/stat");
    proc_stat.ignore(5, ' '); // Skip the 'cpu' prefix.
    vector<size_t> times;
    for (size_t time; proc_stat >> time; times.push_back(time));
    return times;
}

bool get_cpu_times(size_t &idle_time, size_t &total_time) {
    const std::vector<size_t> cpu_times = get_cpu_times();
    if (cpu_times.size() < 4)
        return false;
    idle_time = cpu_times[3];
    total_time = accumulate(cpu_times.begin(), cpu_times.end(), 0);
    return true;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->prog->setMinimum(0);
    ui->prog->setMaximum(100);
    ui->label->setText("MEMORY USAGE");
    ui->label_2->setText("CPU USAGE");
    ui->label_2->setStyleSheet("color:grey;");
    ui->label->setStyleSheet("color:grey;");
    QTimer *timer = new QTimer();
    ui->prog->setValue(0);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateProgress);
    //connect(timer, &QTimer::timeout, this, &MainWindow::updateProgress);
    timer->start(1000);
    ui->prog->show();
}


void MainWindow::updateProgress()
{
    Logger test;
    float pr = (test.logMemoryUsage()/test.availMem())*100;
    QString str = QString::number(test.availMem(), 'f', 2);
    QString str2 = QString::number(test.availMem()-test.logMemoryUsage(), 'f', 2);
    ui->label_5->setText(str+" GB");
    ui->label_6->setText(str2+" GB");
      //  for (size_t idle_time, total_time; get_cpu_times(idle_time, total_time); sleep(1)) {
            get_cpu_times(idle_time, total_time);
            float idle_time_delta = idle_time - previous_idle_time;
            float total_time_delta = total_time - previous_total_time;
            float utilization = 100.0 * (1.0 - idle_time_delta / total_time_delta);
          //  std::cout << utilization << '%' << std::endl;

            ui->prog_2->setValue(utilization);
            previous_idle_time = idle_time;
            previous_total_time = total_time;
        //}


    ui->prog->setValue(pr);
}



MainWindow::~MainWindow()
{
    delete ui;
}
