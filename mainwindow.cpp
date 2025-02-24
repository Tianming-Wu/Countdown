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
    //ui->widget->setAttribute(Qt::WA_TranslucentBackground, false);

    // QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    // effect->setBlurRadius(20);
    // effect->setOffset(0);
    // effect->setColor(QColor(0, 0, 0, 160));
    // ui->widget->setGraphicsEffect(effect);

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

    QAction *acQuit = new QAction("Quit", trayicon);
    connect(acQuit, &QAction::triggered, this, [=](){this->close();});
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
