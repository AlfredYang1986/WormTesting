#include "reportingcontainer.h"
#include "reportingdetailcontainer.h"
#include "reportingimgpane.h"
#include <QHBoxLayout>

reportingcontainer::reportingcontainer() {
    this->setUpSubviews();
}

reportingcontainer::~reportingcontainer() {
    main_layout->deleteLater();
    reporting_detail->deleteLater();
    reporting_img->deleteLater();
}

void reportingcontainer::setUpSubviews() {
    this->setObjectName("content_report_widget");
//    this->setStyleSheet("QWidget#content_report_widget { background-color: red; }");
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    main_layout = new QHBoxLayout;
    main_layout->setContentsMargins(8,0,0,0);

    reporting_detail = new reportingdetailcontainer;
    reporting_detail->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_layout->addWidget(reporting_detail);

    reporting_img = new reportingimgpane;
    reporting_img->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    main_layout->addWidget(reporting_img);

    this->setLayout(main_layout);

    QObject::connect(reporting_detail, SIGNAL(changeCurrentSample(const QJsonObject&)),
                     this, SLOT(currentSampleChange(const QJsonObject&)));
}

QSize reportingcontainer::sizeHint() const {
    return QSize(100, 100);
}

void reportingcontainer::currentSampleChange(const QJsonObject& sample) {
    reporting_img->fillImages(sample);
}
