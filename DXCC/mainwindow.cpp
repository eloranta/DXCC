#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlQuery query;
    query.exec(QString("create table if not exists dxcc ("
        "Dxcc integer,"
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

    //ReadDxccFile();
    //ReadAdif();

    model.select();
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(Update()));
}

void MainWindow::ReadDxccFile()
{
    QFile file(qApp->applicationDirPath() + "/dxcc.out");
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", file.errorString());
        return;
    }

    QSqlQuery query;
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        QString params;
        params = "insert into dxcc (Dxcc, Prefix, Entity, Deleted, Mix, Ph, CW, RT, SAT, m160, m80, m40, m20, m17, m15, m12, m10, m6, m2, cm70, Comment) values('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', '%14', '%15', '%16', '%17', '%19', '%19', '%20', '%21')";
        params = params.arg(fields[0].toInt()).arg(fields[1]).arg(fields[2]).arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("").arg("");
        query.exec(params);
    }

file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Update()
{
    model.select();
}

void MainWindow::ReadAdif()
{
    QString jsonFile = qApp->applicationDirPath() + "/QSL.adi";
    QFile file;
    file.setFileName(jsonFile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    const long long MAX_LEN = 500;
    char data[MAX_LEN];
    long long len;
    QString mode;
    QString country;
    QString band;
    QString dxcc;
    while ((len = file.readLine(data, MAX_LEN)) > 0)
    {
        data[len] = 0;
        QString line(data);
        QRegularExpression rx("<APP_LoTW_MODEGROUP:\\d+:S>(.+)\\n");
        QRegularExpressionMatch match = rx.match(line);
        if (match.hasMatch())
        {
            mode = match.captured(1);
            //qDebug() << mode;
        }
        rx.setPattern("<BAND:\\d+>(.+)\\n");
        match = rx.match(line);
        if (match.hasMatch())
        {
            band = match.captured(1);
            //qDebug() << band;
        }
        rx.setPattern("<DXCC:\\d+>(.+)\\n");
        match = rx.match(line);
        if (match.hasMatch())
        {
            dxcc = match.captured(1);
            //qDebug() << dxcc;
            WriteToDatabase(dxcc.toInt(), mode, band);
        }
    }
    file.close();
}

void MainWindow::WriteToDatabase(int dxcc, const QString& mode, const QString& band)
{
    qDebug() << dxcc << mode << band;

    QSqlQuery query;
    QString params = QString("UPDATE dxcc SET Mix = 'V' WHERE Dxcc = %1").arg(dxcc);
    query.exec(params);

    if (mode == "DATA")
        params = QString("UPDATE dxcc SET RT = 'V' WHERE Dxcc = %1").arg(dxcc);
    else if (mode == "CW")
        params = QString("UPDATE dxcc SET CW = 'V' WHERE Dxcc = %1").arg(dxcc);
    else if (mode == "PHONE")
        params = QString("UPDATE dxcc SET Ph = 'V' WHERE Dxcc = %1").arg(dxcc);
    else if (mode == "SAT")
        params = QString("UPDATE dxcc SET SAT = 'V' WHERE Dxcc = %1").arg(dxcc);
    query.exec(params);

    if (band == "160M")
        params = QString("UPDATE dxcc SET m160 = 'V' WHERE Dxcc = %1").arg(dxcc);
    else if (band == "80M")
        params = QString("UPDATE dxcc SET m80 = 'V' WHERE Dxcc = %1").arg(dxcc);
    else if (band == "40M")
        params = QString("UPDATE dxcc SET m40 = 'V' WHERE Dxcc = %1").arg(dxcc);
    else if (band == "30M")
        params = QString("UPDATE dxcc SET m30 = 'V' WHERE Dxcc = %1").arg(dxcc);
    else if (band == "20M")
        params = QString("UPDATE dxcc SET m20 = 'V' WHERE Dxcc = %1").arg(dxcc);
    else if (band == "17M")
        params = QString("UPDATE dxcc SET m17 = 'V' WHERE Dxcc = %1").arg(dxcc);
    else if (band == "15M")
        params = QString("UPDATE dxcc SET m15 = 'V' WHERE Dxcc = %1").arg(dxcc);
    else if (band == "12M")
        params = QString("UPDATE dxcc SET m12 = 'V' WHERE Dxcc = %1").arg(dxcc);
    else if (band == "10M")
        params = QString("UPDATE dxcc SET m10 = 'V' WHERE Dxcc = %1").arg(dxcc);
    else if (band == "6M")
        params = QString("UPDATE dxcc SET m6 = 'V' WHERE Dxcc = %1").arg(dxcc);
    else if (band == "2M")
        params = QString("UPDATE dxcc SET m2 = 'V' WHERE Dxcc = %1").arg(dxcc);
    query.exec(params);

}

