#include "deletewormdialog.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <proxy/wormproxy.h>
#include <proxy/proxymanager.h>

deletewormdialog::deletewormdialog() {
    this->setUpSubviews();
}

deletewormdialog::~deletewormdialog() {
    main_layout->deleteLater();
}

QSize deletewormdialog::sizeHint() const {
    return QSize(500, 300);
}

void deletewormdialog::setUpSubviews() {
    main_layout = new QVBoxLayout;

    worm_cat_box = new QComboBox;
    worm_box = new QComboBox;

    QFormLayout* content_layout = new QFormLayout;
    content_layout->addRow("虫类:", worm_cat_box);
    content_layout->addRow("虫名:", worm_box);

    main_layout->addLayout(content_layout);

    QHBoxLayout* btns_layout = new QHBoxLayout;
    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding,  QSizePolicy::Minimum));

    QPushButton* save_btn = new QPushButton("删除");
    btns_layout->addWidget(save_btn);
    QObject::connect(save_btn, SIGNAL(released()), this, SLOT(deleteWormImpl()));

    QPushButton* cancel_btn = new QPushButton("取消");
    btns_layout->addWidget(cancel_btn);
    QObject::connect(cancel_btn, SIGNAL(released()), this, SLOT(quitDialog()));

    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding,  QSizePolicy::Minimum));

    main_layout->addLayout(btns_layout);

    this->setLayout(main_layout);

    proxymanager::instance()->getWormProxy()->queryWormCat();

    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(popWormSuccess()),
                     this, SLOT(deleteWormSuccess()));

    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(queryWormCatSuccess(QJsonObject)),
                     this, SLOT(queryWormCatSuccess(QJsonObject)));

    QObject::connect(worm_cat_box, SIGNAL(currentTextChanged(QString)),
                     this, SLOT(catChanges(QString)));
}

void deletewormdialog::deleteWormImpl() {
    QString worm_cat = worm_cat_box->currentText();
    QString worm = worm_box->currentText();
    if (!worm.isEmpty()) {
        proxymanager::instance()->getWormProxy()->popWorm(worm, worm_cat);
    }
}

void deletewormdialog::quitDialog() {
    this->close();
}

void deletewormdialog::deleteWormSuccess() {
    this->close();
}

void deletewormdialog::queryWormCatSuccess(const QJsonObject & cats) {

    current_cats = cats;

    QStringList keys = cats.keys();
    QStringList::const_iterator key = keys.begin();
    for(; key != keys.end(); ++key) {
        worm_cat_box->addItem((*key));
    }
}


void deletewormdialog::catChanges(const QString& cur) {
    worm_box->clear();
    QJsonArray worms = current_cats[cur].toArray();
    QJsonArray::const_iterator iter = worms.begin();
    for (; iter != worms.end(); ++iter) {
        QString tmp = (*iter).toObject().operator []("name").toString();
        worm_box->addItem(tmp);
    }
}
