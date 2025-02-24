#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cfg("./consistent.ini", QSettings::IniFormat, this)
{
    ui->setupUi(this);

    //this->setWindowFlags(Qt::Tool);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground);

    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    this->move(screenGeometry.width()-this->width()-15, 15);

    cfg.beginGroup("app");
    QDate tdate = cfg.value("TargetDate", QDate(2025,6,7)).toDate();

    onDateChange(tdate);
    ui->dateEdit->hide();

    connect(ui->settings, &QPushButton::toggled, this, [=](bool checked) {
        if(checked)
            ui->dateEdit->show();
        else
            ui->dateEdit->hide();
    });

    connect(ui->dateEdit, &QDateEdit::userDateChanged, this, &MainWindow::onDateChange);

    trayicon = new QSystemTrayIcon(this);
    traymenu = new QMenu(this);

    trayicon->setIcon(QIcon(":/imp/calendar.png"));
    trayicon->setToolTip("Countdown");
    trayicon->setContextMenu(traymenu);

    QAction *acQuit = new QAction("Quit", traymenu);
    QAction *acRfPos = new QAction("Re move", traymenu);
    connect(acQuit, &QAction::triggered, this, [=](){this->close();});
    connect(acRfPos, &QAction::triggered, this, [=](){
        QRect screenGeometry = QApplication::primaryScreen()->geometry();
        this->move(screenGeometry.width()-this->width()-15, 15);
    });

    traymenu->addAction(acRfPos);
    traymenu->addSeparator();
    traymenu->addAction(acQuit);

    trayicon->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDateChange(QDate date)
{
    cfg.setValue("TargetDate", date);
    ui->count->setText(QString::number(QDate::currentDate().daysTo(date)));
}
