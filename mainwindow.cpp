#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cfg(QApplication::applicationDirPath() + "/consistent.ini", QSettings::IniFormat, this)
    , timer(new QTimer(this))
{
    ui->setupUi(this);

#ifdef _WIN64
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setAttribute(Qt::WA_QuitOnClose);
#else
    this->setWindowFlags(Qt::FramelessWindowHint); // On Ubuntu, if xcb enabled, Qt::Tool blocks window creation.
#endif

    QRect screenGeometry = QApplication::primaryScreen()->geometry();
#ifdef _WIN64
    this->move(screenGeometry.width()-this->width()-15, 15);
#else
    this->move(screenGeometry.width()-this->width()-15, 45); // On Ubuntu, goes down a little bit to prevent collition with title bar.
#endif
    this->setFixedHeight(150);

    cfg.beginGroup("app");
        if(!cfg.contains("TargetDate")) cfg.setValue("TargetDate", QDate(2025,6,7));
        tdate = cfg.value("TargetDate").toDate();

        if(!cfg.contains("Translucent")) cfg.setValue("Translucent", true);
        bool translucent = cfg.value("Translucent").toBool();

        if(!cfg.contains("TargetString")) cfg.setValue("TargetString", "距离高考还剩：");
        QString text = cfg.value("TargetString").toString();

        if(!cfg.contains("Timer")) cfg.setValue("Timer", true);
        etimer = cfg.value("Timer").toBool();
    cfg.endGroup();

    cfg.beginGroup("widget");
        if(!cfg.contains("Stylesheet"))
            cfg.setValue("Stylesheet", ".QWidget{ background-color: rgba(255,255,255,180); border-radius: 10px; } .QLabel{ color: black; } .QPushButton:checked{ color: green; }");
        QString stylesheet = cfg.value("Stylesheet").toString();
    cfg.endGroup();

    ui->btnTranslucent->setChecked(translucent);
    if(translucent) this->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelName->setText(text);
    ui->centralwidget->setStyleSheet(stylesheet);

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
        cfg.beginGroup("app");
        cfg.setValue("Translucent", checked);
        cfg.endGroup();
    });

    trayicon = new QSystemTrayIcon(this);
    traymenu = new QMenu(this);

    trayicon->setIcon(QIcon(":/imp/settings.png"));
    trayicon->setToolTip("Countdown");
    trayicon->setContextMenu(traymenu);

#ifdef _WIN64
    QAction *acOpen = new QAction("Config", traymenu);
    connect(acOpen, &QAction::triggered, this, [=](){
        QProcess::startDetached("explorer", QStringList(QString("/select," + QApplication::applicationDirPath() + "consistent.ini")));
    });
    traymenu->addAction(acOpen);
    traymenu->addSeparator();
#endif

    QAction *acQuit = new QAction("Quit", traymenu);
    connect(acQuit, &QAction::triggered, this, [=](){this->close();});
    traymenu->addAction(acQuit);

    trayicon->show();

    if(etimer) connect(timer, &QTimer::timeout, this, &MainWindow::onDateChange);
    onDateChange();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDateChange()
{
    ui->count->setText(QString::number(QDate::currentDate().daysTo(tdate)));
    if(etimer) startTimer();
}

void MainWindow::onUserDateChange(QDate date)
{
    cfg.beginGroup("app");
    cfg.setValue("TargetDate", date);
    cfg.endGroup();
    tdate = date;
    onDateChange();
}

void MainWindow::startTimer()
{
    QDateTime now = QDateTime::currentDateTime();
    QDateTime nextMidnight = QDateTime(now.date().addDays(1), QTime(0,0,0,100));

    qint64 msecsToMidnight = now.msecsTo(nextMidnight);

    timer->start(msecsToMidnight);
}
