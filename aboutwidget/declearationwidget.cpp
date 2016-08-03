#include "declearationwidget.h"
#include <QFile>

declearationwidget::declearationwidget() {
    this->setupDeclearation();
}

declearationwidget::~declearationwidget() {

}

void declearationwidget::setupDeclearation() {
    QFile f(":/resource/declearation");
    if (f.open(QIODevice::OpenModeFlag::ReadOnly)) {
        QString html = f.readAll();
        this->setText(html);
        f.close();
    }
    this->setWordWrap(true);
}
