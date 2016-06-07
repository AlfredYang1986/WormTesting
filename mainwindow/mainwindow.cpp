#include "mainwindow.h"
#include "titlewidget/titlewidget.h"
#include "starttesting/starttestingpage.h"
#include "reporting/reportingcontainer.h"
#include "reportlst/reportlstcontainer.h"

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
    this->resize(900, 600);
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
    this->createTestingWidget();

    center_widget->setLayout(main_container);
}

void MainWindow::changeMainContent(const QString &title) {
    if (title == "开始检测") {
        this->createTestingWidget();
    } else if (title == "填写报告") {
        this->createReportWidget();
    } else if (title == "报告列表") {
        this->createReportLstWidget();
    } else {
        this->createResourceWidget();
    }
}

 void MainWindow::createTestingWidget() {

     map<QString, QFrame*>::iterator iter = contents.begin();
     for (; iter != contents.end(); ++iter) {
         QFrame* tmp = (*iter).second;
         tmp->hide();
     }

     QFrame* tmp = contents["开始检测"];
     if (tmp == NULL) {
         starttestingpage* content_widget = new starttestingpage;
         content_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

         main_container->addWidget(content_widget);

         contents[QStringLiteral("开始检测")] = content_widget;
         tmp = content_widget;
     }

     tmp->show();
 }

 void MainWindow::createReportWidget() {
     map<QString, QFrame*>::iterator iter = contents.begin();
     for (; iter != contents.end(); ++iter) {
         QFrame* tmp = (*iter).second;
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
         tmp->hide();
     }

     QFrame* tmp = contents["报告列表"];
     if (tmp == NULL) {
         QFrame* content_widget = new reportlstcontainer;
         content_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

         main_container->addWidget(content_widget);

         contents[QStringLiteral("报告列表")] = content_widget;
         tmp = content_widget;
     }

     tmp->show();
 }

 void MainWindow::createResourceWidget() {
     map<QString, QFrame*>::iterator iter = contents.begin();
     for (; iter != contents.end(); ++iter) {
         QFrame* tmp = (*iter).second;
         tmp->hide();
     }

     QFrame* tmp = contents["样本资料"];
     if (tmp == NULL) {
         QFrame* content_widget = new QFrame;
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
         tmp->hide();
     }

     QFrame* tmp = contents["对比结果"];
     if (tmp == NULL) {
         QFrame* content_widget = new QFrame;
         content_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

         main_container->addWidget(content_widget);

         contents[QStringLiteral("对比结果")] = content_widget;
         tmp = content_widget;
     }

     tmp->show();
 }

