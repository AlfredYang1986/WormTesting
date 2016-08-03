#include "descriptionlabel.h"
#include <QFile>

descriptionlabel::descriptionlabel() {
    this->setupDescription();
}

descriptionlabel::~descriptionlabel() {

}

void descriptionlabel::setupDescription() {
    QFile f(":/resource/descriptions");
    if (f.open(QIODevice::OpenModeFlag::ReadOnly)) {
        QString html = f.readAll();
        this->setText(html);
        f.close();
    }
    this->setWordWrap(true);
}
