/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_3;
    QLabel *label_4;
    QListView *listViewUpload;
    QListView *listViewCloud;
    QPushButton *pushButtonUpload;
    QPushButton *pushButtonFlush;
    QPushButton *pushButtonSelectFile;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditUserName;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEditPassWord;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonLogin;
    QPushButton *pushButtonRegister;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(516, 461);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 120, 71, 21));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(270, 120, 71, 21));
        listViewUpload = new QListView(centralwidget);
        listViewUpload->setObjectName("listViewUpload");
        listViewUpload->setGeometry(QRect(30, 150, 211, 211));
        listViewCloud = new QListView(centralwidget);
        listViewCloud->setObjectName("listViewCloud");
        listViewCloud->setGeometry(QRect(270, 150, 211, 211));
        listViewCloud->setContextMenuPolicy(Qt::NoContextMenu);
        listViewCloud->setEditTriggers(QAbstractItemView::NoEditTriggers);
        pushButtonUpload = new QPushButton(centralwidget);
        pushButtonUpload->setObjectName("pushButtonUpload");
        pushButtonUpload->setGeometry(QRect(150, 380, 75, 23));
        pushButtonFlush = new QPushButton(centralwidget);
        pushButtonFlush->setObjectName("pushButtonFlush");
        pushButtonFlush->setGeometry(QRect(410, 380, 75, 23));
        pushButtonSelectFile = new QPushButton(centralwidget);
        pushButtonSelectFile->setObjectName("pushButtonSelectFile");
        pushButtonSelectFile->setGeometry(QRect(40, 380, 75, 23));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(30, 20, 451, 81));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEditUserName = new QLineEdit(layoutWidget);
        lineEditUserName->setObjectName("lineEditUserName");

        horizontalLayout->addWidget(lineEditUserName);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        lineEditPassWord = new QLineEdit(layoutWidget);
        lineEditPassWord->setObjectName("lineEditPassWord");

        horizontalLayout_2->addWidget(lineEditPassWord);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        pushButtonLogin = new QPushButton(layoutWidget);
        pushButtonLogin->setObjectName("pushButtonLogin");

        verticalLayout->addWidget(pushButtonLogin);

        pushButtonRegister = new QPushButton(layoutWidget);
        pushButtonRegister->setObjectName("pushButtonRegister");

        verticalLayout->addWidget(pushButtonRegister);


        horizontalLayout_3->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 516, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\276\205\344\270\212\344\274\240\345\210\227\350\241\250\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\344\272\221\347\253\257\345\210\227\350\241\250\357\274\232", nullptr));
        pushButtonUpload->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\274\240", nullptr));
        pushButtonFlush->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        pushButtonSelectFile->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\257\206   \347\240\201\357\274\232", nullptr));
        pushButtonLogin->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        pushButtonRegister->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
