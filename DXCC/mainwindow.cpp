#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlQuery query;
    query.exec(QString("create table if not exists dxcc ("
        "Dxcc integer primary key,"
        "Prefix text,"
        "Entity text,"
        "Deleted text,"
        "Mix text,"
        "Ph text,"
        "CW text,"
        "RT text,"
        "SAT text,"
        "m160 text,"
        "m80 text,"
        "m40 text,"
        "m30 text,"
        "m20 text,"
        "m17 text,"
        "m15 text,"
        "m12 text,"
        "m10 text,"
        "m6 text,"
        "m2 text,"
        "cm70 text,"
        "Comment text)"));

    model.setTable("dxcc");
    ui->tableView->setModel(&model);
    model.select();
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(Update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Update()
{
    model.select();
}

