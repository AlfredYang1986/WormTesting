#include "mainwindow.h"
#include "titlewidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setUpSubviews();
}

MainWindow::~MainWindow() {
    content_widget->deleteLater();
    title_widget->deleteLater();
    main_container->deleteLater();
    center_widget->deleteLater();
}

void MainWindow::setUpSubviews() {
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("MainWindow"));
    this->setWindowTitle(QStringLiteral("虫卵检测系统V1.0"));
    this->resize(1181, 733);
    center_widget = new QWidget;
    center_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    center_widget->setObjectName(QStringLiteral("title_widget"));
    this->setCentralWidget(center_widget);

    main_container = new QVBoxLayout;
    main_container->setContentsMargins(0, 0, 0, 0);

    title_widget = new titlewidget;
    title_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    title_widget->setObjectName(QStringLiteral("title_widget"));
    title_widget->setStyleSheet("QWidget#title_widget { background-color: red }");

    content_widget = new QWidget;
    content_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    content_widget->setObjectName(QStringLiteral("content_widget"));
    content_widget->setStyleSheet("QWidget#content_widget { background-color: yellow }");

    main_container->addWidget(title_widget);
    main_container->addWidget(content_widget);

    center_widget->setLayout(main_container);
}
