#include "addwormdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <proxy/wormproxy.h>
#include <proxy/proxymanager.h>

addwormdialog::addwormdialog() {
    this->setUpSubviews();
}

addwormdialog::~addwormdialog() {
    main_layout->deleteLater();
}

QSize addwormdialog::sizeHint() const {
    return QSize(500, 300);
}

void addwormdialog::setUpSubviews() {
    main_layout = new QVBoxLayout;

    worm_cat_box = new QComboBox;
    worm_edit = new QLineEdit;

    QFormLayout* content_layout = new QFormLayout;
    content_layout->addRow("虫类:", worm_cat_box);
    content_layout->addRow("虫名:", worm_edit);

    main_layout->addLayout(content_layout);

    QHBoxLayout* btns_layout = new QHBoxLayout;
    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding,  QSizePolicy::Minimum));

    QPushButton* save_btn = new QPushButton("添加");
    btns_layout->addWidget(save_btn);
    QObject::connect(save_btn, SIGNAL(released()), this, SLOT(addWormImpl()));

    QPushButton* cancel_btn = new QPushButton("取消");
    btns_layout->addWidget(cancel_btn);
    QObject::connect(cancel_btn, SIGNAL(released()), this, SLOT(quitDialog()));

    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding,  QSizePolicy::Minimum));

    main_layout->addLayout(btns_layout);

    this->setLayout(main_layout);

    proxymanager::instance()->getWormProxy()->onlyWormCat();

    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(pushWormSuccess()),
                     this, SLOT(addWormSuccess()));

    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(onlyWormCatSuccess(QJsonArray)),
                     this, SLOT(onlyCategoriesSuccess(QJsonArray)));
}

void addwormdialog::addWormImpl() {
    QString worm_cat = worm_cat_box->currentText();
    QString worm = worm_edit->text();
    if (!worm.isEmpty()) {
        proxymanager::instance()->getWormProxy()->pushWorm(worm, worm_cat);
    }
}

void addwormdialog::quitDialog() {
    this->close();
}

void addwormdialog::addWormSuccess() {
    this->close();
}

void addwormdialog::onlyCategoriesSuccess(const QJsonArray & result) {
    QJsonArray::const_iterator iter = result.begin();
    for (; iter != result.end(); ++iter) {
        QString tmp = (*iter).toString();
        worm_cat_box->addItem(tmp);
    }
}

