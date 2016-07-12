#include "reportingcontainer.h"
#include "commonwidget/sampledetailwidget.h"
#include "commonwidget/commonimglstwidget.h"
#include "reportingimgpane.h"
#include <QHBoxLayout>
#include "proxy/proxymanager.h"
#include "proxy/sampleproxy.h"
#include "proxy/patientproxy.h"
#include "reportingdetailwidget.h"
#include <QScrollArea>
#include "commonwidget/commonimgpreviewwidget.h"

reportingcontainer::reportingcontainer() {
    this->setUpSubviews();
}

reportingcontainer::~reportingcontainer() {
    main_layout->deleteLater();
    sample_detail->deleteLater();
    img_preview->deleteLater();
}

void reportingcontainer::setUpSubviews() {
    this->setObjectName("content_report_widget");
//    this->setStyleSheet("QWidget#content_report_widget { background-color: red; }");
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    main_layout = new QHBoxLayout;
    main_layout->setContentsMargins(8,0,0,0);

    sample_detail = new sampledetailwidget;
    sample_detail->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    main_layout->addWidget(sample_detail);

//    main_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    reporting_detail = new reportingdetailwidget;
    reporting_detail->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_layout->addWidget(reporting_detail);

//    reporting_img = new reportingimgpane;
//    reporting_img->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
//	main_layout->addWidget(reporting_img);


    QVBoxLayout* right_layout = new QVBoxLayout;

    img_preview = new commonimgpreviewwidget;
    img_preview->setMaximumWidth(500);
    img_preview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    right_layout->addWidget(img_preview);

    QScrollArea* area = new QScrollArea;
    area->setMaximumSize(QSize(500, 100));
    area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    img_lst = new commonimglstwidget(false, false);
    //img_lst->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    area->setWidget(img_lst);

    right_layout->addWidget(area);
    right_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    main_layout->addLayout(right_layout);

    this->setLayout(main_layout);

    QObject::connect(reporting_detail, SIGNAL(changeCurrentSample(const QJsonObject&)),
                     this, SLOT(currentSampleChange(const QJsonObject&)));

    //QObject::connect(reporting_img, SIGNAL(saveReportTestResult()),
    //                 this, SLOT(saveTestResult()));
}

QSize reportingcontainer::sizeHint() const {
    return QSize(100, 100);
}

void reportingcontainer::currentSampleChange(const QJsonObject& sample) {
    img_preview->fillImages(sample);
}

void reportingcontainer::setCurrentReportingSampleId(const QString& sample_id) {
    proxymanager::instance()->getSampleProxy()->querySampleWithID(sample_id);
}

void reportingcontainer::querySampleWithIDSuccess(const QJsonObject & sample) {
    sample_detail->querySampleSuccess(sample);
    QJsonObject patient = sample["patient"].toObject();
    sample_detail->queryPatientSuccess(patient);
    img_lst->changeCurrentSample(sample);
    //img_preview->fillImages(sample);
    reporting_detail->setSampleDefaultResult(sample);
}

void reportingcontainer::didFinishEditPatientId(const QString& patient_id) {
    if (!patient_id.isEmpty()) {
        proxymanager::instance()->getPatientProxy()->queryPatiendWithId(patient_id);
    }
}

void reportingcontainer::didFinishEditSampleId(const QString& sample_id) {
    if (!sample_id.isEmpty()) {
        proxymanager::instance()->getSampleProxy()->querySampleWithID(sample_id);
    }
}

void reportingcontainer::queryPatientSuccess(const QJsonObject & patient) {
    sample_detail->queryPatientSuccess(patient);
}

void reportingcontainer::querySampleSuccess(const QJsonObject& sample) {
    sample_detail->querySampleSuccess(sample);
    QJsonObject patient = sample["patient"].toObject();
    sample_detail->queryPatientSuccess(patient);
    img_lst->changeCurrentSample(sample);
}

void reportingcontainer::showEvent(QShowEvent *) {
    QObject::connect(proxymanager::instance()->getSampleProxy(), SIGNAL(querySampleWithIDSuccess(QJsonObject)),
                     this, SLOT(querySampleWithIDSuccess(QJsonObject)));

    QObject::connect(sample_detail, SIGNAL(didFinishEditPatientID(const QString&)),
                     this, SLOT(didFinishEditPatientId(const QString&)));
    QObject::connect(sample_detail, SIGNAL(didFinishEditSampleID(const QString&)),
                     this, SLOT(didFinishEditSampleId(const QString&)));

    QObject::connect(img_lst, SIGNAL(changeCurrentImageSignal(QPixmap)),
                     img_preview, SLOT(setPreviewImage(QPixmap)));
}

void reportingcontainer::hideEvent(QHideEvent *) {
    QObject::disconnect(proxymanager::instance()->getSampleProxy(), SIGNAL(querySampleWithIDSuccess(QJsonObject)),
                     this, SLOT(querySampleWithIDSuccess(QJsonObject)));

    QObject::disconnect(sample_detail, SIGNAL(didFinishEditPatientID(const QString&)),
                     this, SLOT(didFinishEditPatientId(const QString&)));
    QObject::disconnect(sample_detail, SIGNAL(didFinishEditSampleID(const QString&)),
                     this, SLOT(didFinishEditSampleId(const QString&)));

    QObject::disconnect(img_lst, SIGNAL(changeCurrentImageSignal(QPixmap)),
                     img_preview, SLOT(setPreviewImage(QPixmap)));
}

void reportingcontainer::saveTestResult() {
    QString sample_id = sample_detail->queryCurrentSampleId();
    QVector<QString> result = reporting_detail->getTestItemResults();
    proxymanager::instance()->getSampleProxy()->pushReportingTestResult(sample_id, result);
}
