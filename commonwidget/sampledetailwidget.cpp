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

sampledetailwidget::sampledetailwidget() {
    this->setUpSubviews();
}

sampledetailwidget::~sampledetailwidget() {
    main_layout->deleteLater();
}

void sampledetailwidget::setUpSubviews() {
    sample_id_edit = new QLineEdit;
    QObject::connect(sample_id_edit, SIGNAL(editingFinished()), this, SLOT(didFinishEditSampleID_slot()));

    sample_resource_edit = new QLineEdit;
    sample_index_edit = new QLineEdit;
    sample_section_edit = new QLineEdit;
    sample_query_doctor_edit = new QLineEdit;
    sample_pre_test_doctor_edit = new QLineEdit;
    sample_testing_doctor_edit = new QLineEdit;
    sample_post_test_doctor_edit = new QLineEdit;
    sample_start_date_edit = new QLineEdit;
    sample_pre_test_date_edit = new QLineEdit;
    sample_end_date_edit = new QLineEdit;
    sample_testing_date_edit = new QLineEdit;
    sample_reporting_date_edit = new QLineEdit;

    patient_id_edit = new QLineEdit;
    QObject::connect(patient_id_edit, SIGNAL(editingFinished()), this, SLOT(didFinishEditPatientID_slot()));

    patient_name_edit = new QLineEdit;

    patient_gender_box = new QComboBox;
    patient_gender_box->addItem(tr("男"));
    patient_gender_box->addItem(tr("女"));

    patient_age_edit = new QLineEdit;

    patient_section_edit = new QLineEdit;
    patient_section_id_edit = new QLineEdit;
    patient_section_bed_id_edit = new QLineEdit;

//    content_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QFormLayout* sample_layout = new QFormLayout;
    sample_layout->addRow("病人编号:", patient_id_edit);
    sample_layout->addRow("姓  名:", patient_name_edit);
    sample_layout->addRow("性  别:", patient_gender_box);
    sample_layout->addRow("年  龄:", patient_age_edit);
    sample_layout->addRow("科  室:", patient_section_edit);
    sample_layout->addRow("住院号:", patient_section_id_edit);
    sample_layout->addRow("床  号:", patient_section_bed_id_edit);

    sample_layout->addItem(new QSpacerItem(0, 30, QSizePolicy::Fixed, QSizePolicy::Fixed));

    sample_layout->addRow("样本编号:", sample_id_edit);
    sample_layout->addRow("检验序号:", sample_index_edit);
    sample_layout->addRow("样本类型:", sample_resource_edit);

    sample_layout->addRow("开单科室:", sample_section_edit);
    sample_layout->addRow("开单医生:", sample_query_doctor_edit);
    sample_layout->addRow("送检医生:", sample_pre_test_doctor_edit);
    sample_layout->addRow("检测医生:", sample_testing_doctor_edit);
    sample_layout->addRow("审核医生:", sample_post_test_doctor_edit);

    sample_layout->addRow("开单时间:", sample_start_date_edit);
    sample_layout->addRow("取样时间:", sample_end_date_edit);
    sample_layout->addRow("送检时间:", sample_pre_test_date_edit);
    sample_layout->addRow("检测时间:", sample_testing_date_edit);
    sample_layout->addRow("报告时间:", sample_reporting_date_edit);

    this->setLayout(sample_layout);
    main_layout=sample_layout;
}

QSize sampledetailwidget::sizeHint() const {
    return QSize(300, 300);
}


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
    QString sample_resource = sample_resource_edit->text();
    QString sample_patient_id = patient_id_edit->text();

    if (sample_id.isEmpty() || sample_resource.isEmpty() || sample_patient_id.isEmpty()) {
        QMessageBox::information(this, "Error",
                tr("填写所有选项"),
                QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);
    } else {
        QJsonObject json;
        json.insert("sample_id", sample_id_edit->text());
        json.insert("resource", sample_resource_edit->text());

        json.insert("query_doctor", sample_query_doctor_edit->text());
        json.insert("pre_test_doctor", sample_pre_test_doctor_edit->text());
        json.insert("testing_doctor", sample_testing_doctor_edit->text());
        json.insert("post_test_doctor", sample_post_test_doctor_edit->text());

        {
            QString str_num = sample_start_date_edit->text();
            QDateTime time;
            time = QDateTime::fromString(str_num, "yyyy-MM-dd hh:mm");
            long long n = time.toMSecsSinceEpoch();
            json.insert("start_date", n);
        }


        {
            QString str_num = sample_end_date_edit->text();
            QDateTime time;
            time = QDateTime::fromString(str_num, "yyyy-MM-dd hh:mm");
            long long n = time.toMSecsSinceEpoch();
            json.insert("end_date", n);
        }


        {
            QString str_num = sample_pre_test_date_edit->text();
            QDateTime time;
            time = QDateTime::fromString(str_num, "yyyy-MM-dd hh:mm");
            long long n = time.toMSecsSinceEpoch();
            json.insert("pre_test_date", n);
        }


        {
            QString str_num = sample_testing_date_edit->text();
            QDateTime time;
            time = QDateTime::fromString(str_num, "yyyy-MM-dd hh:mm");
            long long n = time.toMSecsSinceEpoch();
            json.insert("testing_date", n);
        }


        {
            QString str_num = sample_reporting_date_edit->text();
            QDateTime time;
            time = QDateTime::fromString(str_num, "yyyy-MM-dd hh:mm");
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

        json.insert("patient", patient);

        proxymanager::instance()->getSampleProxy()->
                pushOrUpdateSample(json);
    }
}

void sampledetailwidget::sampleCancelBtnClick() {
    sample_id_edit->clear();
    sample_resource_edit->clear();
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
    patient_gender_box->clear();
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

    } else {
        qDebug() << "query patient empty" << endl;
    }
}

void sampledetailwidget::querySampleSuccess(const QJsonObject& sample) {
    if (!sample.isEmpty()) {
        sample_id_edit->setText(sample["sample_id"].toString());
        sample_resource_edit->setText(sample["resource"].toString());

        sample_query_doctor_edit->setText(sample["query_doctor"].toString());
        sample_pre_test_doctor_edit->setText(sample["pre_test_doctor"].toString());
        sample_testing_doctor_edit->setText(sample["testing_doctor"].toString());
        sample_post_test_doctor_edit->setText(sample["post_test_doctor"].toString());

        {
            long long n = sample["start_date"].toVariant().toLongLong();
            if (n > 0) {
                sample_start_date_edit->setText(QString("%1").arg(n));
            }
        }

        {
            long long n = sample["end_date"].toVariant().toLongLong();
            if (n > 0) {
                sample_end_date_edit->setText(QString("%1").arg(n));
            }
        }

        {
            long long n = sample["pre_test_date"].toVariant().toLongLong();
            if (n > 0) {
                sample_pre_test_date_edit->setText(QString("%1").arg(n));
            }
        }

        {
            long long n = sample["testing_date"].toVariant().toLongLong();
            if (n > 0) {
                sample_testing_date_edit->setText(QString("%1").arg(n));
            }
        }

        {
            long long n = sample["reporting_date"].toVariant().toLongLong();
            if (n > 0) {
                sample_reporting_date_edit->setText(QString("%1").arg(n));
            }
        }

    } else {
        qDebug() << "query patient empty" << endl;
    }
}

QString sampledetailwidget::queryCurrentSampleId() const {
    return sample_id_edit->text();
}
