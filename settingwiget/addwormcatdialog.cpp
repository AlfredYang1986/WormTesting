#include "addwormcatdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <proxy/wormproxy.h>
#include <proxy/proxymanager.h>

addWormCatDialog::addWormCatDialog() {
    this->setUpSubviews();
}

addWormCatDialog::~addWormCatDialog() {
    main_layout->deleteLater();
}

QSize addWormCatDialog::sizeHint() const {
    return QSize(500, 300);
}

void addWormCatDialog::setUpSubviews() {
    main_layout = new QVBoxLayout;

    worm_cat_edit = new QLineEdit;

    QFormLayout* content_layout = new QFormLayout;
    content_layout->addRow("添加虫类:", worm_cat_edit);

    main_layout->addLayout(content_layout);

    QHBoxLayout* btns_layout = new QHBoxLayout;
    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding,  QSizePolicy::Minimum));

    QPushButton* save_btn = new QPushButton("保存");
    btns_layout->addWidget(save_btn);
    QObject::connect(save_btn, SIGNAL(released()), this, SLOT(addWormCatImpl()));

    QPushButton* cancel_btn = new QPushButton("取消");
    btns_layout->addWidget(cancel_btn);
    QObject::connect(cancel_btn, SIGNAL(released()), this, SLOT(quitDialog()));

    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding,  QSizePolicy::Minimum));

    main_layout->addLayout(btns_layout);

    this->setLayout(main_layout);

    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(pushWormCatSuccess()),
                     this, SLOT(addWormCatSuccess()));
}

void addWormCatDialog::addWormCatImpl() {
    QString worm_cat = worm_cat_edit->text();
    if (!worm_cat.isEmpty()) {
        proxymanager::instance()->getWormProxy()->pushWormCat(worm_cat);
    }
}

void addWormCatDialog::quitDialog() {
    this->close();
}

void addWormCatDialog::addWormCatSuccess() {
    this->close();
}
