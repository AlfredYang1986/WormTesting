#include "sampledetailwidget.h"
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QJsonObject>
#include <QDateTime>
#include "proxy/proxymanager.h"
#include "proxy/patientproxy.h"
#include "proxy/sampleproxy.h"
#include "proxy/configproxy.h"
#include <QGroupBox>
#include <QDateTime>
#include <QDateEdit>
#include <QDateTimeEdit>

sampledetailwidget::sampledetailwidget() {
    this->setUpSubviews();
}

sampledetailwidget::~sampledetailwidget() {
    main_layout->deleteLater();
}

void sampledetailwidget::setUpSubviews() {
    sample_id_edit = new QLineEdit;
    QObject::connect(sample_id_edit, SIGNAL(editingFinished()), this, SLOT(didFinishEditSampleID_slot()));

    sample_resource_box = new QComboBox;

    sample_index_edit = new QLineEdit;
    sample_section_edit = new QLineEdit;
    sample_query_doctor_edit = new QLineEdit;
    sample_pre_test_doctor_edit = new QLineEdit;
    sample_testing_doctor_edit = new QLineEdit;
    sample_post_test_doctor_edit = new QLineEdit;

//    sample_start_date_edit = new QLineEdit;
//    sample_pre_test_date_edit = new QLineEdit;
//    sample_end_date_edit = new QLineEdit;
//    sample_testing_date_edit = new QLineEdit;
//    sample_reporting_date_edit = new QLineEdit;

    sample_start_date_edit = new QDateTimeEdit;
    sample_pre_test_date_edit = new QDateTimeEdit;
    sample_end_date_edit = new QDateTimeEdit;
    sample_testing_date_edit = new QDateTimeEdit;
    sample_reporting_date_edit = new QDateTimeEdit;

    sample_testing_date_edit->setEnabled(false);
    sample_reporting_date_edit->setEnabled(false);

    patient_id_edit = new QLineEdit;
    QObject::connect(patient_id_edit, SIGNAL(editingFinished()), this, SLOT(didFinishEditPatientID_slot()));

    patient_name_edit = new QLineEdit;

    patient_type = new QComboBox;

    patient_gender_box = new QComboBox;
    patient_gender_box->addItem(QStringLiteral("男"));
    patient_gender_box->addItem(QStringLiteral("女"));

    patient_age_edit = new QLineEdit;

    patient_section_edit = new QLineEdit;
    patient_section_id_edit = new QLineEdit;
    patient_section_bed_id_edit = new QLineEdit;

//    content_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    QFormLayout* sample_layout = new QFormLayout;

    QGroupBox* patient_group = new QGroupBox(QStringLiteral("病人信息"));
    QFormLayout* patient_layout = new QFormLayout;

    patient_layout ->addRow(QStringLiteral("病人编号:"), patient_id_edit);
    patient_layout ->addRow(QStringLiteral("病人类型:"), patient_type);
    patient_layout ->addRow(QStringLiteral("姓  名:"), patient_name_edit);
    patient_layout ->addRow(QStringLiteral("性  别:"), patient_gender_box);
    patient_layout ->addRow(QStringLiteral("年  龄:"), patient_age_edit);
    patient_layout ->addRow(QStringLiteral("科  室:"), patient_section_edit);
    patient_layout ->addRow(QStringLiteral("住院号:"), patient_section_id_edit);
    patient_layout ->addRow(QStringLiteral("床  号:"), patient_section_bed_id_edit);

    patient_group->setLayout(patient_layout);
    sample_layout->addRow(patient_group);

    sample_layout->addItem(new QSpacerItem(0, 30, QSizePolicy::Fixed, QSizePolicy::Fixed));

    QGroupBox* sample_group = new QGroupBox(QStringLiteral("样本信息"));
    QFormLayout* info_layout = new QFormLayout;

    info_layout ->addRow(QStringLiteral("样本编号:"), sample_id_edit);
    info_layout ->addRow(QStringLiteral("检验序号:"), sample_index_edit);
    info_layout ->addRow(QStringLiteral("样本类型:"), sample_resource_box);

    info_layout ->addRow(QStringLiteral("开单科室:"), sample_section_edit);
    info_layout ->addRow(QStringLiteral("开单医生:"), sample_query_doctor_edit);
    info_layout ->addRow(QStringLiteral("送检医生:"), sample_pre_test_doctor_edit);
    info_layout ->addRow(QStringLiteral("检测医生:"), sample_testing_doctor_edit);
    info_layout ->addRow(QStringLiteral("审核医生:"), sample_post_test_doctor_edit);

    info_layout ->addRow(QStringLiteral("开单时间:"), sample_start_date_edit);
    info_layout ->addRow(QStringLiteral("取样时间:"), sample_end_date_edit);
    info_layout ->addRow(QStringLiteral("送检时间:"), sample_pre_test_date_edit);
    info_layout ->addRow(QStringLiteral("检测时间:"), sample_testing_date_edit);
    info_layout ->addRow(QStringLiteral("报告时间:"), sample_reporting_date_edit);

    sample_group->setLayout(info_layout);
    sample_layout->addRow(sample_group);

    this->setLayout(sample_layout);
    main_layout=sample_layout;

    QObject::connect(proxymanager::instance()->getConfigProxy(), SIGNAL(queryPatientTypeSuccess(QJsonArray)),
                     this, SLOT(queryPatientTypeSuccess(QJsonArray)));
    QObject::connect(proxymanager::instance()->getConfigProxy(), SIGNAL(querySampleResourceTypeSuccess(QJsonArray)),
                     this, SLOT(querySampleResourceTypeSuccess(QJsonArray)));
}

//QSize sampledetailwidget::sizeHint() const {
//    return QSize(200, 300);
//}

void sampledetailwidget::didFinishEditPatientID_slot() {
    QString patient_id = patient_id_edit->text();
    emit didFinishEditPatientID(patient_id);
}

void sampledetailwidget::didFinishEditSampleID_slot() {
    QString sample_id = sample_id_edit->text();
    emit didFinishEditSampleID(sample_id);
}

void sampledetailwidget::sampleBtnClick() {

    QString sample_id = sample_id_edit->text();
    QString sample_resource = sample_resource_box->currentText();
    QString sample_patient_id = patient_id_edit->text();

    if (sample_id.isEmpty() || sample_resource.isEmpty() || sample_patient_id.isEmpty()) {
        QMessageBox::information(this, "Error",
                QStringLiteral("填写所有选项"),
                QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);
    } else {
        QJsonObject json;
        json.insert("sample_id", sample_id);
        json.insert("resource", sample_resource);

        json.insert("query_doctor", sample_query_doctor_edit->text());
        json.insert("pre_test_doctor", sample_pre_test_doctor_edit->text());
        json.insert("testing_doctor", sample_testing_doctor_edit->text());
        json.insert("post_test_doctor", sample_post_test_doctor_edit->text());

        json.insert("section", sample_section_edit->text());
        json.insert("index", sample_index_edit->text().toInt());

        QDateTime start, end;
        {
            QString str_num = sample_start_date_edit->text();
            QDateTime time;
            time = QDateTime::fromString(str_num, "MM-dd-yyyy hh:mm");
            long long n = time.toMSecsSinceEpoch();
            json.insert("start_date", n);
            start = time;
        }

        {
            QString str_num = sample_end_date_edit->text();
            QDateTime time;
            time = QDateTime::fromString(str_num, "MM-dd-yyyy hh:mm");
            long long n = time.toMSecsSinceEpoch();
            json.insert("end_date", n);
            end = time;
        }
        if (start.toMSecsSinceEpoch() > end.toMSecsSinceEpoch()) {
            QMessageBox::warning(this, "Error",
                                 QStringLiteral("送检时间应该小于取样时间"),
                                 QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
            return;
        }

        {
            QString str_num = sample_pre_test_date_edit->text();
            QDateTime time;
            time = QDateTime::fromString(str_num, "MM-dd-yyyy hh:mm");
            long long n = time.toMSecsSinceEpoch();
            json.insert("pre_test_date", n);
        }


        {
            QString str_num = sample_testing_date_edit->text();
            QDateTime time;
            time = QDateTime::fromString(str_num, "MM-dd-yyyy hh:mm");
            long long n = time.toMSecsSinceEpoch();
            json.insert("testing_date", n);
        }


        {
            QString str_num = sample_reporting_date_edit->text();
            QDateTime time;
            time = QDateTime::fromString(str_num, "MM-dd-yyyy hh:mm");
            long long n = time.toMSecsSinceEpoch();
            json.insert("reporting_date", n);
        }

        QJsonObject patient;
        patient.insert("patient_id", patient_id_edit->text());
        patient.insert("patient_name", patient_name_edit->text());
        int patient_gender = patient_gender_box->currentIndex();
        int patient_age = patient_age_edit->text().toInt();
        patient.insert("patient_gender", (patientproxy::PatientGender)patient_gender);
        patient.insert("patient_age", patient_age);

        patient.insert("patient_section", patient_section_edit->text());
        patient.insert("patient_section_no", patient_section_id_edit->text());
        patient.insert("patient_bed_no", patient_section_bed_id_edit->text());

        json.insert("patient", patient);

        proxymanager::instance()->getSampleProxy()->
                pushOrUpdateSample(json);
    }
}

void sampledetailwidget::sampleCancelBtnClick() {
    sample_id_edit->clear();
//    sample_resource_box->clear();
    sample_index_edit->clear();
    sample_section_edit->clear();
    sample_query_doctor_edit->clear();
    sample_pre_test_doctor_edit->clear();
    sample_testing_doctor_edit->clear();
    sample_post_test_doctor_edit->clear();
    sample_start_date_edit->clear();
    sample_end_date_edit->clear();
    sample_testing_date_edit->clear();
    sample_reporting_date_edit->clear();

    patient_id_edit->clear();
    patient_name_edit->clear();
//    patient_gender_box->clear();
    patient_age_edit->clear();
    patient_section_edit->clear();
    patient_section_id_edit->clear();
    patient_section_bed_id_edit->clear();
}

void sampledetailwidget::queryPatientSuccess(const QJsonObject & patient) {
    if (!patient.isEmpty()) {
        patient_id_edit->setText(patient["patient_id"].toString());
        patient_name_edit->setText(patient["patient_name"].toString());

        int n = patient["patient_gender"].toInt();
        patient_gender_box->setCurrentIndex(n);

        int age = patient["patient_age"].toInt();
        patient_age_edit->setText(QString("%1").arg(age));

        QString section = patient["patient_section"].toString();
        patient_section_edit->setText(section);

        QString section_no = patient["patient_section_no"].toString();
        patient_section_id_edit->setText(section_no);

        QString bed_no = patient["patient_bed_no"].toString();
        patient_section_bed_id_edit->setText(bed_no);

    } else {
        qDebug() << "query patient empty" << endl;
    }
}

void sampledetailwidget::querySampleSuccess(const QJsonObject& sample) {

    if (!sample.isEmpty()) {

        this->clearContents();

        sample_id_edit->setText(sample["sample_id"].toString());
        sample_resource_box->setCurrentText(sample["resource"].toString());

        sample_query_doctor_edit->setText(sample["query_doctor"].toString());
        sample_pre_test_doctor_edit->setText(sample["pre_test_doctor"].toString());
        sample_testing_doctor_edit->setText(sample["testing_doctor"].toString());
        sample_post_test_doctor_edit->setText(sample["post_test_doctor"].toString());

        sample_section_edit->setText(sample["section"].toString());
        sample_index_edit->setText(sample["index"].toString());

        QString date_format = "MM-dd-yyyy";
        {
            qlonglong n = sample["start_date"].toVariant().toLongLong();
            if (n > 0) {
                QDateTime t;
                t.setMSecsSinceEpoch(n);
                sample_start_date_edit->setDateTime(t);
                sample_start_date_edit->setDisplayFormat(date_format);
//                sample_start_date_edit->setText(QString("%1").arg(n));
            }
        }

        {
            qlonglong n = sample["end_date"].toVariant().toLongLong();
            if (n > 0) {
                QDateTime t;
                t.setMSecsSinceEpoch(n);
                sample_end_date_edit->setDateTime(t);
                sample_end_date_edit->setDisplayFormat(date_format);
//                sample_end_date_edit->setText(QString("%1").arg(n));
            }
        }

        {
            qlonglong n = sample["pre_test_date"].toVariant().toLongLong();
            if (n > 0) {
                QDateTime t;
                t.setMSecsSinceEpoch(n);
                sample_pre_test_date_edit->setDateTime(t);
                sample_pre_test_date_edit->setDisplayFormat(date_format);
//                sample_pre_test_date_edit->setText(QString("%1").arg(n));
            }
        }

        QString format = "MM-dd-yyyy HH:mm::ss";
        {
            qlonglong n = sample["testing_date"].toVariant().toLongLong();
            if (n > 0) {
                QDateTime t;
                t.setMSecsSinceEpoch(n);
                sample_testing_date_edit->setDateTime(t);
                sample_testing_date_edit->setDisplayFormat(format);
            }
        }

        {
            qlonglong n = sample["reporting_date"].toVariant().toLongLong();
            if (n > 0) {
                QDateTime t;
                t.setMSecsSinceEpoch(n);
                sample_reporting_date_edit->setDateTime(t);
                sample_reporting_date_edit->setDisplayFormat(format);
//                sample_reporting_date_edit->setText(t.toString(format));
            }
        }

    } else {
        qDebug() << "query patient empty" << endl;
    }
}

QString sampledetailwidget::queryCurrentSampleId() const {
    return sample_id_edit->text();
}

void sampledetailwidget::queryPatientTypeSuccess(const QJsonArray & result) {
    patient_type->clear();
    QJsonArray::const_iterator iter = result.begin();
    for(; iter != result.end(); ++iter) {
        QString tmp = (*iter).toString();
        patient_type->addItem(tmp);
    }
}

void sampledetailwidget::querySampleResourceTypeSuccess(const QJsonArray & result) {
    sample_resource_box->clear();
    QJsonArray::const_iterator iter = result.begin();
    for(; iter != result.end(); ++iter) {
        QString tmp = (*iter).toString();
        sample_resource_box->addItem(tmp);
    }
}

void sampledetailwidget::showEvent(QShowEvent *) {
    sample_id_edit->setFocus();
    proxymanager::instance()->getConfigProxy()->querySampleResourceType();
    proxymanager::instance()->getConfigProxy()->queryPatientType();
}

void sampledetailwidget::clearContents() {
    sample_id_edit->clear();
//    sample_resource_box->clear();
    sample_index_edit->clear();
    sample_section_edit->clear();
    sample_query_doctor_edit->clear();
    sample_pre_test_doctor_edit->clear();
    sample_testing_doctor_edit->clear();
    sample_post_test_doctor_edit->clear();
    sample_start_date_edit->clear();
    sample_end_date_edit->clear();
    sample_testing_date_edit->clear();
    sample_reporting_date_edit->clear();

    patient_id_edit->clear();
    patient_name_edit->clear();
//    patient_gender_box->clear();
    patient_age_edit->clear();
    patient_section_edit->clear();
    patient_section_id_edit->clear();
    patient_section_bed_id_edit->clear();
}
