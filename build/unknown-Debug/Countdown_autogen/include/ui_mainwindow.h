/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QPushButton *settings;
    QLabel *label_2;
    QLabel *count;
    QLabel *label;
    QDateEdit *dateEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(323, 184);
        MainWindow->setContextMenuPolicy(Qt::NoContextMenu);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(323, 184));
        widget->setMaximumSize(QSize(323, 184));
        widget->setStyleSheet(QString::fromUtf8(".widget {\n"
"	background-color: white;\n"
"	border-radius: 10px;\n"
"}"));
        settings = new QPushButton(widget);
        settings->setObjectName("settings");
        settings->setGeometry(QRect(20, 140, 25, 25));
        settings->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background: transparent;\n"
"	border: none\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/imp/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        settings->setIcon(icon);
        settings->setIconSize(QSize(25, 25));
        settings->setCheckable(true);
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(280, 110, 21, 21));
        QFont font;
        font.setPointSize(14);
        label_2->setFont(font);
        count = new QLabel(widget);
        count->setObjectName("count");
        count->setGeometry(QRect(60, 40, 201, 96));
        QFont font1;
        font1.setPointSize(64);
        count->setFont(font1);
        count->setAlignment(Qt::AlignCenter);
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(19, 9, 131, 21));
        label->setMaximumSize(QSize(16777215, 21));
        label->setFont(font);
        dateEdit = new QDateEdit(widget);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(60, 140, 110, 26));
        dateEdit->setDateTime(QDateTime(QDate(2025, 6, 7), QTime(8, 0, 0)));
        dateEdit->setDate(QDate(2025, 6, 7));

        verticalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QString());
        settings->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\244\251", nullptr));
        count->setText(QCoreApplication::translate("MainWindow", "999", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\267\235\347\246\273\351\253\230\350\200\203\350\277\230\345\211\251\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
