#include "starttestingpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "commonwidget/sampledetailwidget.h"
#include "commonwidget/commonimglstwidget.h"
#include "imgcomparepane.h"
#include "camera/cameraproxy.h"
#include "proxy/proxymanager.h"
#include "proxy/sampleproxy.h"
#include "proxy/fileoptproxy.h"
#include "proxy/patientproxy.h"
#include <QScrollArea>

starttestingpage::starttestingpage() : status(TestStatus_ready) {
    this->setUpSubviews();
}

starttestingpage::~starttestingpage() {
    main_layout->deleteLater();
    sample_detail->deleteLater();
//    sample_searching_widget->deleteLater();
    img_pane->deleteLater();
}

void starttestingpage::setUpSubviews() {
    main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(0,0,0,0);

    QFrame* content_widget = new QFrame;
    content_widget->setObjectName("content_widget_page_one");
    content_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    content_widget->setMinimumSize(QSize(200, 200));
    content_widget->setContentsMargins(0,0,0,0);

    QHBoxLayout* page_one_content_layout = new QHBoxLayout;
    page_one_content_layout->setContentsMargins(8,0,0,0);

    QScrollArea* area = new QScrollArea;
    area->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    sample_detail = new sampledetailwidget;
    sample_detail->setObjectName(QStringLiteral("sample_detail"));
    sample_detail->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    area->setWidget(sample_detail);
    page_one_content_layout->addWidget(area);

//    sample_searching_widget = new samplesearchingwidget;
//    sample_searching_widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
//    sample_searching_widget->setMinimumSize(QSize(300,300));
//    sample_searching_widget->setContentsMargins(0,0,0,0);
//    page_one_content_layout->addWidget(sample_searching_widget);

    img_pane = new imgcomparepane;
    img_pane->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    img_pane->setMinimumSize(QSize(200, 200));
    img_pane->setContentsMargins(0,0,0,0);
    page_one_content_layout->addWidget(img_pane);


    QScrollArea* thumbs = new QScrollArea;
    thumbs->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    thumbs->setFixedWidth(280);

    img_lst_pane = new commonimglstwidget;
    img_lst_pane->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    img_lst_pane->setFixedWidth(280);

    thumbs->setWidget(img_lst_pane);
    page_one_content_layout->addWidget(thumbs);

//    QSpacerItem* page_one_content_spacer = new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum);
//    page_one_content_layout->addSpacerItem(page_one_content_spacer);
    content_widget->setLayout(page_one_content_layout);

    main_layout->addWidget(content_widget);

    QHBoxLayout* control_pane = new QHBoxLayout;
    QSpacerItem* control_left_spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    control_start_btn = new QPushButton(QStringLiteral("开始测试"));
    control_start_btn->setObjectName(QStringLiteral("page_one_start_btn"));
    control_start_btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QObject::connect(control_start_btn, SIGNAL(released()), this, SLOT(startTestingBtnClicked()));

    control_end_btn = new QPushButton(QStringLiteral("完成测试"));
    control_end_btn->setObjectName(QStringLiteral("page_one_cancel_btn"));
    control_end_btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QObject::connect(control_end_btn, SIGNAL(released()), this, SLOT(endTestingBtnClicked()));

    {
        control_report_btn = new QPushButton(QStringLiteral("填写报告"));
        control_report_btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        QObject::connect(control_report_btn, SIGNAL(released()), this, SLOT(startReportingBtnClicked()));
    }

    {
        control_compare_btn = new QPushButton(QStringLiteral("开始对比"));
        control_compare_btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        QObject::connect(control_compare_btn, SIGNAL(released()), this, SLOT(startComparingBtnClicked()));
    }


    QSpacerItem* control_right_spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    control_pane->addSpacerItem(control_left_spacer);
    control_pane->addWidget(control_start_btn);
    control_pane->addSpacerItem(new QSpacerItem(40, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));
    control_pane->addWidget(control_end_btn);
    control_pane->addSpacerItem(new QSpacerItem(40, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));
    control_pane->addWidget(control_report_btn);
    control_pane->addSpacerItem(new QSpacerItem(40, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));
    control_pane->addWidget(control_compare_btn);
    control_pane->addSpacerItem(control_right_spacer);

    main_layout->addLayout(control_pane);

    this->setLayout(main_layout);

    this->setObjectName(QStringLiteral("content_widget"));
    this->setStyleSheet("QWidget#content_widget { "
                            "margin-bottom: 8px;"
                        "}"
                        "QPushButton {"
                            "width: 80px;"
                            "height: 30px;"
                            "color: white;"
                            "font-size: 14px;"
                            "background-color: #1bd7ff;"
                            "border: 1px solid #1bd7ff;"
                        "}");

//    QObject::connect(sample_searching_widget, SIGNAL(currentSample(const QJsonObject&)),
//                     sample_detail, SLOT(currentSample(const QJsonObject&)));

}

void starttestingpage::startTestingBtnClicked() {
    QString sample_id = sample_detail->queryCurrentSampleId();
    if (!sample_id.isEmpty()) {
        status = TestStatus_testing;
        sample_detail->setEnabled(false);
        cameraproxy::instance()->startTesting();
    } else {
        QMessageBox::warning(this, "Error",
                             QStringLiteral("请先选定测试样本"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
}

void starttestingpage::endTestingBtnClicked() {
    status = TestStatus_ready;
    QString sample_id = sample_detail->queryCurrentSampleId();
    proxymanager::instance()->getSampleProxy()->sampleTestComplished(sample_id);
    cameraproxy::instance()->endTesting();
    sample_detail->setEnabled(true);
    img_pane->clearPane();
}

void starttestingpage::takeImageSuccess(const QImage& image) {
    QString sample_id = sample_detail->queryCurrentSampleId();
    if (sample_id.isEmpty()) {
        QMessageBox::warning(this, "Error",
                             QStringLiteral("请先选定测试样本"),
                             QMessageBox::Ok, QMessageBox::Ok);

        return;
    }

    proxymanager::instance()->getSampleProxy()->pushSampleImage(sample_id, image);
}

void starttestingpage::setCurrentTestingSample(const QJsonObject &sample) {
    current_sample = sample;
    sample_detail->querySampleSuccess(sample);
    QJsonObject patient = sample["patient"].toObject();
    sample_detail->queryPatientSuccess(patient);
    img_lst_pane->changeCurrentSample(sample);
}


void starttestingpage::uploadSampleImageSuccess(const QString& sample_id, const QString& image_name) {
    img_lst_pane->pushImageName(image_name);
}


void starttestingpage::startReportingBtnClicked() {
    QString sample_id = sample_detail->queryCurrentSampleId();
    if (!sample_id.isEmpty()) {
        emit startReporting(sample_id);
    }
}

void starttestingpage::startComparingBtnClicked() {
    QString sample_id = sample_detail->queryCurrentSampleId();
    if (!sample_id.isEmpty()) {
        emit startComparing(sample_id);
    }
}

void starttestingpage::querySampleWithIDSuccess(const QJsonObject & sample) {
//    sample_detail->querySampleSuccess(sample);
//    QJsonObject patient = sample["patient"].toObject();
//    sample_detail->queryPatientSuccess(patient);
//    img_lst_pane->changeCurrentSample(sample);
    this->setCurrentTestingSample(sample);
}

void starttestingpage::didFinishEditPatientId(const QString& patient_id) {
    if (!patient_id.isEmpty()) {
        proxymanager::instance()->getPatientProxy()->queryPatiendWithId(patient_id);
    }
}

void starttestingpage::didFinishEditSampleId(const QString& sample_id) {
    if (!sample_id.isEmpty()) {
        proxymanager::instance()->getSampleProxy()->querySampleWithID(sample_id);
    }
}

void starttestingpage::queryPatientSuccess(const QJsonObject & patient) {
    sample_detail->queryPatientSuccess(patient);
}

void starttestingpage::querySampleSuccess(const QJsonObject& sample) {
    sample_detail->querySampleSuccess(sample);
    QJsonObject patient = sample["patient"].toObject();
    sample_detail->queryPatientSuccess(patient);
}

void starttestingpage::showEvent(QShowEvent *) {
    QObject::connect(cameraproxy::instance(), SIGNAL(stream(const QImage&)),
                     img_pane, SLOT(imageStream(const QImage&)));
    QObject::connect(img_pane, SIGNAL(takeImageSuccess(const QImage&)),
                     this, SLOT(takeImageSuccess(const QImage&)));

    QObject::connect(proxymanager::instance()->getFileProxy(), SIGNAL(uploadSampleImageSuccess(QString,QString)),
                     this, SLOT(uploadSampleImageSuccess(QString,QString)));

    QObject::connect(sample_detail, SIGNAL(didFinishEditPatientID(const QString&)),
                     this, SLOT(didFinishEditPatientId(const QString&)));
    QObject::connect(sample_detail, SIGNAL(didFinishEditSampleID(const QString&)),
                     this, SLOT(didFinishEditSampleId(const QString&)));
    QObject::connect(proxymanager::instance()->getSampleProxy(), SIGNAL(querySampleWithIDSuccess(QJsonObject)),
                     this, SLOT(querySampleWithIDSuccess(QJsonObject)));
    QObject::connect(proxymanager::instance()->getPatientProxy(), SIGNAL(queryPatientSuccess(const QJsonObject&)),
                     this, SLOT(queryPatientSuccess(const QJsonObject&)));
}

void starttestingpage::hideEvent(QHideEvent *) {
    QObject::disconnect(cameraproxy::instance(), SIGNAL(stream(const QImage&)),
                     img_pane, SLOT(imageStream(const QImage&)));
    QObject::disconnect(img_pane, SIGNAL(takeImageSuccess(const QImage&)),
                     this, SLOT(takeImageSuccess(const QImage&)));

    QObject::disconnect(proxymanager::instance()->getFileProxy(), SIGNAL(uploadSampleImageSuccess(QString,QString)),
                     this, SLOT(uploadSampleImageSuccess(QString,QString)));

    QObject::disconnect(sample_detail, SIGNAL(didFinishEditPatientID(const QString&)),
                     this, SLOT(didFinishEditPatientId(const QString&)));
    QObject::disconnect(sample_detail, SIGNAL(didFinishEditSampleID(const QString&)),
                     this, SLOT(didFinishEditSampleId(const QString&)));
    QObject::disconnect(proxymanager::instance()->getSampleProxy(), SIGNAL(querySampleWithIDSuccess(QJsonObject)),
                     this, SLOT(querySampleWithIDSuccess(QJsonObject)));
    QObject::disconnect(proxymanager::instance()->getPatientProxy(), SIGNAL(queryPatientSuccess(const QJsonObject&)),
                     this, SLOT(queryPatientSuccess(const QJsonObject&)));
    cameraproxy::instance()->endTesting();
}

starttestingpage::TestStatus starttestingpage::currentStatus() const {
    return status;
}
