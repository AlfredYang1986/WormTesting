#include "aboutmainwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "descriptionlabel.h"
#include "aboutuswidget.h"
#include "declearationwidget.h"
#include <QScrollArea>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>

aboutmainwidget::aboutmainwidget()
    : t(NULL), a(NULL), d(NULL) {
    this->setupSubviews();
}

aboutmainwidget::~aboutmainwidget() {
    main_layout->deleteLater();
}

void aboutmainwidget::setupSubviews() {
    main_layout = new QVBoxLayout;

    area = new QScrollArea;
    area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    t = new descriptionlabel;
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect clientRect = desktopWidget->availableGeometry();
    t->setFixedWidth(clientRect.width() - 16);
    area->setWidget(t);

    main_layout->addWidget(area);

    QHBoxLayout* btn_layout = new QHBoxLayout;
    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QPushButton* des_btn = new QPushButton(("测试描述"));
    QObject::connect(des_btn, SIGNAL(released()), this, SLOT(des_btn_clicked()));
    btn_layout->addWidget(des_btn);

    QPushButton* aboutus_btn = new QPushButton(("关于我们"));
    QObject::connect(aboutus_btn, SIGNAL(released()), this, SLOT(aboutus_btn_clicked()));
    btn_layout->addWidget(aboutus_btn);

    QPushButton* declear_btn = new QPushButton(("免责声明"));
    QObject::connect(declear_btn, SIGNAL(released()), this, SLOT(declearaton_btn_clicked()));
    btn_layout->addWidget(declear_btn);
    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    main_layout->addLayout(btn_layout);

    this->setLayout(main_layout);
    this->setStyleSheet("QPushButton {"
                            "width: 80px;"
                            "height: 30px;"
                            "color: white;"
                            "font-size: 14px;"
                            "background-color: #1bd7ff;"
                            "border: 1px solid #1bd7ff;"
                        "}");
}

QSize aboutmainwidget::sizeHint() const {
    return QSize(100, 100);
}

void aboutmainwidget::des_btn_clicked() {
    if (t == NULL)
        t = new descriptionlabel;

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect clientRect = desktopWidget->availableGeometry();
    t->setFixedWidth(clientRect.width() - 16);
    area->setWidget(t);
    a = NULL;
    d = NULL;
}

void aboutmainwidget::aboutus_btn_clicked() {
    if (a == NULL)
        a = new aboutuswidget;

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect clientRect = desktopWidget->availableGeometry();
    a->setFixedWidth(clientRect.width() - 16);
    area->setWidget(a);
    t = NULL;
    d = NULL;
}

void aboutmainwidget::declearaton_btn_clicked() {
    if (d == NULL)
        d = new declearationwidget;

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect clientRect = desktopWidget->availableGeometry();
    d->setFixedWidth(clientRect.width() - 16);
    area->setWidget(d);
    t = NULL;
    a = NULL;
}
