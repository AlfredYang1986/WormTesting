#include "commonimgpreviewwidget.h"
#include "proxy/proxymanager.h"
#include "proxy/fileoptproxy.h"
#include <QtMath>

commonimgpreviewwidget::commonimgpreviewwidget() {
    content = new QLabel(this);
}

commonimgpreviewwidget::~commonimgpreviewwidget() {

}

void commonimgpreviewwidget::setPreviewImage(const QPixmap & m) {
    float w = this->layoutContent();
    QPixmap m2 = m.scaled(w, w);
    content->setPixmap(m2);
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
        float w = this->layoutContent();
        m = m.scaled(w, w);
    }
}

float commonimgpreviewwidget::layoutContent() {
    QSize s = this->size();
    float w =  fmin(s.width(), s.height());
    if (s.width() > s.height()) {
        content->setGeometry((s.width() - w) / 2, 0, w, w);
    } else {
        content->setGeometry(0 , (s.height() - w) / 2, w, w);
    }
    return w;
}

void commonimgpreviewwidget::showEvent(QShowEvent *) {
    QObject::connect(proxymanager::instance()->getFileProxy(), SIGNAL(downloadFileSuccess(QByteArray,QString)),
                     this, SLOT(downloadFileSuccess(QByteArray,QString)));
}

void commonimgpreviewwidget::hideEvent(QHideEvent *) {
    QObject::disconnect(proxymanager::instance()->getFileProxy(), SIGNAL(downloadFileSuccess(QByteArray,QString)),
                     this, SLOT(downloadFileSuccess(QByteArray,QString)));
}
