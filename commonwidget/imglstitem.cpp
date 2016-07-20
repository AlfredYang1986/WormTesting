#include "imglstitem.h"
#include <QPushButton>
#include <QPixmap>
#include <QLabel>

imglstitem::imglstitem(bool w, bool v)
    : isWormImgItem(w), isVer(v) {
    this->setUpSubviews();
}

imglstitem::~imglstitem() {
    delect_btn->deleteLater();
    save_as_btn->deleteLater();
}

QSize imglstitem::sizeHint() const {
    if (isVer)
        return QSize(280, 200);
    else
        return QSize(140, 100);
}

void imglstitem::setUpSubviews() {

    {
        delect_btn = new QPushButton;
        delect_btn->setFixedSize(50, 30);
        delect_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        delect_btn->clearMask();
        delect_btn->setBackgroundRole(QPalette::Base);
        QPixmap m;
        m.load(":resource/start_testing_delete.png");
        delect_btn->setIcon(m);
        delect_btn->setIconSize(QSize(50, 30));
    }

    {
        save_as_btn = new QPushButton;
        save_as_btn->setFixedSize(50, 30);
        save_as_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        save_as_btn->clearMask();
        save_as_btn->setBackgroundRole(QPalette::Base);
        QPixmap m;
        m.load(":resource/start_testing_save_as.png");
        save_as_btn->setIcon(m);
        save_as_btn->setIconSize(QSize(50, 30));
    }

    //pic_preview = new QLabel;

    //pic_preview->setGeometry(0, 0, 280, 200);
    delect_btn->setGeometry(0, 0, 50, 30);
    save_as_btn->setGeometry(0, 35, 50, 30);

    delect_btn->setParent(this);
    save_as_btn->setParent(this);
    //pic_preview->setParent(this);

    if (isWormImgItem) {
        delect_btn->hide();
        save_as_btn->hide();
    }

    this->setStyleSheet("QPushButton {"
                            "background-color: none;"
                            "border: none;"
                        "}");

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

bool imglstitem::isShowOptBtns() const {
    return !isWormImgItem;
}

void imglstitem::mousePressEvent(QMouseEvent *) {
    emit imageSelected(&current_pixmap);
}

void imglstitem::setCurrentPixmap(const QPixmap & m) {
    current_pixmap = m;
    QPixmap tmp = current_pixmap;
    if (isVer)
        tmp = m.scaled(280, 200);
    else
        tmp = m.scaled(140, 100);
    this->setPixmap(tmp);
}

QPixmap imglstitem::getCurrentPixmap() const {
    return current_pixmap;
}
