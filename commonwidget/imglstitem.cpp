﻿#include "imglstitem.h"
#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

imglstitem::imglstitem(bool w, bool v)
    : isWormImgItem(w), isVer(v), select_able(false), selected(false) {
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

    {
        selected_label = new QLabel;
        selected_label->setFixedSize(50, 50);
        selected_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        selected_label->clearMask();
        selected_label->setBackgroundRole(QPalette::Base);
        QPixmap m;
        m.load(":resource/tick.png");
        selected_label->setPixmap(m.scaled(50, 50));
        selected_label->setHidden(true);
    }

    //pic_preview = new QLabel;

    //pic_preview->setGeometry(0, 0, 280, 200);
    delect_btn->setGeometry(0, 0, 50, 30);
    save_as_btn->setGeometry(0, 35, 50, 30);

    if (isVer)
        selected_label->setGeometry(115, 75, 50, 50);
    else
        selected_label->setGeometry(45, 25, 50, 50);


    delect_btn->setParent(this);
    save_as_btn->setParent(this);
    selected_label->setParent(this);
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

void imglstitem::mouseDoubleClickEvent(QMouseEvent *) {
    if (select_able) {

        bool can = true;
        emit canSelected(&can);

        if (selected) {
            selected = false;
            selected_label->setHidden(true);
        } else if (can) {
            selected = true;
            selected_label->setHidden(false);
        } else {
            QMessageBox::warning(this, "Error",
                                 QStringLiteral("只能选择一张或者两张图进行打印"),
                                 QMessageBox::Ok, QMessageBox::Ok);
        }
    }
}

void imglstitem::saveAsBtnSelected() {
//    const QPixmap* m = this->pixmap();
    QString filename = QFileDialog::getSaveFileName((QWidget*)this->parent(), "Save File", "", "jpg");
    if (filename.trimmed() == "") {
        return;
    }

    QPixmap m = this->getCurrentPixmap();
    m.save(filename + ".jpg", "JPG");
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

bool imglstitem::isSelected() const {
    return selected;
}

void imglstitem::setSelected(bool b) {
    selected = b;
}

bool imglstitem::isSelectAble() const {
    return select_able;
}

void imglstitem::setSelectAble(bool b) {
    select_able = b;
}
