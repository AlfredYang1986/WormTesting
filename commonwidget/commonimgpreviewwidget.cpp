#include "commonimgpreviewwidget.h"
#include "proxy/proxymanager.h"
#include "proxy/fileoptproxy.h"

commonimgpreviewwidget::commonimgpreviewwidget() {

}

commonimgpreviewwidget::~commonimgpreviewwidget() {

}

void commonimgpreviewwidget::setPreviewImage(const QPixmap & m) {
    QPixmap m2 = m.scaled(this->width(), this->height());
//    QPixmap m2 = m.scaledToHeight(this->height());
    this->setPixmap(m2);
}

void commonimgpreviewwidget::fillImages(const QJsonObject& sample) {
    QJsonArray arr = sample["images"].toArray();
    current_img_name = arr.last().toString();
    proxymanager::instance()->getFileProxy()->downloadFile(current_img_name);
}

void commonimgpreviewwidget::downloadFileSuccess(const QByteArray& arr, const QString& filename) {
    if (current_img_name == filename) {
        QPixmap m;
        m.loadFromData(arr);
        m = m.scaled(this->width(), this->height());
//        m = m.scaledToHeight(this->height());
        this->setPixmap(m);
    }
}

void commonimgpreviewwidget::showEvent(QShowEvent *) {
    QObject::connect(proxymanager::instance()->getFileProxy(), SIGNAL(downloadFileSuccess(QByteArray,QString)),
                     this, SLOT(downloadFileSuccess(QByteArray,QString)));
}

void commonimgpreviewwidget::hideEvent(QHideEvent *) {
    QObject::disconnect(proxymanager::instance()->getFileProxy(), SIGNAL(downloadFileSuccess(QByteArray,QString)),
                     this, SLOT(downloadFileSuccess(QByteArray,QString)));
}
