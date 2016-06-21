#include "pushwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "proxy/proxymanager.h"
#include "proxy/sampleproxy.h"
#include "proxy/patientproxy.h"

pushwidget::pushwidget() {
    this->setUpSubviews();
}

pushwidget::~pushwidget() {
    main_layout->deleteLater();
}

void pushwidget::setUpSubviews() {
    sample_id_edit = new QLineEdit;
    sample_resource_edit = new QLineEdit;
    sample_patient_id_edit = new QLineEdit;

    patient_id_edit = new QLineEdit;
    patient_name_edit = new QLineEdit;
    patient_gender_edit = new QLineEdit;
    patient_age_edit = new QLineEdit;

    main_layout = new QVBoxLayout;

    main_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QHBoxLayout* content_layout = new QHBoxLayout;
    content_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QFormLayout* sample_layout = new QFormLayout;
    sample_layout->addRow("样本编号:", sample_id_edit);
    sample_layout->addRow("样本来源:", sample_resource_edit);
    sample_layout->addRow("病人编号:", sample_patient_id_edit);
    QPushButton* sample_button = new QPushButton("录入样本");
    QObject::connect(sample_button, SIGNAL(released()), this, SLOT(sampleBtnClick()));
    sample_layout->addWidget(sample_button);
    QPushButton* sample_cancel = new QPushButton("取消样本");
    QObject::connect(sample_cancel, SIGNAL(released()), this, SLOT(sampleCancelBtnClick()));
    sample_layout->addWidget(sample_cancel);
    content_layout->addLayout(sample_layout);

    QFormLayout* patient_layout = new QFormLayout;
    patient_layout->addRow("病人编号:", patient_id_edit);
    patient_layout->addRow("姓  名:", patient_name_edit);
    patient_layout->addRow("性  别:", patient_gender_edit);
    patient_layout->addRow("年  龄:", patient_age_edit);

    QPushButton* patient_button = new QPushButton("录入病人");
    QObject::connect(patient_button, SIGNAL(released()), this, SLOT(patientBtnClick()));
    patient_layout->addWidget(patient_button);
    QPushButton* patient_cancel = new QPushButton("取消病人");
    QObject::connect(patient_cancel, SIGNAL(released()), this, SLOT(patientCancelBtnClick()));
    patient_layout->addWidget(patient_cancel);

    content_layout->addLayout(patient_layout);

    content_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    main_layout->addLayout(content_layout);
    main_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    this->setLayout(main_layout);
}

QSize pushwidget::sizeHint() const {
    return QSize(300, 300);
}

void pushwidget::sampleBtnClick() {
    QString sample_id = sample_id_edit->text();
    QString sample_resource = sample_resource_edit->text();
    QString sample_patient_id = sample_patient_id_edit->text();

    if (sample_id.isEmpty() && sample_resource.isEmpty() && sample_patient_id.isEmpty()) {
        QMessageBox::information(this, "Error",
                tr("填写所有选项"),
                QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);
    } else {

    }
}

void pushwidget::sampleCancelBtnClick() {
    sample_id_edit->clear();
    sample_resource_edit->clear();
    sample_patient_id_edit->clear();
}

void pushwidget::patientBtnClick() {
    QString patient_id = patient_id_edit->text();
    QString patient_name = patient_name_edit->text();
    QString patient_gender = patient_gender_edit->text();
    QString patient_age = patient_age_edit->text();

    if (patient_id.isEmpty() && patient_name.isEmpty()
            && patient_gender.isEmpty() && patient_age.isEmpty()) {
        QMessageBox::information(this, "Error",
                tr("填写所有选项"),
                QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);
    } else {

    }
}

void pushwidget::patientCancelBtnClick() {
    patient_id_edit->clear();
    patient_name_edit->clear();
    patient_gender_edit->clear();
    patient_age_edit->clear();
}
