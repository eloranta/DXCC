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
    ReadAdif();

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
            qDebug() << mode;
        }
        rx.setPattern("<BAND:\\d+>(.+)\\n");
        match = rx.match(line);
        if (match.hasMatch())
        {
            band = match.captured(1);
            qDebug() << band;
        }
        rx.setPattern("<DXCC:\\d+>(.+)\\n");
        match = rx.match(line);
        if (match.hasMatch())
        {
            dxcc = match.captured(1);
            qDebug() << dxcc;
        }

        // rx.setPattern("<COUNTRY:\\d+>(.+)\\n");
        // match = rx.match(line);
        // if (match.hasMatch())
        // {
        //     country = match.captured(1);
        //     //            qDebug() << dxcc << country;

        //     Qso qso;
        //     if(map.find(dxcc) != map.end())
        //         qso = map[dxcc];

        //     qso.setValues(country, mode, band);
        //     map[dxcc] = qso;
        // }
    }
    file.close();
}
