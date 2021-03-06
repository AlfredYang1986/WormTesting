﻿#include "reportingcontainer.h"
#include "commonwidget/sampledetailwidget.h"
#include "commonwidget/commonimglstwidget.h"
//#include "reportingimgpane.h"
#include <QHBoxLayout>
#include "proxy/proxymanager.h"
#include "proxy/sampleproxy.h"
#include "proxy/patientproxy.h"
#include "proxy/authproxy.h"
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
#include <QApplication>
#include <QMessageBox>

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

    QPushButton* post_test_btn = new QPushButton(QStringLiteral("审核"));
    QObject::connect(post_test_btn, SIGNAL(released()), this, SLOT(postTestResult()));
    btn_layout->addWidget(post_test_btn);

    QPushButton* save_btn = new QPushButton(QStringLiteral("修改"));
    QObject::connect(save_btn, SIGNAL(released()), this, SLOT(saveTestResult()));
    btn_layout->addWidget(save_btn);

    QPushButton* print_preview_btn = new QPushButton(QStringLiteral("打印预览"));
    QObject::connect(print_preview_btn, SIGNAL(released()),
                     this, SLOT(printPreview()));
    btn_layout->addWidget(print_preview_btn);

//    QPushButton* cancel_btn = new QPushButton(QStringLiteral("取消"));
//    QObject::connect(save_btn, SIGNAL(released()), this, SLOT()
//    btn_layout->addWidget(cancel_btn);

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

    img_lst = new commonimglstwidget(false, false, true);
    //img_lst->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    area->setWidget(img_lst);

    right_layout->addWidget(area);

    tested_sample = new QTableWidget;
    tested_sample->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tested_sample->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    {
        QStringList header;
        header<< QStringLiteral("病人编号")
              << QStringLiteral("姓名")
              << QStringLiteral("年龄")
              << QStringLiteral("样本编号")
              << QStringLiteral("样本类型")
              << QStringLiteral("送检医生")
              << QStringLiteral("检测医生")
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

    QString sample_id = this->current_sample["sample_id"].toString();
    proxymanager::instance()->getSampleProxy()->querySampleWithID(sample_id);
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

    QTime dieTime = QTime::currentTime().addMSecs(1000);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    proxymanager::instance()->getSampleProxy()->querySampleWithID(sample_id);
}

void reportingcontainer::postTestResult() {
    if (proxymanager::instance()->getAuthProxy()->currentAuthStatus() == authproxy::AuthStatus::Auth_testing_doctor) {
        QMessageBox::warning(this, "Error",
                             QStringLiteral("普通测试医生没有这个权限"),
                             QMessageBox::Ok, QMessageBox::Ok);
    } else {
        this->changeReportingStatusToAdjusted();
    }
}

void reportingcontainer::setColorForItem(QTableWidgetItem* item, const int s) {

    switch (s) {
    case 1:
        item->setForeground(QBrush(QColor(255, 0, 0)));
        break;
    case 2:
        break;
        item->setForeground(QBrush(QColor(0, 0, 255)));
    case 3:
        break;
        item->setForeground(QBrush(QColor(0, 255, 0)));
    default:
        break;
    }
}

void reportingcontainer::queryTesetedSamples(const QJsonArray& samples) {
    tested_sample->clear();
    QStringList header;
    header<< QStringLiteral("病人编号")
          << QStringLiteral("姓名")
          << QStringLiteral("年龄")
          << QStringLiteral("样本编号")
          << QStringLiteral("样本类型")
          << QStringLiteral("送检医生")
          << QStringLiteral("检测医生")
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
            QTableWidgetItem* item1 = new QTableWidgetItem(patient["patient_fake_id"].toString());
            setColorForItem(item1, tmp["status"].toInt());
            tested_sample->setItem(index, 0, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(patient["patient_name"].toString());
            setColorForItem(item1, tmp["status"].toInt());
            tested_sample->setItem(index, 1, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(QString("%1").arg(patient["patient_age"].toInt()));
            setColorForItem(item1, tmp["status"].toInt());
            tested_sample->setItem(index, 2, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(tmp["sample_id"].toString());
            setColorForItem(item1, tmp["status"].toInt());
            tested_sample->setItem(index, 3, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(tmp["resource"].toString());
            setColorForItem(item1, tmp["status"].toInt());
            tested_sample->setItem(index, 4, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(tmp["query_doctor"].toString());
            setColorForItem(item1, tmp["status"].toInt());
            tested_sample->setItem(index, 5, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(tmp["testing_doctor"].toString());
            setColorForItem(item1, tmp["status"].toInt());
            tested_sample->setItem(index, 6, item1);
        }

        {
            qlonglong timespan = tmp["date"].toVariant().toLongLong();
            QDateTime t;
            t.setMSecsSinceEpoch(timespan);
            QString format = "MM-dd-yyyy HH:mm:ss";
            QTableWidgetItem* item2 = new QTableWidgetItem(t.toString(format));
            setColorForItem(item2, tmp["status"].toInt());
            tested_sample->setItem(index, 7, item2);
        }
        ++index;
    }
    vec_sample_tested = samples;
}

void reportingcontainer::testedWidgetClicked(const QModelIndex& index) {
    QJsonObject sample = vec_sample_tested.at(index.row()).toObject();
    this->setCurrentReportingSample(sample);
}

QString reportingcontainer::htmlContent(QTextDocument& document) {

    QFile f(":/resource/print");
    if (f.open(QIODevice::OpenModeFlag::ReadOnly)) {
        QString html = f.readAll();
        f.close();

        QJsonObject patient = current_sample["patient"].toObject();
        QString sample_id = current_sample["sample_id"].toString();
        QString patient_name = patient["patient_name"].toString();
        QString patient_gender = patient["patient_gender"].toInt() == 0 ? QStringLiteral("男") : QStringLiteral("女");
        QString patient_age = QString("%1").arg(patient["patient_age"].toInt());
        QString patient_id = patient["patient_fake_id"].toString();
        QString sample_resource = current_sample["resource"].toString();
        QString patient_section = patient["patient_section"].toString();
        QString patient_section_no = patient["patient_section_no"].toString();
        QString patient_bed_no = patient["patient_bed_no"].toString();

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
        //QStringList::iterator i = str_reVal.begin();
        int i = 0;
        for (; i != std::min(str_reVal.size(), 17); ++i) {
            contents += presuffix;
            {
                QString tmp = str_reVal.at(i);
                contents += "<td>" + tmp + "</td>";
                if (str_result.contains(tmp)) {
                    contents += "<td style='text-align:center; border-right: 2px solid #000;'>" + QString(QStringLiteral("已检出")) + "</td>";
                } else {
                    contents += "<td style='text-align:center; border-right: 2px solid #000;'>" + QString(QStringLiteral("未检出")) + "</td>";
                }
            }

            {
                if (i + 17 < str_reVal.size()) {
                    QString tmp = str_reVal.at(i + 17);
                    contents += "<td>" + tmp + "</td>";
                    if (str_result.contains(tmp)) {
                        contents += "<td style='text-align:center'>" + QString(QStringLiteral("已检出")) + "</td>";
                    } else {
                        contents += "<td style='text-align:center'>" + QString(QStringLiteral("未检出")) + "</td>";
                    }
                }
            }
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
        QString img_preffix = "<td style='text-align:center; margin-top: 10px;'>";
        QString img_suffix = "</td>";

//        QVector<QImage> vec_img = img_lst->getCurrentImages();
        QVector<QImage> vec_img = img_lst->getCurrentSelectedImages();
        QVector<QImage>::iterator vec_img_iter = vec_img.begin();
        int index = 0;
        for (; vec_img_iter != vec_img.end(); ++ vec_img_iter) {
            QImage t = (*vec_img_iter).scaledToWidth(300);
            QUrl url;
            url.setUrl(QString("tmp%1").arg(index));
            document.addResource(QTextDocument::ImageResource, url, QVariant(t));

            images += img_preffix;
            images += "<img src='" + QString("tmp%1").arg(index) +  "'></img>";
            images += img_suffix;

            ++index;
        }

        QString hos_name;

        {
        QFile f(QApplication::applicationDirPath() + "/config");
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            hos_name = QString::fromLocal8Bit(f.readAll());
            f.close();
        }
        }

        QString hos_section;

        {
        QFile f(QApplication::applicationDirPath() + "/config_section");
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            hos_section = QString::fromLocal8Bit(f.readAll());
            f.close();
        }
        }

        QString hos_phone;

        {
        QFile f(QApplication::applicationDirPath() + "/config_phone");
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            hos_phone = QString::fromLocal8Bit(f.readAll());
            f.close();
        }
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
                .arg(images)
                .arg(hos_name)
                .arg(patient_section)
                .arg(patient_section_no)
                .arg(patient_bed_no)
                .arg(hos_section)
                .arg(hos_phone);
    } else {
        return "";
    }
}

void reportingcontainer::changeReportingStatusToPrinted() {
    QJsonObject a;
    QDateTime reporting_time = QDateTime::currentDateTime();
    a.insert("reporting_date", reporting_time.toMSecsSinceEpoch());
    a.insert("status", 3);
    a.insert("sample_id", current_sample["sample_id"].toString());
    a.insert("post_test_doctor", proxymanager::instance()->getAuthProxy()->current_user_name);

    proxymanager::instance()->getSampleProxy()->pushOrUpdateSample(a);
}

void reportingcontainer::changeReportingStatusToAdjusted() {

    QJsonObject a;
    QDateTime reporting_time = QDateTime::currentDateTime();
    a.insert("reporting_date", reporting_time.toMSecsSinceEpoch());
    a.insert("status", 2);
    a.insert("sample_id", current_sample["sample_id"].toString());
    a.insert("post_test_doctor", proxymanager::instance()->getAuthProxy()->current_user_name);

    proxymanager::instance()->getSampleProxy()->pushOrUpdateSample(a);
}

void reportingcontainer::printPreview() {

    if (current_sample.isEmpty()) {
        QMessageBox::warning(this, "Error",
                             QStringLiteral("请选择特定sample在进行打印操作"),
                             QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    if (img_lst->getCurrentSelectedImageCount() == 0) {
        QMessageBox::warning(this, "Error",
                             QStringLiteral("请选择一张或者两张图片在进行打印操作"),
                             QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    if (proxymanager::instance()->getAuthProxy()->currentAuthStatus() < authproxy::AuthStatus::Auth_post_test_doctor) {
        QMessageBox::warning(this, "Error",
                             QStringLiteral("权限不够不能打印报告"),
                             QMessageBox::Ok, QMessageBox::Ok);
    } else {

        int result = QMessageBox::warning(this, "Warning",
                                          QStringLiteral("打印将基于用户已经保存的数剧，你没有保存的数据将会丢失。您是否继续？"),
                                          QMessageBox::Cancel | QMessageBox::Ok,
                                          QMessageBox::Ok);

        if (result == QMessageBox::Ok) {
            printpreviewdialog* dlg = new printpreviewdialog(this);
            dlg->exec();
        }
    }
}

bool reportingcontainer::hasAuthToPrint() const {
    if (proxymanager::instance()->getAuthProxy()->currentAuthStatus() > authproxy::AuthStatus::Auth_testing_doctor ||
            current_sample["status"].toInt() > 1) {
        return true;
    } else {
        return false;
    }
}
