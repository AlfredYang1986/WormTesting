#include "mainwindow.h"
#include "titlewidget/titlewidget.h"
#include "starttesting/starttestingpage.h"
#include "reporting/reportingcontainer.h"
#include "reportlst/reportlstcontainer.h"
#include "pushwidget/pushwidget.h"
#include "sampleresource/sampleresourcecontainer.h"
#include "settingwiget/settingmainwidget.h"
#include "imgcomparewidget/imagecomparewidget.h"
#include <QMessageBox>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setUpSubviews();
}

MainWindow::~MainWindow() {
    center_widget->deleteLater();
    title_widget->deleteLater();
    main_container->deleteLater();

    map<QString, QFrame*>::iterator iter = contents.begin();
    for (; iter != contents.end(); ++iter) {
        ((*iter).second)->deleteLater();
    }
}

void MainWindow::setUpSubviews() {
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("MainWindow"));
    this->setWindowTitle(QStringLiteral("虫卵检测系统V1.0"));
    this->setWindowState(Qt::WindowMaximized);
    center_widget = new QWidget;
    center_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    center_widget->setObjectName(QStringLiteral("center_widget"));
    this->setCentralWidget(center_widget);
    center_widget->setContentsMargins(0,0,0,0);

    main_container = new QVBoxLayout;
    main_container->setContentsMargins(0, 0, 0, 0);

    title_widget = new titlewidget;
    title_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QObject::connect(title_widget, SIGNAL(changeContentPane(const QString&)), this, SLOT(changeMainContent(const QString&)));

    main_container->addWidget(title_widget);
//    this->createTestingWidget();
    this->createPushWidget();

    center_widget->setLayout(main_container);
}

void MainWindow::changeMainContent(const QString &title) {
    if (this->isReadyToChangeMainWidget()) {
        if (title == QStringLiteral("开始检测")) {
            this->createTestingWidget();
        } else if (title == QStringLiteral("填写报告")) {
            this->createReportWidget();
        } else if (title == QStringLiteral("报告列表")) {
            this->createReportLstWidget();
        } else if (title == QStringLiteral("录入样本")) {
            this->createPushWidget();
        } else if (title == QStringLiteral("样本资料")) {
            this->createResourceWidget();
        } else if (title == QStringLiteral("系统设置")) {
            this->createSettingWidget();
        } else if (title == QStringLiteral("对比结果")) {
            this->createCompareWidget();
        }
//        else {
//            this->createCompareWidget();
//        }
    }
}

 void MainWindow::createPushWidget() {
     map<QString, QFrame*>::iterator iter = contents.begin();
     for (; iter != contents.end(); ++iter) {
         QFrame* tmp = (*iter).second;
         if (tmp)
            tmp->hide();
     }

     QFrame* tmp = contents["录入样本"];
     if (tmp == NULL) {
         pushwidget* content_widget = new pushwidget;
         content_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

         main_container->addWidget(content_widget);
         contents[QStringLiteral("录入样本")] = content_widget;

         QObject::connect(content_widget, SIGNAL(startTesting(const QJsonObject&)),
                          this, SLOT(startTest(const QJsonObject&)));

         tmp = content_widget;
     }

     tmp->show();
 }

 void MainWindow::createTestingWidget() {

     map<QString, QFrame*>::iterator iter = contents.begin();
     for (; iter != contents.end(); ++iter) {
         QFrame* tmp = (*iter).second;
         if (tmp)
            tmp->hide();
     }

     QFrame* tmp = contents["开始检测"];
     if (tmp == NULL) {
         starttestingpage* content_widget = new starttestingpage;
         content_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

         contents[QStringLiteral("开始检测")] = content_widget;
         main_container->addWidget(content_widget);

         QObject::connect(content_widget, SIGNAL(startReporting(const QString&)),
                          this, SLOT(startReport(const QString&)));
         QObject::connect(content_widget, SIGNAL(startComparing(const QString&)),
                          this, SLOT(startCompare(const QString&)));

         tmp = content_widget;
     }

     tmp->show();
 }

 void MainWindow::createReportWidget() {
     map<QString, QFrame*>::iterator iter = contents.begin();
     for (; iter != contents.end(); ++iter) {
         QFrame* tmp = (*iter).second;
         if (tmp)
             tmp->hide();
     }

     QFrame* tmp = contents["填写报告"];
     if (tmp == NULL) {
         QFrame* content_widget = new reportingcontainer;
         content_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

         main_container->addWidget(content_widget);
         contents[QStringLiteral("填写报告")] = content_widget;
         tmp = content_widget;
     }

     tmp->show();
 }

 void MainWindow::createReportLstWidget() {
     map<QString, QFrame*>::iterator iter = contents.begin();
     for (; iter != contents.end(); ++iter) {
         QFrame* tmp = (*iter).second;
         if (tmp)
            tmp->hide();
     }

     QFrame* tmp = contents["报告列表"];
     if (tmp == NULL) {
         reportlstcontainer* content_widget = new reportlstcontainer;
         content_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

         main_container->addWidget(content_widget);
         contents[QStringLiteral("报告列表")] = content_widget;

         QObject::connect(content_widget, SIGNAL(startReporting(QString)),
                          this, SLOT(startReport(const QString&)));

         tmp = content_widget;
     }

     tmp->show();
 }

 void MainWindow::createResourceWidget() {
     map<QString, QFrame*>::iterator iter = contents.begin();
     for (; iter != contents.end(); ++iter) {
         QFrame* tmp = (*iter).second;
         if (tmp)
            tmp->hide();
     }

     QFrame* tmp = contents["样本资料"];
     if (tmp == NULL) {
         QFrame* content_widget = new sampleresourcecontainer;
         content_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

         main_container->addWidget(content_widget);
         contents[QStringLiteral("样本资料")] = content_widget;
         tmp = content_widget;
     }

     tmp->show();
 }

 void MainWindow::createCompareWidget() {
     map<QString, QFrame*>::iterator iter = contents.begin();
     for (; iter != contents.end(); ++iter) {
         QFrame* tmp = (*iter).second;
         if (tmp)
            tmp->hide();
     }

     QFrame* tmp = contents["对比结果"];
     if (tmp == NULL) {
         QFrame* content_widget = new imagecomparewidget;
         content_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

         main_container->addWidget(content_widget);
         contents[QStringLiteral("对比结果")] = content_widget;
         tmp = content_widget;
     }

     tmp->show();
 }

void MainWindow::createSettingWidget() {
    map<QString, QFrame*>::iterator iter = contents.begin();
    for (; iter != contents.end(); ++iter) {
        QFrame* tmp = (*iter).second;
        if (tmp)
            tmp->hide();
    }

    QFrame* tmp = contents["系统设置"];
    if (tmp == NULL) {
        QFrame* content_widget = new settingmainwidget;
        content_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        main_container->addWidget(content_widget);
        contents[QStringLiteral("系统设置")] = content_widget;
        tmp = content_widget;
    }

    tmp->show();
}

void MainWindow::createAboutWidget() {
    map<QString, QFrame*>::iterator iter = contents.begin();
    for (; iter != contents.end(); ++iter) {
        QFrame* tmp = (*iter).second;
        if (tmp)
            tmp->hide();
    }

    QFrame* tmp = contents["关于系统"];
    if (tmp == NULL) {
        QFrame* content_widget = new QFrame;
        content_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        main_container->addWidget(content_widget);
        contents[QStringLiteral("关于系统")] = content_widget;
        tmp = content_widget;
    }

    tmp->show();
}

 void MainWindow::startTest(const QJsonObject & sample) {
    this->createTestingWidget();
    starttestingpage* p = (starttestingpage*)contents["开始检测"];
    p->setCurrentTestingSample(sample);
 }

 void MainWindow::startReport(const QJsonObject & sample) {

 }

void MainWindow::startReport(const QString& sample_id) {
    this->createReportWidget();
    reportingcontainer* p = (reportingcontainer*)contents["填写报告"];
    p->setCurrentReportingSampleId(sample_id);
}

void MainWindow::startCompare(const QString& sample_id) {

}

bool MainWindow::isReadyToChangeMainWidget() {
    starttestingpage* tmp = (starttestingpage*)contents["开始检测"];
    if (tmp && tmp->currentStatus() == starttestingpage::TestStatus_testing) {
        QMessageBox::information(this, "error",
                                 tr("请先完成测试在切换界面"),
                                 QMessageBox::Ok, QMessageBox::Ok);
        return false;
    } else {
        return true;
    }
}
