#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTimer>
#include<iostream>
#include<fstream>
#include<QResizeEvent>
#include<QString>
#include<QDebug>
#include<QStyle>
#include<QSize>
#include<QDesktopWidget>

#include "windows.h"

float RAM_used(){
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    return (memInfo.ullTotalPhys - memInfo.ullAvailPhys)*100.00/memInfo.ullTotalPhys;
}

float TotalRAM()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    return memInfo.ullTotalPhys;
}


float FreeRAM()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    return memInfo.ullAvailPhys;
}


static float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
    static unsigned long long _previousTotalTicks = 0;
    static unsigned long long _previousIdleTicks = 0;

    unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
    unsigned long long idleTicksSinceLastTime = idleTicks - _previousIdleTicks;


    float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);

    _previousTotalTicks = totalTicks;
    _previousIdleTicks = idleTicks;
    return ret;
}

static unsigned long long FileTimeToInt64(const FILETIME & ft)
{
    return (((unsigned long long)(ft.dwHighDateTime)) << 32) | ((unsigned long long)ft.dwLowDateTime);
}

float GetCPULoad()
{
    FILETIME idleTime, kernelTime, userTime;
    return GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime) + FileTimeToInt64(userTime)) : -1.0f;
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
    QString str = QString::number(TotalRAM()/(1024.00*1024.00*1024.00), 'f', 2);
    QString str2 = QString::number(FreeRAM()/(1024.00*1024.00*1024.00), 'f', 2);
    ui->label_5->setText(str+" GB");
    ui->label_6->setText(str2+" GB");
    ui->prog_2->setValue(GetCPULoad()*100);
    ui->prog->setValue(RAM_used());
}



MainWindow::~MainWindow()
{
    delete ui;
}
