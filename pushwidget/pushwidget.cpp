#include "pushwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QComboBox>
#include <QGroupBox>
#include "samplesearchingwidget.h"
#include "proxy/proxymanager.h"
#include "proxy/sampleproxy.h"
#include "proxy/patientproxy.h"
#include "commonwidget/sampledetailwidget.h"

pushwidget::pushwidget() {
    this->setUpSubviews();
}

pushwidget::~pushwidget() {
    main_layout->deleteLater();
}

void pushwidget::setUpSubviews() {
    main_layout = new QVBoxLayout;

//    main_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QHBoxLayout* content_layout = new QHBoxLayout;
//    content_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QVBoxLayout* left_layout = new QVBoxLayout;
    sample_detail_widget = new sampledetailwidget();
    left_layout->addWidget(sample_detail_widget);

    QPushButton* sample_button = new QPushButton("录入样本");
    QObject::connect(sample_button, SIGNAL(released()), sample_detail_widget, SLOT(sampleBtnClick()));
    left_layout->addWidget(sample_button);
    QPushButton* sample_cancel = new QPushButton("取消样本");
    QObject::connect(sample_cancel, SIGNAL(released()), sample_detail_widget, SLOT(sampleCancelBtnClick()));
    left_layout->addWidget(sample_cancel);

    content_layout->addLayout(left_layout);

    sample_searching_widget = new samplesearchingwidget;
    sample_searching_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sample_searching_widget->setMinimumSize(QSize(300,300));
    sample_searching_widget->setContentsMargins(0,0,0,0);
    content_layout->addWidget(sample_searching_widget);

//    content_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    main_layout->addLayout(content_layout);
//    main_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    this->setLayout(main_layout);

//    QObject::connect(proxymanager::instance()->getPatientProxy(), SIGNAL(pushPatientSuccess(const QJsonObject&)),
//                     this, SLOT(pushPatientSuccess(const QJsonObject&)));

    QObject::connect(sample_detail_widget, SIGNAL(didFinishEditPatientID(const QString&)),
                     this, SLOT(didFinishEditPatientId(const QString&)));
    QObject::connect(sample_detail_widget, SIGNAL(didFinishEditSampleID(const QString&)),
                     this, SLOT(didFinishEditSampleId(const QString&)));

    QObject::connect(proxymanager::instance()->getSampleProxy(), SIGNAL(pushSampleSuccess(const QJsonObject&)),
                     this, SLOT(pushSampleSuccess(const QJsonObject&)));

    QObject::connect(proxymanager::instance()->getSampleProxy(), SIGNAL(updateSampleSuccess(const QJsonObject&)),
                     this, SLOT(pushSampleSuccess(const QJsonObject&)));

    QObject::connect(proxymanager::instance()->getPatientProxy(), SIGNAL(queryPatientSuccess(const QJsonObject&)),
                     this, SLOT(queryPatientSuccess(const QJsonObject&)));

    QObject::connect(proxymanager::instance()->getSampleProxy(), SIGNAL(querySampleWithIDSuccess(const QJsonObject&)),
                     this, SLOT(querySampleSuccess(const QJsonObject&)));

}

QSize pushwidget::sizeHint() const {
    return QSize(300, 300);
}

void pushwidget::pushSampleSuccess(const QJsonObject &) {
    sample_searching_widget->reloadData();
}

void pushwidget::didFinishEditPatientId(const QString& patient_id) {
    if (!patient_id.isEmpty()) {
        proxymanager::instance()->getPatientProxy()->queryPatiendWithId(patient_id);
    }
}

void pushwidget::didFinishEditSampleId(const QString& sample_id) {
    if (!sample_id.isEmpty()) {
        proxymanager::instance()->getSampleProxy()->querySampleWithID(sample_id);
    }
}

void pushwidget::queryPatientSuccess(const QJsonObject & patient) {
    sample_detail_widget->queryPatientSuccess(patient);
}

void pushwidget::querySampleSuccess(const QJsonObject& sample) {
    sample_detail_widget->querySampleSuccess(sample);
    QJsonObject patient = sample["patient"].toObject();
    sample_detail_widget->queryPatientSuccess(patient);
}
