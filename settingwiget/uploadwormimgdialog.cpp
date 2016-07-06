#include "uploadwormimgdialog.h"
#include "commonwidget/commonimglstwidget.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include "proxy/proxymanager.h"
#include "proxy/wormproxy.h"
#include "proxy/fileoptproxy.h"

uploadwormimgdialog::uploadwormimgdialog() {
    this->setUpSubviews();
}

uploadwormimgdialog::~uploadwormimgdialog() {
    main_layout->deleteLater();
}

QSize uploadwormimgdialog::sizeHint() const {
    return QSize(1000, 1000);
}

void uploadwormimgdialog::setUpSubviews() {
    main_layout = new QVBoxLayout;

    box = new QComboBox;
    pic = new QLabel;
    pic->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    img_lst = new commonimglstwidget;
    img_lst->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QFormLayout* form = new QFormLayout;
    form->addRow("选择虫类", box);
    main_layout->addLayout(form);

    QHBoxLayout* content_layout = new QHBoxLayout;
    content_layout->addWidget(pic);
    content_layout->addWidget(img_lst);
    main_layout->addLayout(content_layout);

    QHBoxLayout* btns_layout = new QHBoxLayout;
    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QPushButton* save_btn = new QPushButton("添加");
    QObject::connect(save_btn, SIGNAL(released()), this, SLOT(savaBtnClicked()));
    btns_layout->addWidget(save_btn);
    btns_layout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));

    QPushButton* cancel_btn = new QPushButton("关闭");
    QObject::connect(cancel_btn, SIGNAL(released()), this, SLOT(cancelBtnClicked()));
    btns_layout->addWidget(cancel_btn);
    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    main_layout->addLayout(btns_layout);

    this->setLayout(main_layout);

    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(queryWormCatSuccess(QJsonObject)),
                     this, SLOT(queryWormCatSuccess(QJsonObject)));

    QObject::connect(box, SIGNAL(currentTextChanged(QString)),
                     this, SLOT(currentBoxTextChanged(QString)));

    proxymanager::instance()->getWormProxy()->queryWormCat();
}

void uploadwormimgdialog::savaBtnClicked() {
    QString file = QFileDialog::getOpenFileName(this,
                        "", "",
                        "Images (*.png *.xpm *.jpg)");

    QImage image(file);
    QString worm_name = box->currentText();
    proxymanager::instance()->getFileProxy()->uploadSampleImage(worm_name, image);
//    this->close();
}

void uploadwormimgdialog::cancelBtnClicked() {
    this->close();
}

void uploadwormimgdialog::queryWormCatSuccess(const QJsonObject & cats) {

    if (this->isHidden())
        return;

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

void uploadwormimgdialog::currentBoxTextChanged(const QString& cur) {

    if (this->isHidden())
        return;

    QStringList keys = current_cats.keys();
    QStringList::iterator key = keys.begin();
    for (; key != keys.end(); ++key) {
        QJsonArray arr = current_cats[*key].toArray();

        QJsonArray::iterator iter = arr.begin();
        for (; iter != arr.end(); ++iter) {
            QString name = (*iter).toObject()["name"].toString();
            if (name == cur) {
                QVector<QVariant> var_lst = (*iter).toObject()["img_lst"]
                        .toArray().toVariantList().toVector();
                QVector<QString> name_lst;
                QVector<QVariant>::iterator i = var_lst.begin();
                for (; i != var_lst.end(); ++i) {
                    name_lst.push_back((*i).toString());
                }
                img_lst->changeShowingImgLst(name_lst);
                break;
            }
        }
    }
}

void uploadwormimgdialog::showEvent(QShowEvent *) {
    QObject::connect(proxymanager::instance()->getFileProxy(), SIGNAL(uploadSampleImageSuccess(QString,QString)),
                     this, SLOT(uploadSampleImageSuccess(QString,QString)));
}

void uploadwormimgdialog::hideEvent(QHideEvent *) {
    QObject::disconnect(proxymanager::instance()->getFileProxy(), SIGNAL(uploadSampleImageSuccess(QString,QString)),
                     this, SLOT(uploadSampleImageSuccess(QString,QString)));
}

void uploadwormimgdialog::uploadSampleImageSuccess(const QString & worm_name, const QString & img_name) {
    proxymanager::instance()->getWormProxy()->pushWormImage(worm_name, img_name);
    box->setCurrentText(worm_name);
}
