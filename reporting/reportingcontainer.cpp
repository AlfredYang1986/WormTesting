#include "reportingcontainer.h"
#include "commonwidget/sampledetailwidget.h"
#include "commonwidget/commonimglstwidget.h"
//#include "reportingimgpane.h"
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
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QDesktopServices>
#include <QTextDocument>
#include "printpreviewdialog.h"

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

    QPushButton* print_preview_btn = new QPushButton(QStringLiteral("打印预览"));
    QObject::connect(print_preview_btn, SIGNAL(released()),
                     this, SLOT(printPreview()));
    btn_layout->addWidget(print_preview_btn);

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
        header<< QStringLiteral("样本编号")
              << QStringLiteral("姓名")
              << QStringLiteral("年龄")
              << QStringLiteral("样本来源")
              << QStringLiteral("样本总类")
              << QStringLiteral("送检医生")
              << QStringLiteral("审核医生")
              << QStringLiteral("日期");
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
    current_sample = sample;
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
    QObject::connect(proxymanager::instance()->getPatientProxy(), SIGNAL(queryPatientSuccess(const QJsonObject&)),
                     this, SLOT(queryPatientSuccess(const QJsonObject&)));
    QObject::connect(proxymanager::instance()->getSampleProxy(), SIGNAL(querySampleWithIDSuccess(QJsonObject)),
                     this, SLOT(querySampleWithIDSuccess(QJsonObject)));

    QObject::connect(sample_detail, SIGNAL(didFinishEditPatientID(const QString&)),
                     this, SLOT(didFinishEditPatientId(const QString&)));
    QObject::connect(sample_detail, SIGNAL(didFinishEditSampleID(const QString&)),
                     this, SLOT(didFinishEditSampleId(const QString&)));

    QObject::connect(img_lst, SIGNAL(changeCurrentImageSignal(QPixmap)),
                     img_preview, SLOT(setPreviewImage(QPixmap)));

    QObject::connect(proxymanager::instance()->getSampleProxy(), SIGNAL(updateSampleSuccess(QJsonObject)),
                     this, SLOT(querySampleWithIDSuccess(QJsonObject)));
}

void reportingcontainer::hideEvent(QHideEvent *) {
    QObject::disconnect(proxymanager::instance()->getPatientProxy(), SIGNAL(queryPatientSuccess(const QJsonObject&)),
                     this, SLOT(queryPatientSuccess(const QJsonObject&)));
    QObject::disconnect(proxymanager::instance()->getSampleProxy(), SIGNAL(querySampleWithIDSuccess(QJsonObject)),
                     this, SLOT(querySampleWithIDSuccess(QJsonObject)));

    QObject::disconnect(sample_detail, SIGNAL(didFinishEditPatientID(const QString&)),
                     this, SLOT(didFinishEditPatientId(const QString&)));
    QObject::disconnect(sample_detail, SIGNAL(didFinishEditSampleID(const QString&)),
                     this, SLOT(didFinishEditSampleId(const QString&)));

    QObject::disconnect(img_lst, SIGNAL(changeCurrentImageSignal(QPixmap)),
                     img_preview, SLOT(setPreviewImage(QPixmap)));

    QObject::disconnect(proxymanager::instance()->getSampleProxy(), SIGNAL(updateSampleSuccess(QJsonObject)),
                     this, SLOT(querySampleWithIDSuccess(QJsonObject)));
}

void reportingcontainer::saveTestResult() {
    QString sample_id = sample_detail->queryCurrentSampleId();
    QVector<QString> result = reporting_detail->getTestItemResults();
    proxymanager::instance()->getSampleProxy()->pushReportingTestResult(sample_id, result);
}

void reportingcontainer::queryTesetedSamples(const QJsonArray& samples) {
    tested_sample->clear();
    QStringList header;
    header<< QStringLiteral("样本编号")
          << QStringLiteral("姓名")
          << QStringLiteral("年龄")
          << QStringLiteral("样本来源")
          << QStringLiteral("样本总类")
          << QStringLiteral("送检医生")
          << QStringLiteral("审核医生")
          << QStringLiteral("日期");
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
            QString format = "MM-dd-yyyy HH:mm:ss";
            QTableWidgetItem* item2 = new QTableWidgetItem(t.toString(format));
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

QString reportingcontainer::htmlContent(QTextDocument& document) {

    if (current_sample.isEmpty())
        return "";

    QFile f(":/resource/print");
    if (f.open(QIODevice::OpenModeFlag::ReadOnly)) {
        QString html = f.readAll();
        f.close();

        QJsonObject patient = current_sample["patient"].toObject();
        QString sample_id = current_sample["sample_id"].toString();
        QString patient_name = patient["patient_name"].toString();
        QString patient_gender = patient["patient_gender"].toInt() == 0 ? QStringLiteral("男") : QStringLiteral("女");
        QString patient_age = QString("%1").arg(patient["patient_age"].toInt());
        QString patient_id = patient["patient_id"].toString();
        QString sample_resource = current_sample["resource"].toString();

        QVector<QVariant> result = current_sample["result"].toArray().toVariantList().toVector();
        QStringList str_result;
        QVector<QVariant> ::iterator iter = result.begin();
        for(; iter != result.end(); ++iter) {
            str_result.push_back(iter->toString());
        }

        QString contents = "";
        QString presuffix = "<tr>";
        QString suffix = "</tr>";
        QStringList str_reVal = reporting_detail->getAllReportingField();
        QStringList::iterator i = str_reVal.begin();
        for (; i != str_reVal.end(); ++i) {
            QString tmp = *i;
            contents += presuffix;
            contents += "<td>" + tmp + "</td>";
            if (str_result.contains(tmp)) {
                contents += "<td>" + QString(QStringLiteral("已检出")) + "</td>";
            } else {
                contents += "<td>" + QString(QStringLiteral("未检出")) + "</td>";
            }
            contents += "<td></td>";
            contents += "<td></td>";
            contents += suffix;
        }

        qlonglong testing_time_span = current_sample["testing_date"].toVariant().toLongLong();
        QDateTime testing_time;
        testing_time.setMSecsSinceEpoch(testing_time_span);
        QString format = "MM-dd-yyyy HH:mm:ss";
        QString str_testing_time = testing_time.toString(format);

        QDateTime reporting_time = QDateTime::currentDateTime();
        QString str_reporting_time = reporting_time.toString(format);

        QString testing_doctor = current_sample["testing_doctor"].toString();
        QString post_test_doctor = current_sample["post_test_doctor"].toString();

        QString images = "";
        QString img_preffix = "<td>";
        QString img_suffix = "</td>";

        QVector<QImage> vec_img = img_lst->getCurrentImages();
        QVector<QImage>::iterator vec_img_iter = vec_img.begin();
        int index = 0;
        for (; vec_img_iter != vec_img.end(); ++ vec_img_iter) {
            QImage t = (*vec_img_iter);
            QUrl url;
            url.setUrl(QString("tmp%1").arg(index));
            document.addResource(QTextDocument::ImageResource, url, QVariant(t));

            images += img_preffix;
            images += "<img src='" + QString("tmp%1").arg(index) +  "'></img>";
            images += img_suffix;

            ++index;
        }

        return html.arg(sample_id)
                .arg(patient_name)
                .arg(patient_gender)
                .arg(patient_age)
                .arg(patient_id)
                .arg(sample_resource)
                .arg(contents)
                .arg(str_testing_time)
                .arg(str_reporting_time)
                .arg(testing_doctor)
                .arg(post_test_doctor)
                .arg(images);
    } else {
        return "";
    }
}

void reportingcontainer::changeReportingStatusInService() {
    QJsonObject a;
    QDateTime reporting_time = QDateTime::currentDateTime();
    a.insert("reporting_date", reporting_time.toMSecsSinceEpoch());
    a.insert("status", 2);
    a.insert("sample_id", current_sample["sample_id"].toString());

    proxymanager::instance()->getSampleProxy()->pushOrUpdateSample(a);
}

void reportingcontainer::printPreview() {
    printpreviewdialog* dlg = new printpreviewdialog(this);
    dlg->exec();
}
