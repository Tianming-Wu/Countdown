#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cfg(QApplication::applicationDirPath() + "/consistent.ini", QSettings::IniFormat, this)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setAttribute(Qt::WA_QuitOnClose);
    //this->setAttribute(Qt::WA_TranslucentBackground);

    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    this->move(screenGeometry.width()-this->width()-15, 15);
    this->setFixedHeight(150);

    cfg.beginGroup("app");
        QDate tdate = cfg.value("TargetDate", QDate(2025,6,7)).toDate();
        bool translucent = cfg.value("Translucent", false).toBool();

        if(!cfg.contains("TargetName")) cfg.setValue("TargetName", "高考");
        QString text = "距离" + cfg.value("TargetName", "高考").toString() + "还剩:";
    cfg.endGroup();

    cfg.beginGroup("widget");
        if(!cfg.contains("Stylesheet"))
            cfg.setValue("Stylesheet", ".QWidget{ background-color: white; border-radius: 10px; }");
        QString stylesheet = cfg.value("Stylesheet").toString();
    cfg.endGroup();

    onDateChange(tdate);
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
    cfg.beginGroup("app");
    cfg.setValue("TargetDate", date);
    cfg.endGroup();
    ui->count->setText(QString::number(QDate::currentDate().daysTo(date)));
}
