#include "deletewwormcatdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <proxy/wormproxy.h>
#include <proxy/proxymanager.h>

deletewwormcatdialog::deletewwormcatdialog() {
    this->setUpSubviews();
}

deletewwormcatdialog::~deletewwormcatdialog() {
    main_layout->deleteLater();
}

QSize deletewwormcatdialog::sizeHint() const {
    return QSize(500, 300);
}

void deletewwormcatdialog::setUpSubviews() {
    main_layout = new QVBoxLayout;

    box = new QComboBox;

    QFormLayout* content_layout = new QFormLayout;
    content_layout->addRow("删除虫类:", box);

    main_layout->addLayout(content_layout);

    QHBoxLayout* btns_layout = new QHBoxLayout;
    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding,  QSizePolicy::Minimum));

    QPushButton* save_btn = new QPushButton("删除");
    btns_layout->addWidget(save_btn);
    QObject::connect(save_btn, SIGNAL(released()), this, SLOT(deleteWormCatImpl()));

    QPushButton* cancel_btn = new QPushButton("取消");
    btns_layout->addWidget(cancel_btn);
    QObject::connect(cancel_btn, SIGNAL(released()), this, SLOT(quitDialog()));

    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding,  QSizePolicy::Minimum));

    main_layout->addLayout(btns_layout);

    this->setLayout(main_layout);

    proxymanager::instance()->getWormProxy()->onlyWormCat();

    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(popWormCatSuccess()),
                     this, SLOT(deleteWormCatSuccess()));

    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(onlyWormCatSuccess(QJsonArray)),
                     this, SLOT(onlyCategoriesSuccess(QJsonArray)));
}

void deletewwormcatdialog::deleteWormCatImpl() {
    QString worm_cat = box->currentText();
    if (!worm_cat.isEmpty()) {
        proxymanager::instance()->getWormProxy()->popWormCat(worm_cat);
    }
}

void deletewwormcatdialog::quitDialog() {
    this->close();
}

void deletewwormcatdialog::deleteWormCatSuccess() {
    this->close();
}

void deletewwormcatdialog::onlyCategoriesSuccess(const QJsonArray & result) {
    QJsonArray::const_iterator iter = result.begin();
    for (; iter != result.end(); ++iter) {
        QString tmp = (*iter).toString();
        box->addItem(tmp);
    }
}
