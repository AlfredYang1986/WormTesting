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
#include <QTableWidget>
#include <QPushButton>
#include <QScrollArea>

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

    {
        QScrollArea* area = new QScrollArea;
        area->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

        sample_detail = new sampledetailwidget;
        sample_detail->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

        area->setWidget(sample_detail);
        main_layout->addWidget(area);
    }

//    main_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    reporting_detail = new reportingdetailwidget;
    reporting_detail->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    main_layout->addWidget(reporting_detail);

    QHBoxLayout* btn_layout = new QHBoxLayout;

    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QPushButton* save_btn = new QPushButton(QStringLiteral("保存"));
    QObject::connect(save_btn, SIGNAL(released()), this, SLOT(saveTestResult()));
    btn_layout->addWidget(save_btn);

    QPushButton* preview_btn = new QPushButton(QStringLiteral("打印"));
//    QObject::connect(save_btn, SIGNAL(released()), this, SLOT()
    btn_layout->addWidget(preview_btn);

    QPushButton* cancel_btn = new QPushButton(QStringLiteral("取消"));
//    QObject::connect(save_btn, SIGNAL(released()), this, SLOT()
    btn_layout->addWidget(cancel_btn);

    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QVBoxLayout* mid_layout = new QVBoxLayout;
    mid_layout->addWidget(reporting_detail);
    mid_layout->addLayout(btn_layout);
    main_layout->addLayout(mid_layout);

//    reporting_img = new reportingimgpane;
//    reporting_img->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
//	main_layout->addWidget(reporting_img);


    QVBoxLayout* right_layout = new QVBoxLayout;

    img_preview = new commonimgpreviewwidget;
//    img_preview->setMaximumWidth(500);
    img_preview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    right_layout->addWidget(img_preview);

    QScrollArea* area = new QScrollArea;
//    area->setMaximumSize(QSize(500, 100));
    area->setMaximumHeight(100);
    area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    img_lst = new commonimglstwidget(false, false);
    //img_lst->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    area->setWidget(img_lst);

    right_layout->addWidget(area);

    tested_sample = new QTableWidget;
    tested_sample->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tested_sample->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    {
        QStringList header;
        header<<"样本编号"<<"姓名" << "年龄" << "样本来源" << "样本总类" << "送检医生" << "审核医生" << "日期";
        tested_sample->setColumnCount(header.count());
        tested_sample->setHorizontalHeaderLabels(header);
    }
    right_layout->addWidget(tested_sample);
    right_layout->addSpacerItem(new QSpacerItem(0, 8, QSizePolicy::Minimum, QSizePolicy::Fixed));

    main_layout->addLayout(right_layout);

    this->setLayout(main_layout);

    QObject::connect(reporting_detail, SIGNAL(changeCurrentSample(const QJsonObject&)),
                     this, SLOT(currentSampleChange(const QJsonObject&)));

    //QObject::connect(reporting_img, SIGNAL(saveReportTestResult()),
    //                 this, SLOT(saveTestResult()));

    QObject::connect(proxymanager::instance()->getSampleProxy(), SIGNAL(queryTestedSampleSuccess(const QJsonArray&)),
                     this, SLOT(queryTesetedSamples(const QJsonArray&)));

    QObject::connect(tested_sample, SIGNAL(clicked(const QModelIndex&)),
                     this, SLOT(testedWidgetClicked(const QModelIndex&)));

    proxymanager::instance()->getSampleProxy()->queryTestedSample();

    this->setStyleSheet("QPushButton {"
                            "width: 80px;"
                            "height: 30px;"
                            "color: white;"
                            "font-size: 14px;"
                            "background-color: #1bd7ff;"
                            "border: 1px solid #1bd7ff;"
                            "margin-bottom: 8px;"
                        "}");
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

void reportingcontainer::setCurrentReportingSample(const QJsonObject& sample) {
    this->querySampleWithIDSuccess(sample);
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

void reportingcontainer::queryTesetedSamples(const QJsonArray& samples) {
    tested_sample->clear();
    QStringList header;
    header<<"样本编号"<<"姓名" << "年龄" << "样本来源" << "样本总类" << "送检医生" << "审核医生" << "日期";
    tested_sample->setColumnCount(header.count());
    tested_sample->setHorizontalHeaderLabels(header);

    tested_sample->setRowCount(samples.count());

    QJsonArray::const_iterator iter = samples.begin();
    int index = 0;
    for(; iter != samples.end(); ++iter) {
        QJsonObject tmp = (*iter).toObject();
        QJsonObject patient = tmp["patient"].toObject();

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(tmp["sample_id"].toString());
            if (tmp["status"].toInt() == 1)
                item1->setForeground(QBrush(QColor(255, 0, 0)));
            else
                item1->setForeground(QBrush(QColor(0, 0, 255)));
            tested_sample->setItem(index, 0, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(patient["patient_name"].toString());
            if (tmp["status"].toInt() == 1)
                item1->setForeground(QBrush(QColor(255, 0, 0)));
            else
                item1->setForeground(QBrush(QColor(0, 0, 255)));
            tested_sample->setItem(index, 1, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(QString("%1").arg(patient["patient_age"].toInt()));
            if (tmp["status"].toInt() == 1)
                item1->setForeground(QBrush(QColor(255, 0, 0)));
            else
                item1->setForeground(QBrush(QColor(0, 0, 255)));
            tested_sample->setItem(index, 2, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(tmp["resource"].toString());
            if (tmp["status"].toInt() == 1)
                item1->setForeground(QBrush(QColor(255, 0, 0)));
            else
                item1->setForeground(QBrush(QColor(0, 0, 255)));
            tested_sample->setItem(index, 3, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem("");
            if (tmp["status"].toInt() == 1)
                item1->setForeground(QBrush(QColor(255, 0, 0)));
            else
                item1->setForeground(QBrush(QColor(0, 0, 255)));
            tested_sample->setItem(index, 4, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(tmp["testing_doctor"].toString());
            if (tmp["status"].toInt() == 1)
                item1->setForeground(QBrush(QColor(255, 0, 0)));
            else
                item1->setForeground(QBrush(QColor(0, 0, 255)));
            tested_sample->setItem(index, 5, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(tmp["testing_doctor"].toString());
            if (tmp["status"].toInt() == 1)
                item1->setForeground(QBrush(QColor(255, 0, 0)));
            else
                item1->setForeground(QBrush(QColor(0, 0, 255)));
            tested_sample->setItem(index, 6, item1);
        }

        {
            qlonglong timespan = tmp["date"].toVariant().toLongLong();
            QDateTime t;
            t.setMSecsSinceEpoch(timespan);
            QTableWidgetItem* item2 = new QTableWidgetItem(t.toString());
            if (tmp["status"].toInt() == 1)
                item2->setForeground(QBrush(QColor(255, 0, 0)));
            else
                item2->setForeground(QBrush(QColor(0, 0, 255)));
            tested_sample->setItem(index, 7, item2);
        }
        ++index;
    }
    vec_sample_tested = samples;
}

void reportingcontainer::testedWidgetClicked(const QModelIndex& index) {
    QJsonObject sample = vec_sample_tested.at(index.row()).toObject();
}
