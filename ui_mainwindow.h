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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *loginPage;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *labelTitle;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditUserName;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEditPassWord;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushButtonLogin;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *pushButtonRegister;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QWidget *functionPage;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_8;
    QLabel *labelWelcome;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButtonUploadFunction;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButtonCloudFunction;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_41;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *pushButtonManageFunction;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButtonLogout;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_9;
    QWidget *uploadPage;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_3;
    QListView *listViewUpload;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButtonSelectFile;
    QPushButton *pushButtonUpload;
    QPushButton *pushButtonBackFromUpload;
    QWidget *cloudPage;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_4;
    QLabel *label_5;
    QListView *listViewCloud;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButtonFlush;
    QPushButton *pushButtonBackFromCloud;
    QWidget *managePage;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_6;
    QListView *listViewManage;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButtonDownload;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonShare;
    QPushButton *pushButtonCancelShare;
    QPushButton *pushButtonBackFromManage;
    QStatusBar *statusbar;
    QWidget *sharePage;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_7;
    QListView *listViewShare;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *pushButtonFlushShare;
    QPushButton *pushButtonCollect;
    QPushButton *pushButtonBackFromShare;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *pushButtonShareFunction;
    QSpacerItem *horizontalSpacer_15;
    QSpacerItem *verticalSpacer_10;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(516, 461);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        loginPage = new QWidget();
        loginPage->setObjectName("loginPage");
        verticalLayout_2 = new QVBoxLayout(loginPage);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        labelTitle = new QLabel(loginPage);
        labelTitle->setObjectName("labelTitle");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        labelTitle->setFont(font);
        labelTitle->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(labelTitle);

        verticalSpacer_7 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(15);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(loginPage);
        label->setObjectName("label");
        label->setMinimumSize(QSize(80, 30));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        label->setFont(font1);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        lineEditUserName = new QLineEdit(loginPage);
        lineEditUserName->setObjectName("lineEditUserName");
        lineEditUserName->setMinimumSize(QSize(220, 35));
        QFont font2;
        font2.setPointSize(11);
        lineEditUserName->setFont(font2);

        horizontalLayout->addWidget(lineEditUserName);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(loginPage);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(80, 30));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        lineEditPassWord = new QLineEdit(loginPage);
        lineEditPassWord->setObjectName("lineEditPassWord");
        lineEditPassWord->setMinimumSize(QSize(220, 35));
        lineEditPassWord->setFont(font2);
        lineEditPassWord->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(lineEditPassWord);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        pushButtonLogin = new QPushButton(loginPage);
        pushButtonLogin->setObjectName("pushButtonLogin");
        pushButtonLogin->setMinimumSize(QSize(100, 40));
        pushButtonLogin->setFont(font1);
        pushButtonLogin->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 170, 255);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(pushButtonLogin);

        horizontalSpacer_10 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);

        pushButtonRegister = new QPushButton(loginPage);
        pushButtonRegister->setObjectName("pushButtonRegister");
        pushButtonRegister->setMinimumSize(QSize(100, 40));
        pushButtonRegister->setFont(font1);
        pushButtonRegister->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 0);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(pushButtonRegister);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_11);


        verticalLayout_3->addLayout(horizontalLayout_4);


        horizontalLayout_3->addLayout(verticalLayout_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        stackedWidget->addWidget(loginPage);
        functionPage = new QWidget();
        functionPage->setObjectName("functionPage");
        verticalLayout_4 = new QVBoxLayout(functionPage);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalSpacer_8 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_8);

        labelWelcome = new QLabel(functionPage);
        labelWelcome->setObjectName("labelWelcome");
        QFont font3;
        font3.setPointSize(14);
        font3.setBold(true);
        labelWelcome->setFont(font3);
        labelWelcome->setStyleSheet(QString::fromUtf8("color: rgb(60, 60, 60);"));
        labelWelcome->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(labelWelcome);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        pushButtonUploadFunction = new QPushButton(functionPage);
        pushButtonUploadFunction->setObjectName("pushButtonUploadFunction");
        pushButtonUploadFunction->setMinimumSize(QSize(180, 60));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        pushButtonUploadFunction->setFont(font4);

        horizontalLayout_5->addWidget(pushButtonUploadFunction);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_5);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        pushButtonCloudFunction = new QPushButton(functionPage);
        pushButtonCloudFunction->setObjectName("pushButtonCloudFunction");
        pushButtonCloudFunction->setMinimumSize(QSize(180, 60));
        pushButtonCloudFunction->setFont(font4);

        horizontalLayout_6->addWidget(pushButtonCloudFunction);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        verticalLayout_4->addLayout(horizontalLayout_6);

        verticalSpacer_41 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_41);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_12);

        pushButtonManageFunction = new QPushButton(functionPage);
        pushButtonManageFunction->setObjectName("pushButtonManageFunction");
        pushButtonManageFunction->setMinimumSize(QSize(180, 60));
        pushButtonManageFunction->setFont(font4);

        horizontalLayout_11->addWidget(pushButtonManageFunction);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_13);


        verticalLayout_4->addLayout(horizontalLayout_11);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_14);

        pushButtonShareFunction = new QPushButton(functionPage);
        pushButtonShareFunction->setObjectName("pushButtonShareFunction");
        pushButtonShareFunction->setMinimumSize(QSize(180, 60));
        pushButtonShareFunction->setFont(font4);

        horizontalLayout_13->addWidget(pushButtonShareFunction);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_15);


        verticalLayout_4->addLayout(horizontalLayout_13);
        
        verticalSpacer_10 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_10);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        pushButtonLogout = new QPushButton(functionPage);
        pushButtonLogout->setObjectName("pushButtonLogout");
        pushButtonLogout->setMinimumSize(QSize(120, 40));
        pushButtonLogout->setFont(font1);

        horizontalLayout_7->addWidget(pushButtonLogout);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);


        verticalLayout_4->addLayout(horizontalLayout_7);

        verticalSpacer_9 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_9);

        stackedWidget->addWidget(functionPage);
        uploadPage = new QWidget();
        uploadPage->setObjectName("uploadPage");
        verticalLayout_5 = new QVBoxLayout(uploadPage);
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_3 = new QLabel(uploadPage);
        label_3->setObjectName("label_3");
        label_3->setFont(font4);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(60, 60, 60);"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_3);

        listViewUpload = new QListView(uploadPage);
        listViewUpload->setObjectName("listViewUpload");
        QFont font5;
        font5.setPointSize(10);
        listViewUpload->setFont(font5);
        listViewUpload->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_5->addWidget(listViewUpload);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        pushButtonSelectFile = new QPushButton(uploadPage);
        pushButtonSelectFile->setObjectName("pushButtonSelectFile");
        pushButtonSelectFile->setMinimumSize(QSize(0, 40));
        QFont font6;
        font6.setPointSize(10);
        font6.setBold(true);
        pushButtonSelectFile->setFont(font6);

        horizontalLayout_8->addWidget(pushButtonSelectFile);

        pushButtonUpload = new QPushButton(uploadPage);
        pushButtonUpload->setObjectName("pushButtonUpload");
        pushButtonUpload->setMinimumSize(QSize(0, 40));
        pushButtonUpload->setFont(font6);

        horizontalLayout_8->addWidget(pushButtonUpload);

        pushButtonBackFromUpload = new QPushButton(uploadPage);
        pushButtonBackFromUpload->setObjectName("pushButtonBackFromUpload");
        pushButtonBackFromUpload->setMinimumSize(QSize(0, 40));
        pushButtonBackFromUpload->setFont(font6);

        horizontalLayout_8->addWidget(pushButtonBackFromUpload);


        verticalLayout_5->addLayout(horizontalLayout_8);

        stackedWidget->addWidget(uploadPage);
        cloudPage = new QWidget();
        cloudPage->setObjectName("cloudPage");
        verticalLayout_6 = new QVBoxLayout(cloudPage);
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_4 = new QLabel(cloudPage);
        label_4->setObjectName("label_4");
        label_4->setFont(font4);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(60, 60, 60);"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_4);

        label_5 = new QLabel(cloudPage);
        label_5->setObjectName("label_5");
        QFont font7;
        font7.setPointSize(9);
        font7.setItalic(true);
        label_5->setFont(font7);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(100, 100, 100);"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_5);

        listViewCloud = new QListView(cloudPage);
        listViewCloud->setObjectName("listViewCloud");
        listViewCloud->setFont(font5);
        listViewCloud->setContextMenuPolicy(Qt::CustomContextMenu);
        listViewCloud->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_6->addWidget(listViewCloud);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        pushButtonFlush = new QPushButton(cloudPage);
        pushButtonFlush->setObjectName("pushButtonFlush");
        pushButtonFlush->setMinimumSize(QSize(0, 40));
        pushButtonFlush->setFont(font6);

        horizontalLayout_9->addWidget(pushButtonFlush);

        pushButtonBackFromCloud = new QPushButton(cloudPage);
        pushButtonBackFromCloud->setObjectName("pushButtonBackFromCloud");
        pushButtonBackFromCloud->setMinimumSize(QSize(0, 40));
        pushButtonBackFromCloud->setFont(font6);

        horizontalLayout_9->addWidget(pushButtonBackFromCloud);


        verticalLayout_6->addLayout(horizontalLayout_9);

        stackedWidget->addWidget(cloudPage);
        managePage = new QWidget();
        managePage->setObjectName("managePage");
        verticalLayout_7 = new QVBoxLayout(managePage);
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_6 = new QLabel(managePage);
        label_6->setObjectName("label_6");
        label_6->setFont(font4);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(60, 60, 60);"));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label_6);

        listViewManage = new QListView(managePage);
        listViewManage->setObjectName("listViewManage");
        listViewManage->setFont(font5);
        listViewManage->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_7->addWidget(listViewManage);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        pushButtonDownload = new QPushButton(managePage);
        pushButtonDownload->setObjectName("pushButtonDownload");
        pushButtonDownload->setMinimumSize(QSize(0, 40));
        pushButtonDownload->setFont(font6);

        horizontalLayout_10->addWidget(pushButtonDownload);

        pushButtonDelete = new QPushButton(managePage);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setMinimumSize(QSize(0, 40));
        pushButtonDelete->setFont(font6);

        horizontalLayout_10->addWidget(pushButtonDelete);

        pushButtonShare = new QPushButton(managePage);
        pushButtonShare->setObjectName("pushButtonShare");
        pushButtonShare->setMinimumSize(QSize(0, 40));
        pushButtonShare->setFont(font6);

        horizontalLayout_10->addWidget(pushButtonShare);
        
        pushButtonCancelShare = new QPushButton(managePage);
        pushButtonCancelShare->setObjectName("pushButtonCancelShare");
        pushButtonCancelShare->setMinimumSize(QSize(0, 40));
        pushButtonCancelShare->setFont(font6);

        horizontalLayout_10->addWidget(pushButtonCancelShare);

        pushButtonBackFromManage = new QPushButton(managePage);
        pushButtonBackFromManage->setObjectName("pushButtonBackFromManage");
        pushButtonBackFromManage->setMinimumSize(QSize(0, 40));
        pushButtonBackFromManage->setFont(font6);

        horizontalLayout_10->addWidget(pushButtonBackFromManage);


        verticalLayout_7->addLayout(horizontalLayout_10);

        stackedWidget->addWidget(managePage);
        
        sharePage = new QWidget();
        sharePage->setObjectName("sharePage");
        verticalLayout_8 = new QVBoxLayout(sharePage);
        verticalLayout_8->setObjectName("verticalLayout_8");
        label_7 = new QLabel(sharePage);
        label_7->setObjectName("label_7");
        label_7->setFont(font4);
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(60, 60, 60);"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(label_7);

        listViewShare = new QListView(sharePage);
        listViewShare->setObjectName("listViewShare");
        listViewShare->setFont(font5);
        listViewShare->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_8->addWidget(listViewShare);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        pushButtonFlushShare = new QPushButton(sharePage);
        pushButtonFlushShare->setObjectName("pushButtonFlushShare");
        pushButtonFlushShare->setMinimumSize(QSize(0, 40));
        pushButtonFlushShare->setFont(font6);

        horizontalLayout_12->addWidget(pushButtonFlushShare);

        pushButtonCollect = new QPushButton(sharePage);
        pushButtonCollect->setObjectName("pushButtonCollect");
        pushButtonCollect->setMinimumSize(QSize(0, 40));
        pushButtonCollect->setFont(font6);

        horizontalLayout_12->addWidget(pushButtonCollect);

        pushButtonBackFromShare = new QPushButton(sharePage);
        pushButtonBackFromShare->setObjectName("pushButtonBackFromShare");
        pushButtonBackFromShare->setMinimumSize(QSize(0, 40));
        pushButtonBackFromShare->setFont(font6);

        horizontalLayout_12->addWidget(pushButtonBackFromShare);


        verticalLayout_8->addLayout(horizontalLayout_12);

        stackedWidget->addWidget(sharePage);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\345\233\276\347\211\207\344\272\221\345\255\230\345\202\250\347\263\273\347\273\237", nullptr));
        labelTitle->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\345\233\276\347\211\207\344\272\221\345\255\230\345\202\250\347\263\273\347\273\237", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\257\206   \347\240\201\357\274\232", nullptr));
        pushButtonLogin->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        pushButtonRegister->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        labelWelcome->setText(QCoreApplication::translate("MainWindow", "\346\254\242\350\277\216\344\275\277\347\224\250\357\274\214\350\257\267\351\200\211\346\213\251\345\212\237\350\203\275\357\274\232", nullptr));
        pushButtonUploadFunction->setText(QCoreApplication::translate("MainWindow", "\345\233\276\347\211\207\344\270\212\344\274\240\345\212\237\350\203\275", nullptr));
        pushButtonCloudFunction->setText(QCoreApplication::translate("MainWindow", "\344\272\221\347\253\257\345\233\276\347\211\207\351\242\204\350\247\210", nullptr));
        pushButtonManageFunction->setText(QCoreApplication::translate("MainWindow", "\344\272\221\347\253\257\345\233\276\347\211\207\347\256\241\347\220\206", nullptr));
        pushButtonShareFunction->setText(QCoreApplication::translate("MainWindow", "\345\205\261\344\272\253\345\233\276\347\211\207\345\271\263\345\217\260", nullptr));
        pushButtonLogout->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\276\205\344\270\212\344\274\240\345\233\276\347\211\207\345\210\227\350\241\250", nullptr));
        pushButtonSelectFile->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        pushButtonUpload->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\274\240", nullptr));
        pushButtonBackFromUpload->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\344\272\221\347\253\257\345\233\276\347\211\207\345\210\227\350\241\250", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\346\217\220\347\244\272\357\274\232\345\217\214\345\207\273\344\270\213\350\275\275\345\233\276\347\211\207\357\274\214\345\217\263\351\224\256\345\210\240\351\231\244\345\233\276\347\211\207", nullptr));
        pushButtonFlush->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        pushButtonBackFromCloud->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\344\272\221\347\253\257\345\233\276\347\211\207\347\256\241\347\220\206", nullptr));
        pushButtonDownload->setText(QCoreApplication::translate("MainWindow", "\344\270\213\350\275\275", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        pushButtonShare->setText(QCoreApplication::translate("MainWindow", "\345\210\206\344\272\253", nullptr));
        pushButtonCancelShare->setText(QCoreApplication::translate("MainWindow", "\345\217\226\346\266\210\345\210\206\344\272\253", nullptr));
        pushButtonBackFromManage->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\345\205\261\344\272\253\345\233\276\347\211\207\345\271\263\345\217\260", nullptr));
        pushButtonFlushShare->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        pushButtonCollect->setText(QCoreApplication::translate("MainWindow", "\346\224\266\350\227\217", nullptr));
        pushButtonBackFromShare->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
