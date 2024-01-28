#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model.setTable("dxcc");
    ui->tableView->setModel(&model);

    QSqlQuery query;
    query.exec(QString("create table if not exists dxcc ("
               "Dxcc integer primary key,"
               "Prefic text,"
               "Entity text,"
               "Deleted text,"
               "Mix text,"
               "Ph text,"
               "CW text,"
               "RT text,"
               "SAT text,"
               "160 text,"
               "80 text,"
               "40 text,"
               "30 text,"
               "20 text,"
               "17 text,"
               "15 text,"
               "12 text,"
               "10 text,"
               "6 text,"
               "2 text,"
               "70cm text,"
               "Comment text)"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

