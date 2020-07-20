#include "mainwindow.h"
#include <QApplication>
#include<QProgressBar>
#include<iostream>
#include<QPalette>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow x;
    x.setGeometry(0,0,650,500);
    x.setStyleSheet("background-color:white;");
    x.setFixedSize(x.size());
    x.show();

    return a.exec();
}
