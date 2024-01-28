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

//    QString params;
//    params = "insert into dxcc (Dxcc, Prefix, Entity, Deleted, Mix, Ph, CW, RT, SAT, m160, m80, m40, m20, m17, m15, m12, m10, m6, m2, cm70, Comment) values(%1, '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', '%14', '%15', '%16', '%17', '%19', '%19', '%20', '%21')";
//    params = params.arg(246).arg("1A").arg("Sov. Mil. Order of Malta").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("");
//    qDebug() << params;
//    query.exec(params);
//    qDebug() << query.lastError();
    model.select();
}

MainWindow::~MainWindow()
{
    delete ui;
}

