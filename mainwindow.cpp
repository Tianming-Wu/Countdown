#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cfg(QApplication::applicationDirPath() + "/consistent.ini", QSettings::IniFormat, this)
{
    ui->setupUi(this);

#ifdef _WIN64
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setAttribute(Qt::WA_QuitOnClose);
#else
    this->setWindowFlags(Qt::FramelessWindowHint); // On Ubuntu, if xcb enabled, Qt::Tool blocks window creation.
#endif

    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    QPoint winpos;
#ifdef _WIN64
    winpos = QPoint(screenGeometry.width()-this->width()-15, 15);
#else
    winpos = QPoint(screenGeometry.width()-this->width()-15, 45); // On Ubuntu, goes down a little bit to prevent collition with title bar.
#endif
    this->move(winpos);

    cfg.beginGroup("app");
        if(!cfg.contains("TargetDate")) cfg.setValue("TargetDate", QDate(2025,6,7).toString(Qt::ISODate));
        tdate = QDate::fromString(cfg.value("TargetDate").toString(), Qt::ISODate);

        if(!cfg.contains("Translucent")) cfg.setValue("Translucent", true);
        bool translucent = cfg.value("Translucent").toBool();

        if(!cfg.contains("TargetString")) cfg.setValue("TargetString", "距离高考还剩：");
        QString text = cfg.value("TargetString").toString();

        if(!cfg.contains("Timer")) cfg.setValue("Timer", true);
        etimer = cfg.value("Timer").toBool();

        if(!cfg.contains("Animation")) cfg.setValue("Animation", true);
        bool animation = cfg.value("Animation").toBool();
    cfg.endGroup();

    cfg.beginGroup("widget");
        if(!cfg.contains("Stylesheet"))
            cfg.setValue("Stylesheet", ".QWidget{ background-color: rgba(255,255,255,180); border-radius: 10px; } QLabel{ color: black; } .QPushButton:checked{ color: green; }");
        QString stylesheet = cfg.value("Stylesheet").toString();

        if(!cfg.contains("gradient_enabled"))
            cfg.setValue("gradient_enabled", false);
        bool gradientEnabled = cfg.value("gradient_enabled", false).toBool();

        if(!cfg.contains("gradient_colors"))
            cfg.setValue("gradient_colors", "#FF0000:0,#FF3300:0.08,#FF6600:0.16,#FF9900:0.25,#FFCC00:0.33,#FFFF00:0.41,#99FF00:0.5,#33FF00:0.58,#00FF66:0.66,#00FFFF:0.75,#0066FF:0.83,#CC00FF:0.91,#FF00FF:1");
        QString gradientStops = cfg.value("gradient_colors").toString();

        if(!cfg.contains("gradient_angle"))
            cfg.setValue("gradient_angle", 30);
        int angle = cfg.value("gradient_angle", 30).toInt();

        if(!cfg.contains("gradient_labels"))
            cfg.setValue("gradient_labels", "count");
        QStringList gradientLabels = cfg.value("gradient_labels")
                                         .toString().split(',', Qt::SkipEmptyParts);
    cfg.endGroup();

    ui->btnTranslucent->setChecked(translucent);
    if(translucent) this->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelName->setText(text);
    ui->centralwidget->setStyleSheet(stylesheet);
    if(etimer) timer = new QTimer(this);

    // 应用渐变效果
    if(gradientEnabled) {
        foreach (QString labelName, gradientLabels) {
            GradientLabel *label = findChild<GradientLabel*>(labelName);
            if (label) {
                label->setGradientEnabled(true);
                label->setGradientAngle(angle);

                if (!gradientStops.isEmpty()) {
                    QGradientStops stops;
                    foreach (QString stop, gradientStops.split(',')) {
                        QStringList parts = stop.split(':');
                        if (parts.size() == 2) {
                            stops << QGradientStop(parts[1].toDouble(), QColor(parts[0]));
                        }
                    }
                    label->setGradientStops(stops);
                }
            }
        }
    }

    // ui->dateEdit->hide();
    // ui->btnTranslucent->hide();

    connect(ui->settings, &QPushButton::toggled, this, [=](bool checked) {
        if(checked) {
            if(animation) pa_expand->start();
            else this->setFixedHeight(184);
            // ui->dateEdit->show(); ui->btnTranslucent->show();
        } else {
            if(animation) pa_shrink->start();
            else this->setFixedHeight(150);
            // ui->dateEdit->hide(); ui->btnTranslucent->hide();
        }
    });

    connect(ui->dateEdit, &QDateEdit::userDateChanged, this, &MainWindow::onUserDateChange);

    connect(ui->btnTranslucent, &QPushButton::toggled, this, [=](bool checked) {
        cfg.setValue("app/Translucent", checked);
    });

    connect(ui->labelAbout, &QLabel::linkActivated, this, [=](QString s) {
        QMessageBox::aboutQt(nullptr, s);
    });

    if(animation) {
        pa_appear = new QPropertyAnimation(this, "pos", this);
        pa_expand = new QPropertyAnimation(this, "geometry", this);
        pa_shrink = new QPropertyAnimation(this, "geometry", this);

        pa_appear->setStartValue(QPoint(winpos.x(), winpos.y()-180));
        pa_appear->setEndValue(winpos);
        pa_appear->setEasingCurve(QEasingCurve::OutCubic);

        pa_expand->setStartValue(QRect(winpos, QSize(323, 150)));
        pa_expand->setEndValue(QRect(winpos, QSize(323, 183)));
        pa_expand->setEasingCurve(QEasingCurve::OutCubic);
        pa_expand->setDuration(200);

        pa_shrink->setStartValue(QRect(winpos, QSize(323, 183)));
        pa_shrink->setEndValue(QRect(winpos, QSize(323, 150)));
        pa_shrink->setEasingCurve(QEasingCurve::InCubic);
        pa_shrink->setDuration(200);
    }

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

    if(animation) pa_appear->start(QAbstractAnimation::DeleteWhenStopped);
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
    cfg.setValue("TargetDate", date.toString(Qt::ISODate));
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
