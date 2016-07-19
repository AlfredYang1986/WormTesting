#include "reportingdetailitem.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>

reportingdetailitem::reportingdetailitem(const QString& t)
    : title(t) {
    this->setUpSubviews();
}

reportingdetailitem::~reportingdetailitem() {
    main_layout->deleteLater();
    label->deleteLater();
    box->deleteLater();
}

void reportingdetailitem::setUpSubviews() {
    main_layout = new QHBoxLayout;

    label = new QLabel(title);
    label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    main_layout->addWidget(label);

    box = new QComboBox;
    box->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    box->addItem(QStringLiteral("未检出"));
    box->addItem(QStringLiteral("已检出"));
    main_layout->addWidget(box);

    this->setLayout(main_layout);
}

QSize reportingdetailitem::sizeHint() const {
    QSize l_size = label->sizeHint();
    QSize b_size = box->sizeHint();

    return QSize(l_size.width() + b_size.width(), //std::max(l_size.height(), b_size.width()));
                 l_size.height());
}

QString reportingdetailitem::getItemTestResult() const {
    if (box->currentText() == QStringLiteral("已检出")) return title;
    else return "";
}

void reportingdetailitem::setCurrentSelected(bool b) {
    if (b)
        box->setCurrentText(QStringLiteral("已检出"));
    else
        box->setCurrentText(QStringLiteral("未检出"));
}

QString reportingdetailitem::getItemTitle() const {
    return title;
}
