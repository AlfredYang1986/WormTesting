#include "imglstitem.h"
#include <QPushButton>
#include <QPixmap>

imglstitem::imglstitem() {
    this->setUpSubviews();
}

imglstitem::~imglstitem() {
    delect_btn->deleteLater();
    save_as_btn->deleteLater();
}

QSize imglstitem::sizeHint() const {
    return QSize(200, 200);
}

void imglstitem::setUpSubviews() {
    delect_btn = new QPushButton("删除");
    save_as_btn = new QPushButton("另存为");

    delect_btn->setGeometry(0, 0, 50, 30);
    save_as_btn->setGeometry(0, 35, 50, 30);

    delect_btn->setParent(this);
    save_as_btn->setParent(this);

    QObject::connect(save_as_btn, SIGNAL(released()), this, SLOT(saveAsBtnSelected()));
    QObject::connect(delect_btn, SIGNAL(released()), this, SLOT(delectBtnSelected_slot()));
}

void imglstitem::saveAsBtnSelected() {
    const QPixmap* m = this->pixmap();
    m->save(this->objectName(), "JPG");
}

void imglstitem::delectBtnSelected_slot() {
    emit delectBtnSelected(this->objectName());
}
