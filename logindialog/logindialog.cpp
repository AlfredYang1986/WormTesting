﻿#include "logindialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "proxy/proxymanager.h"
#include "proxy/authproxy.h"

logindialog::logindialog() {
    this->setUpSubview();
}

logindialog::~logindialog() {
    main_layout->deleteLater();
}

QSize logindialog::sizeHint() const {
    return QSize(500, 300);
}

void logindialog::setUpSubview() {
    setWindowFlags(Qt::FramelessWindowHint);
//    setWindowOpacity(1);
//    setAttribute(Qt::WA_TranslucentBackground);

    user_name_edit = new QLineEdit;
    password_edit = new QLineEdit;
    password_edit->setEchoMode(QLineEdit::Password);

    main_layout = new QVBoxLayout;

    QHBoxLayout* tmp = new QHBoxLayout;
    tmp->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QFormLayout* content_layout = new QFormLayout;
    content_layout->addRow(QStringLiteral("用户名 :"), user_name_edit);
    content_layout->addItem(new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));
    content_layout->addRow(QStringLiteral("密 码 :"), password_edit);

    tmp->addLayout(content_layout);
    tmp->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    main_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QHBoxLayout* label_layout = new QHBoxLayout;
    QLabel* label = new QLabel(" ");
    label->setObjectName("login_title");
    label_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding , QSizePolicy::Minimum));
    label_layout->addWidget(label);
    label_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding , QSizePolicy::Minimum));

    main_layout->addLayout(label_layout);
    main_layout->addLayout(tmp);

    QHBoxLayout* btn_layout = new QHBoxLayout;
    QPushButton* btn_login = new QPushButton(QStringLiteral("登录"));
    QObject::connect(btn_login, SIGNAL(released()), this, SLOT(loginBtnClicked()));
    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding , QSizePolicy::Minimum));
    btn_layout->addWidget(btn_login);
    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding , QSizePolicy::Minimum));

    main_layout->addLayout(btn_layout);
    main_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    this->setLayout(main_layout);

    this->setObjectName("login_dialog");
    this->setStyleSheet("QWidget#login_dialog {"
                            "background-color: none;"
                            "background-image: url(':/resource/login_bkg.png');"
                        "}"
                        "QLabel {"
                            "color: white;"
                            "font-size: 18px;"
                        "}"
                        "QLabel#login_title {"
                            "font-size: 30px;"
                            "color: white;"
                            "margin-bottom: 20px;"
                            "letter-spacing:5px;"
                        "}"
                        "QLineEdit {"
                            "border: none;"
                            "border-bottom: 1px solid #1bb1ff;"
                            "width: 200px;"
                            "line-height: 36px;"
                        "}"
                        "QPushButton {"
                            "margin-top: 20px;"
                            "width: 280px;"
                            "height: 35px;"
                            "color: #1bd7ff;"
                            "font-size: 18px;"
                            "background-color: white;"
                            "border: 1px solid #1bd7ff;"
                            "border-radius: 4px;"
                        "}"
                        );
}

void logindialog::loginBtnClicked() {
    QString user_name = user_name_edit->text();
    QString password = password_edit->text();

    if (user_name.isEmpty() || password.isEmpty())
        return;
    else
        proxymanager::instance()->getAuthProxy()->login(user_name, password);
}

void logindialog::showEvent(QShowEvent *) {
    user_name_edit->clear();
    password_edit->clear();
    user_name_edit->setFocus();
}
