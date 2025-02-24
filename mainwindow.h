#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QSettings>
#include <QGraphicsDropShadowEffect>

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
    void onDateChange(QDate);

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *trayicon;
    QMenu *traymenu;
    QSettings cfg;
};
#endif // MAINWINDOW_H
