#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QSettings>
#include <QGraphicsDropShadowEffect>
#include <QScreen>
#include <QProcess>
#include <QTimer>
#include <QPropertyAnimation>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onUserDateChange(QDate);
    void onDateChange();

private:
    void startTimer();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *trayicon;
    QMenu *traymenu;
    QSettings cfg;
    QTimer *timer;

    bool etimer;
    QDate tdate;

    QPropertyAnimation *pa_appear, *pa_expand, *pa_shrink;
};
#endif // MAINWINDOW_H
