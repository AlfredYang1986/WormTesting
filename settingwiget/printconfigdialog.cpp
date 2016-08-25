#include "printconfigdialog.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QLabel>

printconfigdialog::printconfigdialog() {
    this->setupSubviews();
}

printconfigdialog::~printconfigdialog() {
    main_layout->deleteLater();
}

QSize printconfigdialog::sizeHint() const {
    return QSize(500, 300);
}

void printconfigdialog::setupSubviews() {
    main_layout = new QVBoxLayout;

    QLabel* title = new QLabel(QStringLiteral("更新医院名称："));
    title->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    main_layout->addWidget(title);

    hos_name_edit = new QLineEdit;
    main_layout->addWidget(hos_name_edit);

    QFile f(QApplication::applicationDirPath() + "/config");
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        hos_name_edit->setText(QString(f.readAll()));
        f.close();
    }

    QHBoxLayout* btn_layout = new QHBoxLayout;
    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QPushButton* save_btn = new QPushButton(QStringLiteral("更新"));
    QObject::connect(save_btn, SIGNAL(released()), this, SLOT(saveBtnClicked()));
    btn_layout->addWidget(save_btn);

    QPushButton* cancel_btn = new QPushButton(QStringLiteral("取消"));
    QObject::connect(cancel_btn, SIGNAL(released()), this, SLOT(cancelBtnClicked()));
    btn_layout->addWidget(cancel_btn);

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

void printconfigdialog::saveBtnClicked() {

    QString str = hos_name_edit->text();
    QFile f(QApplication::applicationDirPath() + "/config");
    if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        f.reset();
        QTextStream s(&f);
        s << str;
        f.close();
    }

    this->close();
}

void printconfigdialog::cancelBtnClicked() {
    this->close();
}
