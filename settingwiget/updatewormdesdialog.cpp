#include "updatewormdesdialog.h"
#include <QVBoxLayout>
#include <QComboBox>
#include <QTextEdit>
#include <QFormLayout>
#include <QPushButton>
#include "proxy/proxymanager.h"
#include "proxy/wormproxy.h"

updatewormdesdialog::updatewormdesdialog() {
    this->setUpSubviews();
}

updatewormdesdialog::~updatewormdesdialog() {
    QObject::disconnect(proxymanager::instance()->getWormProxy(), SIGNAL(queryWormCatSuccess(QJsonObject)),
                     this, SLOT(queryWormCatSuccess(QJsonObject)));

    QObject::disconnect(box, SIGNAL(currentTextChanged(QString)),
                     this, SLOT(currentBoxTextChanged(QString)));
}

QSize updatewormdesdialog::sizeHint() const {
    return QSize(500, 300);
}

void updatewormdesdialog::setUpSubviews() {
    main_layout = new QVBoxLayout;

    box = new QComboBox;
    box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    des = new QTextEdit;

    QFormLayout* content_layout = new QFormLayout;
    content_layout->addRow("选择虫子", box);
    content_layout->addRow("修改描述", des);

    QHBoxLayout* btns_layout = new QHBoxLayout;
    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QPushButton* save_btn = new QPushButton("更新");
    QObject::connect(save_btn, SIGNAL(released()), this, SLOT(savaBtnClicked()));
    btns_layout->addWidget(save_btn);
    btns_layout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));

    QPushButton* cancel_btn = new QPushButton("取消");
    QObject::connect(cancel_btn, SIGNAL(released()), this, SLOT(cancelBtnClicked()));
    btns_layout->addWidget(cancel_btn);
    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    main_layout->addLayout(content_layout);
    main_layout->addLayout(btns_layout);

    this->setLayout(main_layout);

    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(queryWormCatSuccess(QJsonObject)),
                     this, SLOT(queryWormCatSuccess(QJsonObject)));

    QObject::connect(box, SIGNAL(currentTextChanged(QString)),
                     this, SLOT(currentBoxTextChanged(QString)));

    proxymanager::instance()->getWormProxy()->queryWormCat();
}

void updatewormdesdialog::savaBtnClicked() {
    QString n = box->currentText();
    QString d = des->toPlainText();
    if (!n.isEmpty() && !d.isEmpty()) {
        proxymanager::instance()->getWormProxy()->changeWromdescription(n, d);

        QTime dieTime = QTime::currentTime().addMSecs(1000);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    this->close();
}

void updatewormdesdialog::cancelBtnClicked() {
    this->close();
}

void updatewormdesdialog::queryWormCatSuccess(const QJsonObject & cats) {
    current_cats = cats;

    QStringList keys = current_cats.keys();
    QStringList::iterator key = keys.begin();
    for (; key != keys.end(); ++key) {
        QJsonArray arr = current_cats[*key].toArray();

        QJsonArray::iterator iter = arr.begin();
        for (; iter != arr.end(); ++iter) {
            QString name = (*iter).toObject()["name"].toString();
            box->addItem(name);
        }
    }
}

void updatewormdesdialog::currentBoxTextChanged(const QString& cur) {
    QStringList keys = current_cats.keys();
    QStringList::iterator key = keys.begin();
    for (; key != keys.end(); ++key) {
        QJsonArray arr = current_cats[*key].toArray();

        QJsonArray::iterator iter = arr.begin();
        for (; iter != arr.end(); ++iter) {
            QString name = (*iter).toObject()["name"].toString();
            if (name == cur) {
                QString text = (*iter).toObject()["description"].toString();
                des->setText(text);
                break;
            }
        }
    }
}
