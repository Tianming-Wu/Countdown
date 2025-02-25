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
    this->setFixedHeight(150);

    cfg.beginGroup("app");
    QDate tdate = cfg.value("TargetDate", QDate(2025,6,7)).toDate();
    bool translucent = cfg.value("Translucent", false).toBool();

    onDateChange(tdate);
    ui->btnTranslucent->setChecked(translucent);
    if(translucent) this->setAttribute(Qt::WA_TranslucentBackground);

    ui->dateEdit->hide();
    ui->btnTranslucent->hide();

    connect(ui->settings, &QPushButton::toggled, this, [=](bool checked) {
        if(checked) {
            this->setFixedHeight(184);
            ui->dateEdit->show(); ui->btnTranslucent->show();
        } else {
            this->setFixedHeight(150);
            ui->dateEdit->hide(); ui->btnTranslucent->hide();
        }
    });

    connect(ui->dateEdit, &QDateEdit::userDateChanged, this, &MainWindow::onDateChange);

    connect(ui->btnTranslucent, &QPushButton::toggled, this, [=](bool checked) {
        cfg.setValue("Translucent", checked);
        if(checked) {
            this->setAttribute(Qt::WA_TranslucentBackground);
        } else {
            this->setAttribute(Qt::WA_TranslucentBackground, false);
        }
    });

    trayicon = new QSystemTrayIcon(this);
    traymenu = new QMenu(this);

    trayicon->setIcon(QIcon(":/imp/calendar.png"));
    trayicon->setToolTip("Countdown");
    trayicon->setContextMenu(traymenu);

#ifdef _WIN64
    QAction *acOpen = new QAction("Config", traymenu);
    connect(acOpen, &QAction::triggered, this, [=](){
        QProcess::startDetached("explorer", QStringList("/select,consistent.ini"));
    });
    traymenu->addAction(acOpen);
    traymenu->addSeparator();
#endif

    QAction *acQuit = new QAction("Quit", traymenu);
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
